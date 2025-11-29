#ifndef DIARY_EVENT_H
#define DIARY_EVENT_H

#include "DataComponent.h"
#include <string>
#include <utility>

class Event : public DataComponent
{
    std::string datetime;
public:
    Event(const int id, const std::string& title, const std::string &dt) : DataComponent(id, title), datetime(dt) {}
    [[nodiscard]] BaseComponent* clone() const override { return new Event(*this); }

    [[nodiscard]] std::string getDate() const override { return datetime; }
    void setDate(const std::string& d) override { datetime = d; }

    [[nodiscard]] std::string getInfo() const override { return "[EVENT] " + title + " at " + datetime;}
};

#endif //DIARY_EVENT_H