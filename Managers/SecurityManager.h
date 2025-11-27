//
// Created by User on 26.11.2025.
//

#ifndef DIARY_SECURITY_H
#define DIARY_SECURITY_H

#include <string>

#include "StorageManager.h"

class SecurityManager
{
public:
    bool login();
    void loadPassword();
    void changePassword(const std::string& path = "password.dat");
private:
    std::string password;
};


#endif //DIARY_SECURITY_H