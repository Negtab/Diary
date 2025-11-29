#ifndef DIARY_SECURITY_H
#define DIARY_SECURITY_H

#include <string>

class SecurityManager
{
public:
    void loadPassword();
    [[nodiscard]] bool login() const;
    void changeName(const std::string& path = "password.dat");
    void changePassword(const std::string& path = "password.dat");
private:
    std::string name;
    std::string password;
};


#endif //DIARY_SECURITY_H