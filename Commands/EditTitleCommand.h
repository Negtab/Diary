//
// Created by User on 26.11.2025.
//

#ifndef DIARY_EDITTITLECOMMAND_H
#define DIARY_EDITTITLECOMMAND_H

#include "../MainTypes/DataComponent.h"
#include "Command.h"
#include <string>
#include <utility>

class EditTitleCommand : public Command
{
    BaseComponent* item;
    std::string oldTitle;
    std::string newTitle;

public:
    EditTitleCommand(BaseComponent* i, std::string  oldT, std::string  newT)
        : item(i), oldTitle(std::move(oldT)), newTitle(std::move(newT)) {}

    void execute(Diary& diary) override { dynamic_cast<DataComponent*>(item)->setTitle(newTitle); }
    void undo(Diary& diary) override { dynamic_cast<DataComponent*>(item)->setTitle(oldTitle); }
};




#endif //DIARY_EDITCOMMAND_H