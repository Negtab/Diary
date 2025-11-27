#ifndef DIARY_INPUTMANAGER_H
#define DIARY_INPUTMANAGER_H
#include <string>

class InputManager {
public:
    InputManager() = default;
    ~InputManager() = default;

    static bool isValidTime(const std::string& s);
    static bool isValidDate(int d, int m, int y);
    static int inputInt(const std::string& prompt, int minVal, int maxVal);
    static std::string inputString(const std::string& prompt, bool allowEmpty = false);
private:
    static bool isLeap(int year);
};

#endif