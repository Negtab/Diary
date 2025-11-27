#ifndef DIARY_CLEARCOMMAND_H
#define DIARY_CLEARCOMMAND_H

#include "Command.h"
#include <vector>

class BaseComponent;

class ClearCommand : public Command
{
    std::vector<BaseComponent*> backup;
public:
    ~ClearCommand() override = default;

    void execute(Diary& diary) override
    {
        backup.clear();
        for (auto* item : diary.items)
            backup.push_back(item->clone());

        diary.clearInternal();
    }
    void undo(Diary& diary) override
    {
        diary.clear();

        for (auto* item : backup)
            diary.items.push_back(item->clone());
    }
};

#endif //DIARY_CLEARCOMMAND_H