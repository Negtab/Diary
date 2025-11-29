#include "SecurityManager.h"
#include "StorageManager.h"

#include <iostream>
#include <limits>

bool SecurityManager::login() const {
    std::string log, pas;
    std::cout << "Введите логин: ";
    std::cin >> log;
    std::cout << "Введите пароль: ";
    std::cin >> pas;
    return ((pas == password) && (log == name));
}

void SecurityManager::changeName(const std::string &path)
{
    std::string buff = StorageManager::loadPassword(path);
    std::string oldLog = buff.substr(0, buff.find('\n'));
    std::string oldPass = buff.substr(buff.find('\n') + 1);

    std::string input;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введите текущий логин: ";
    std::getline(std::cin, input);

    if (input.compare(oldLog))
    {
        std::cout << "Ошибка: пароль логин!\n";
        return;
    }

    std::cout << "Введите текущий пароль: ";
    std::getline(std::cin, input);

    if (input.compare(oldPass))
    {
        std::cout << "Ошибка: пароль неверный!\n";
        return;
    }

    std::string newLog1, newLog2;
    std::cout << "Введите новый логин: ";
    std::getline(std::cin, newLog1);

    if (newLog1.size() < 4)
    {
        std::cout << "Ошибка: пароль должен быть минимум 4 символа.\n";
        return;
    }

    std::cout << "Повторите новый логин: ";
    std::getline(std::cin, newLog2);

    if (newLog1 != newLog2)
    {
        std::cout << "Ошибка: пароли не совпадают!\n";
        return;
    }

    StorageManager::savePassword(newLog1, oldPass, path);
    std::cout << "Пароль успешно изменён!\n";
}



void SecurityManager::changePassword(const std::string& path)
{
    std::string buff = StorageManager::loadPassword(path);
    std::string oldLog = buff.substr(0, buff.find('\n'));
    std::string oldPass = buff.substr(buff.find('\n') + 1);

    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введите текущий логин: ";
    std::getline(std::cin, input);

    if (input.compare(oldLog))
    {
        std::cout << "Ошибка: пароль логин!\n";
        return;
    }

    std::cout << "Введите текущий пароль: ";
    std::getline(std::cin, input);

    if (input.compare(oldPass))
    {
        std::cout << "Ошибка: пароль неверный!\n";
        return;
    }

    std::string newPass1, newPass2;
    std::cout << "Введите новый пароль: ";
    std::getline(std::cin, newPass1);

    if (newPass1.size() < 4)
    {
        std::cout << "Ошибка: пароль должен быть минимум 4 символа.\n";
        return;
    }

    std::cout << "Повторите новый пароль: ";
    std::getline(std::cin, newPass2);

    if (newPass1 != newPass2)
    {
        std::cout << "Ошибка: пароли не совпадают!\n";
        return;
    }

    StorageManager::savePassword(oldLog, newPass1, path);
    std::cout << "Пароль успешно изменён!\n";
}

void SecurityManager::loadPassword()
{
    std::string buf = StorageManager::loadPassword();
    name = buf.substr(0, buf.find('\n'));
    password = buf.substr(buf.find('\n') + 1);
}
