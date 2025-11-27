#include "StorageManager.h"
#include "../MainTypes/Note.h"
#include "../MainTypes/Event.h"
#include "../MainTypes/Reminder.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string StorageManager::xorCrypt(const std::string &data, const std::string &key)
{
    std::string out = data;
    for (size_t i = 0; i < data.size(); ++i)
        out[i] = data[i] ^ key[i % key.size()];
    return out;
}

static const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string StorageManager::base64_encode(const std::string &in) {
    std::string out;
    int val=0, valb=-6;
    for (unsigned char c : in)
    {
        val = (val<<8) + c;
        valb += 8;
        while (valb >= 0)
        {
            out.push_back(table[(val>>valb)&0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6)
        out.push_back(table[((val<<8)>>(valb+8))&0x3F]);
    while (out.size()%4)
        out.push_back('=');
    return out;
}

std::string StorageManager::base64_decode(const std::string &in)
{
    std::string out;
    std::vector<int> T(256,-1);
    for (int i=0; i<64; i++)
        T[table[i]] = i;

    int val = 0, valb =- 8;
    for (unsigned char c : in)
    {
        if (T[c] == -1)
            break;
        val = (val<<6) + T[c];
        valb += 6;
        if (valb >= 0)
        {
            out.push_back(char((val>>valb)&0xFF));
            valb -= 8;
        }
    }
    return out;
}

void StorageManager::save(const std::vector<BaseComponent*>& items, const std::string& filename)
{
    std::ofstream out(filename);
    std::ostringstream raw;

    for (auto* i : items)
        raw << i->getInfo() << "\n";

    std::string encrypted = xorCrypt(base64_encode(raw.str()), "my_secret_key");
    out << encrypted;
    out.close();
}

void StorageManager::load(std::vector<BaseComponent*>& items, const std::string& filename)
{
    std::ifstream in(filename);
    if (!in.is_open())
        return;

    std::stringstream ss;

    ss << in.rdbuf();
    in.close();

    std::string encrypted = ss.str();

    std::string decoded = base64_decode(xorCrypt(encrypted, "my_secret_key"));

    std::stringstream data(decoded);
    std::string line;

    while (std::getline(data, line))
    {
        if (line.size() < 3) continue;
        if (line[0] != '[') continue;
        if (line.find(']') == std::string::npos) continue;

        if (line.rfind("[NOTE]", 0) == 0) {
            size_t p = line.find(']');
            if (p == std::string::npos || p + 2 > line.size())
                continue;
            std::string rest = line.substr(p + 2);
            size_t colon = rest.find(':');
            items.push_back(new Note(rand()%100000, rest.substr(0, colon), rest.substr(colon+2)));
        }
        else if (line.rfind("[EVENT]", 0) == 0) {
            size_t p = line.find(']');
            if (p == std::string::npos || p + 2 > line.size())
                continue;
            std::string rest = line.substr(p + 2);
            size_t at = rest.find(" at ");
            items.push_back(new Event(rand()%100000, rest.substr(0, at), rest.substr(at+4)));
        }
        else if (line.rfind("[REMINDER]", 0) == 0) {
            size_t p = line.find(']');
            if (p == std::string::npos || p + 2 > line.size())
                continue;
            std::string rest = line.substr(p + 2);

            size_t sep1 = rest.find(" -> ");
            size_t sep2 = rest.find(" -> ", sep1 + 4);

            if (sep1 == std::string::npos || sep2 == std::string::npos)
                continue;

            std::string title = rest.substr(0, sep1);
            std::string date  = rest.substr(sep1 + 4, sep2 - (sep1 + 4));
            std::string time  = rest.substr(sep2 + 4);

            items.push_back(new Reminder(rand() % 100000, title, date, time));
        }
    }
}

void StorageManager::saveTxt(const std::vector<BaseComponent*>& items, const std::string& filename)
{
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error: cannot open " << filename << " for writing\n";
        return;
    }

    for (auto* i : items)
        out << i->getInfo() << "\n";
}

void StorageManager::loadTxt(std::vector<BaseComponent*>& items, const std::string& filename)
{
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Error: cannot open " << filename << "\n";
        return;
    }

    std::string line;
    while (std::getline(in, line))
    {
        if (line.size() < 3) continue;
        if (line[0] != '[') continue;

        size_t endTag = line.find(']');
        if (endTag == std::string::npos) continue;

        std::string tag = line.substr(0, endTag + 1);
        std::string rest = (endTag + 2 < line.size()) ? line.substr(endTag + 2) : "";

        if (tag == "[NOTE]") {

            size_t colon = rest.find(':');
            if (colon == std::string::npos) continue;

            std::string title = rest.substr(0, colon);
            std::string text  = (colon + 2 < rest.size()) ? rest.substr(colon + 2) : "";

            items.push_back(new Note(rand() % 100000, title, text));
        }
        else if (tag == "[EVENT]") {

            size_t at = rest.find(" at ");
            if (at == std::string::npos) continue;

            std::string title = rest.substr(0, at);
            std::string date  = rest.substr(at + 4);

            items.push_back(new Event(rand() % 100000, title, date));
        }
        else if (tag == "[REMINDER]") {

            size_t sep1 = rest.find(" -> ");
            size_t sep2 = rest.find(" -> ", sep1 + 4);

            if (sep1 == std::string::npos || sep2 == std::string::npos)
                continue;

            std::string title = rest.substr(0, sep1);
            std::string date  = rest.substr(sep1 + 4, sep2 - (sep1 + 4));
            std::string time  = rest.substr(sep2 + 4);

            items.push_back(new Reminder(rand() % 100000, title, date, time));
        }
    }
}

void StorageManager::savePassword(const std::string& pass, const std::string& path)
{
    std::ofstream f(path, std::ios::binary);
    std::string enc = xorCrypt(pass, "my_secret_key");
    f << enc;
}

std::string StorageManager::loadPassword(const std::string& path)
{
    std::ifstream f(path, std::ios::binary);
    if (!f)
        return "1234";

    std::string enc;
    std::getline(f, enc);
    return xorCrypt(enc, "my_secret_key");
}

