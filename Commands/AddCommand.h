#ifndef DIARY_ADDCOMMAND_H
#define DIARY_ADDCOMMAND_H

#include "Command.h"
#include "../MainTypes/BaseComponent.h"

class AddCommand : public Command
{
    BaseComponent* added;
public:
    explicit AddCommand(BaseComponent* comp) : added(comp) {}

    void execute(Diary& diary) override { diary.addInternal(added); }
    void undo(Diary& diary) override { diary.removeInternal(added->getId()); }
};

#endif //DIARY_ADDCOMMAND_H