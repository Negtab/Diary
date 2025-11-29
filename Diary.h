#ifndef DIARY_DIARY_H
#define DIARY_DIARY_H

#include <vector>
#include <memory>

#include "MainTypes/BaseComponent.h"
#include "Commands/Command.h"

class Diary
{
public:
    Diary();
    ~Diary();

    void add(BaseComponent* item);
    void remove(int id);
    void edit(int id);
    void clear();

    void showReminder();

    void undo();

    void addInternal(BaseComponent* item);
    void removeInternal(int id);
    void editInternal(int id, const std::string& newTitle);
    void clearInternal();

    void list() const;

    std::vector<BaseComponent*> items;
private:
    std::vector<Command*> history;
};


#endif //DIARY_DIARY_H