//
// Created by User on 26.11.2025.
//

#ifndef DIARY_CALENDAR_H
#define DIARY_CALENDAR_H

#include <string>
#include <vector>

#include "MainTypes/BaseComponent.h"

class Calendar {
public:
    static bool isLeap(int year);
    static int daysInMonth(int month, int year);
    static int dayOfWeek(int d, int m, int y);
    static void printMonth(int month, int year, const std::vector<BaseComponent*>& items);
private:
    static bool parseDate(const std::string& s, int &d, int &m, int &y);
};

#endif //DIARY_CALENDAR_H