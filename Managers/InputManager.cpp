#include <iostream>
#include <ctime>
#include "InputManager.h"

int InputManager::inputInt(const std::string& prompt, const int minVal, const int maxVal) {
    int value;
    bool isCorrect;
    do {
        isCorrect = true;
        std::cout << prompt;

        std::cin >> value;
        if (std::cin.fail() || std::cin.peek() != '\n' || value < minVal || value > maxVal)
            isCorrect = false;

        if (!isCorrect)
        {
            std::cout << "Ошибка: введите число от " << minVal << " до " << maxVal << ".\n";
            std::cin.clear();
            while (std::cin.get() != '\n') {}
        }

    } while (!isCorrect);

    while (std::cin.get() != '\n') {}

    return value;
}

std::string InputManager::inputString(const std::string& prompt, const bool allowEmpty) {
    while (true) {
        std::cout << prompt;
        std::string s;
        std::getline(std::cin, s);

        if (!allowEmpty && s.empty()) {
            std::cout << "Ошибка: строка не может быть пустой!\n";
            continue;
        }
        return s;
    }
}

bool InputManager::isLeap(const int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

bool InputManager::isValidDate(const int d, const int m, const int y)
{
    time_t currentTime = time(nullptr);
    struct tm *localTime = localtime(&currentTime);

    int year = localTime->tm_year + 1900;
    int month = localTime->tm_mon + 1;
    int day = localTime->tm_mday;


    if (y < year || y > 3000) return false;
    if ((y == year && (m < month || m > 12)) || m < 1 || m > 12) return false;

    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && isLeap(y)) daysInMonth[1] = 29;

    return (year == y && month == m) ? d >= day && d <= daysInMonth[m-1] : d >= 1 && d <= daysInMonth[m-1];
}

bool InputManager::isValidTime(const std::string& s) {
    if (s.size() != 5) return false;
    if (s[2] != ':') return false;

    if (!isdigit(s[0]) || !isdigit(s[1]) ||
        !isdigit(s[3]) || !isdigit(s[4]))
        return false;


    int hh = (s[0] - '0') * 10 + (s[1] - '0');
    int mm = (s[3] - '0') * 10 + (s[4] - '0');

    if (hh < 0 || hh > 23) return false;
    if (mm < 0 || mm > 59) return false;

    return true;
}
