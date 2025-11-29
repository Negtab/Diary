#include "SecurityManager.h"
#include "StorageManager.h"

#include <iostream>

bool SecurityManager::login() const {
    std::string input;
    std::cout << "Введите пароль: ";
    std::cin >> input;
    return input == password;
}

void SecurityManager::changePassword(const std::string& path)
{
    std::string oldPass = StorageManager::loadPassword(path);

    std::string input;
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

    StorageManager::savePassword(newPass1, path);
    std::cout << "Пароль успешно изменён!\n";
}

void SecurityManager::loadPassword()
{
    password = StorageManager::loadPassword();
}
