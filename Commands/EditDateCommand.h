#ifndef DIARY_EDITDATACOMMAND_H
#define DIARY_EDITDATACOMMAND_H

#include "../Diary.h"
#include "../MainTypes/DataComponent.h"

class EditDateCommand : public Command
{
    DataComponent* item;
    std::string oldDate;
    std::string newDate;
public:
    EditDateCommand(BaseComponent* i, const std::string& o, const std::string& n)
        : item(dynamic_cast<DataComponent*>(i)), oldDate(o), newDate(n) {}

    void execute(Diary&) override { item->setDate(newDate); }
    void undo(Diary&) override { item->setDate(oldDate); }
};


#endif //DIARY_EDITDATACOMMAND_H