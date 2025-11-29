#include "Calendar.h"

#include <iostream>
#include <iomanip>

#include "MainTypes/Event.h"
#include "MainTypes/Reminder.h"

bool Calendar::isLeap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

int Calendar::daysInMonth(int m, int y) {
    static int md[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && isLeap(y)) return 29;
    return md[m - 1];
}

int Calendar::dayOfWeek(int d, int m, int y) {
    if (m < 3)
    {
        m += 12;
        y -= 1;
    }
    int K = y % 100;
    int J = y / 100;
    int h = (d + 13*(m+1)/5 + K + K/4 + J/4 + 5*J) % 7;
    return (h + 6) % 7;
}

bool Calendar::parseDate(const std::string& s, int &d, int &m, int &y)
{
    std::stringstream ss(s);
    char dot1, dot2;
    ss >> d >> dot1 >> m >> dot2 >> y;
    return ss && dot1 == '.' && dot2 == '.';
}


void Calendar::printMonth(int m, int y, const std::vector<BaseComponent*>& items)
{
    time_t currentTime = time(nullptr);
    struct tm *localTime = localtime(&currentTime);

    int year  = localTime->tm_year + 1900;
    int month = localTime->tm_mon + 1;
    int day   = localTime->tm_mday;

    static const char* MONTHS[] =
    {"January","February","March","April","May","June","July","August",
     "September","October","November","December"};

    std::cout << "\n      " << MONTHS[m - 1] << " " << y << "\n";
    std::cout << " Mo Tu We Th Fr Sa Su\n";

    int firstDay = dayOfWeek(1, m, y);
    int dims = daysInMonth(m, y);

    std::vector<bool> marks(dims + 1, false);

    for (auto* item : items)
    {
        if (auto* e = dynamic_cast<Event*>(item))
        {
            int dE, mE, yE;
            if (parseDate(e->getDate(), dE, mE, yE))
                if (mE == m && yE == y && dE >= 1 && dE <= dims)
                    marks[dE] = true;
        }
        if (auto* r = dynamic_cast<Reminder*>(item))
        {
            int dR, mR, yR;
            if (parseDate(r->getDate(), dR, mR, yR))
                if (mR == m && yR == y && dR >= 1 && dR <= dims)
                    marks[dR] = true;
        }
    }

    for (int i = 0; i < firstDay; i++)
        std::cout << "    ";

    for (int d = 1; d <= dims; d++)
    {
        bool isToday = (d == day && m == month && y == year);
        bool hasEvent = marks[d];

        std::stringstream cell;

        if (isToday)
            cell << "[" << d << "]";
        else if (hasEvent)
            cell << " " << d << "*";
        else
            cell << " " << d << " ";

        std::string out = cell.str();
        while (out.size() < 4) out.push_back(' ');

        std::cout << out;

        if ((firstDay + d) % 7 == 0)
            std::cout << "\n";
    }

    std::cout << "\n\n";

    std::cout << "Events & Reminders this month:\n";

    bool found = false;

    for (auto* item : items)
    {
        if (auto* e = dynamic_cast<Event*>(item))
        {
            int dE, mE, yE;
            if (parseDate(e->getDate(), dE, mE, yE))
                if (mE == m && yE == y)
                {
                    std::cout << " • " << e->getInfo() << "\n";
                    found = true;
                }
        }
        if (auto* r = dynamic_cast<Reminder*>(item))
        {
            int dR, mR, yR;
            if (parseDate(r->getDate(), dR, mR, yR))
                if (mR == m && yR == y)
                {
                    std::cout << " • " << r->getInfo() << "\n";
                    found = true;
                }
        }
    }

    if (!found)
        std::cout << " (none)\n";
}
