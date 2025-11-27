#ifndef DIARY_STORAGE_H
#define DIARY_STORAGE_H

#include <string>
#include <vector>

#include "../MainTypes/BaseComponent.h"

class StorageManager {
public:
    static void save(const std::vector<BaseComponent*>& items, const std::string& filename = "save.dat");
    static void load(std::vector<BaseComponent*>& items, const std::string& filename = "save.dat");

    static void saveTxt(const std::vector<BaseComponent*>& items, const std::string& filename = "save.txt");
    static void loadTxt(std::vector<BaseComponent*>& items, const std::string& filename = "save.txt");

    static void savePassword(const std::string& pass, const std::string& path = "password.dat");
    static std::string loadPassword(const std::string& path = "password.dat");
private:
    static std::string xorCrypt(const std::string& data, const std::string& key);
    static std::string base64_encode(const std::string& in);
    static std::string base64_decode(const std::string& in);
};


#endif //DIARY_STORAGE_H