#ifndef DIARY_NOTE_H
#define DIARY_NOTE_H

#include <utility>

#include "DataComponent.h"
#include "Event.h"

class Note : public DataComponent
{
    std::string text;
public:
    Note(int id, const std::string& title, std::string  text) : DataComponent(id, title), text(std::move(text)) {}

    explicit Note(const Event & event);

    void setText(const std::string& t) { text = t; }
    [[nodiscard]] std::string getText() const { return text; }
    [[nodiscard]] BaseComponent* clone() const override { return new Note(*this); }
    [[nodiscard]] std::string getInfo() const override { return "[NOTE] " + title + ": " + text; }
};

#endif //DIARY_NOTE_H