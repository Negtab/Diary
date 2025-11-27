//
// Created by User on 26.11.2025.
//

#ifndef DIARY_EVENT_H
#define DIARY_EVENT_H

#include "DataComponent.h"
#include <string>
#include <utility>

class Event : public DataComponent
{
    std::string datetime;
public:
    Event(const int id, const std::string& title, std::string  dt) : DataComponent(id, title), datetime(std::move(dt)) {}
    [[nodiscard]] BaseComponent* clone() const override { return new Event(*this); }

    [[nodiscard]] std::string getDate() const override { return datetime; }
    void setDate(const std::string& d) override { datetime = d; }

    [[nodiscard]] std::string getInfo() const override { return "[EVENT] " + title + " at " + datetime;}
};

#endif //DIARY_EVENT_H