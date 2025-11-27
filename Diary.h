//
// Created by User on 26.11.2025.
//

#ifndef DIARY_DIARY_H
#define DIARY_DIARY_H

#include <vector>
#include <memory>

#include "MainTypes/BaseComponent.h"
#include "Commands/Command.h"

class Diary
{
    std::vector<Command*> history;
public:
    Diary() = default;
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
};


#endif //DIARY_DIARY_H