#ifndef DIARY_EDITTIMECOMMAND_H
#define DIARY_EDITTIMECOMMAND_H

#include "../Diary.h"
#include "../MainTypes/Reminder.h"

class EditTimeCommand : public Command
{
    Reminder* reminder;
    std::string oldTime;
    std::string newTime;

public:
    EditTimeCommand(Reminder* r, const std::string& o, const std::string& n)
        : reminder(r), oldTime(o), newTime(n) {}

    void execute(Diary&) override { reminder->setTime(newTime); }
    void undo(Diary&) override { reminder->setTime(oldTime); }
};


#endif //DIARY_EDITTIMECOMMAND_H