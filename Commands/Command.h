#ifndef DIARY_COMMAND_H
#define DIARY_COMMAND_H

class Diary;

class Command
{
public:
    virtual ~Command() = default;
    virtual void execute(Diary& diary) = 0;
    virtual void undo(Diary& diary) = 0;
};

#endif //DIARY_COMMAND_H