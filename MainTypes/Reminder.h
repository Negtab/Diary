//
// Created by User on 26.11.2025.
//

#ifndef DIARY_REMINDER_H
#define DIARY_REMINDER_H

#include "DataComponent.h"
#include <string>
#include <utility>

class Reminder : public DataComponent
{
    std::string time;
    std::string date;
public:
    Reminder(const int id, const std::string &title, std::string date, std::string time) :
            DataComponent(id, title), time(std::move(time)), date(std::move(date)) {}

    [[nodiscard]] BaseComponent* clone() const override { return new Reminder(*this); }

    [[nodiscard]] std::string getDate() const override { return date; }
    void setDate(const std::string& d) override { date = d; }

    [[nodiscard]] std::string getTime() const { return time; }
    void setTime(const std::string& t) { time = t; }

    [[nodiscard]] std::string getInfo() const override { return "[REMINDER] " + title + " -> " + date + " -> " + time; }
};

#endif //DIARY_REMINDER_H