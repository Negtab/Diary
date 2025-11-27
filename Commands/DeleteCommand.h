//
// Created by User on 26.11.2025.
//

#ifndef DIARY_DELETECOMMAND_H
#define DIARY_DELETECOMMAND_H

#include "Command.h"
#include "../MainTypes/BaseComponent.h"

class DeleteCommand : public Command
{
    BaseComponent* removed;
public:
    DeleteCommand(BaseComponent* comp) : removed(comp) {}

    void execute(Diary& diary) override{ diary.removeInternal(removed->getId()); }
    void undo(Diary& diary) override { diary.addInternal(removed); }
};

#endif //DIARY_DELETECOMMAND_H