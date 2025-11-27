#include "Diary.h"

#include <algorithm>

#include "Commands/AddCommand.h"
#include "Commands/DeleteCommand.h"
#include "Commands/EditTitleCommand.h"
#include <iostream>
#include <sstream>

#include "Commands/ClearCommand.h"
#include "Commands/EditDateCommand.h"
#include "Commands/EditTextCommand.h"
#include "Commands/EditTimeCommand.h"
#include "MainTypes/DataComponent.h"
#include "MainTypes/Note.h"
#include "MainTypes/Reminder.h"
#include "Managers/InputManager.h"

Diary::~Diary()
{
    for (auto* i : items)
        delete i;
    for (auto* c : history)
        delete c;
}

void Diary::add(BaseComponent* item)
{
    Command* cmd = new AddCommand(item);
    cmd->execute(*this);
    history.push_back(cmd);
}

void Diary::remove(const int id)
{
    BaseComponent* found = nullptr;
    for (auto* i : items)
        if (i->getId() == id)
            found = i;

    if (!found)
    {
        std::cout << "Элемент не найден";
        return;
    }

    std::cout << "Элемент найден и удален";

    Command* cmd = new DeleteCommand(found);
    cmd->execute(*this);
    history.push_back(cmd);
}

void Diary::edit(int id)
{
    BaseComponent* item = nullptr;
    for (auto* i : items)
        if (i->getId() == id)
            item = i;

    if (!item) {
        std::cout << "Элемент не найден.\n";
        return;
    }

    std::cout << "Найден объект:\n" << item->getInfo() << "\n\n";

    // Определяем тип
    auto* note     = dynamic_cast<Note*>(item);
    auto* event    = dynamic_cast<Event*>(item);
    auto* reminder = dynamic_cast<Reminder*>(item);

    std::cout << "Что вы хотите изменить?\n";
    int choice = 0;

    if (note) {
        std::cout << "1. Заголовок\n";
        std::cout << "2. Текст\n";
        choice = InputManager::inputInt("Выбор: ", 1, 2);
    }
    else if (event) {
        std::cout << "1. Заголовок\n";
        std::cout << "2. Дата\n";
        choice = InputManager::inputInt("Выбор: ", 1, 2);
    }
    else if (reminder) {
        std::cout << "1. Заголовок\n";
        std::cout << "2. Дата\n";
        std::cout << "3. Время\n";
        choice = InputManager::inputInt("Выбор: ", 1, 3);
    }

    Command* cmd = nullptr;

    switch (choice)
    {
        case 1: // Title
        {
            std::string newTitle = InputManager::inputString("Новый заголовок: ");
            cmd = new EditTitleCommand(item,
                    dynamic_cast<DataComponent*>(item)->getTitle(),
                    newTitle);
            break;
        }

        case 2:
        {
            if (note) {
                std::string newText = InputManager::inputString("Новый текст: ");
                cmd = new EditTextCommand(note, note->getText(), newText);
            }
            else {
                std::cout << "Дата:" << "\n";
                int d {0}, m {0}, y {0};
                while (true) {
                    d = InputManager::inputInt("День: ", 1, 31);
                    m = InputManager::inputInt("Месяц: ", 1, 12);
                    y = InputManager::inputInt("Год: ", 1900, 3000);

                    if (InputManager::isValidDate(d, m, y))
                        break;
                    std::cout << "Неверная дата\nПроверьте не поставили ли Вы:\n -прошедшую дату\n -несуществующую дату\n -дату после 3000 года" << std::endl;
                }
                cmd = new EditDateCommand(item, item->getDate(), (std::to_string(d) + "." + std::to_string(m) + "." + std::to_string(y)));
            }
            break;
        }

        case 3: // only for reminder
        {
            std::cout << "Введите новое время (HH:MM): ";
            std::string time;
            do
            {
                time = InputManager::inputString("Время оповещения: ");
            }while (!InputManager::isValidTime(time));
            cmd = new EditTimeCommand(reminder, reminder->getTime(), time);
            break;
        }
        default: break;
    }

    if (cmd) {
        cmd->execute(*this);
        history.push_back(cmd);
    }
}

void Diary::clear()
{
    Command* cmd = new ClearCommand();
    cmd->execute(*this);
    history.push_back(cmd);
}

void Diary::undo()
{
    if (history.empty())
        return;
    Command* cmd = history.back();
    history.pop_back();
    cmd->undo(*this);
    delete cmd;
}

void Diary::addInternal(BaseComponent* item)
{
    items.push_back(item);
}

void Diary::removeInternal(int id)
{
    items.erase(
        std::remove_if(items.begin(), items.end(),
            [&](BaseComponent* i){ return i->getId() == id; }),
        items.end()
    );
}

void Diary::editInternal(int id, const std::string& newTitle) {
    for (auto* i : items)
        if (i->getId() == id)
            dynamic_cast<DataComponent*>(i)->setTitle(newTitle);
}

void Diary::clearInternal()
{
    for (auto* item : items)
        delete item;

    items.clear();
}


void Diary::list() const {
    for (auto* i : items)
        std::cout << i->getInfo() << "\n";
}

void Diary::showReminder()
{
    time_t currentTime = time(nullptr);
    struct tm *localTime = localtime(&currentTime);

    int yearCur  = localTime->tm_year + 1900;
    int monthCur = localTime->tm_mon + 1;
    int dayCur   = localTime->tm_mday;

    int hourCur   = localTime->tm_hour;
    int minuteCur = localTime->tm_min;

    for (auto* i : items)
    {
        auto* r = dynamic_cast<Reminder*>(i);
        if (!r)
            continue;

        int day   = 0;
        int month = 0;
        int year  = 0;

        {
            std::stringstream ss(r->getDate());
            char dot1, dot2;
            ss >> day >> dot1 >> month >> dot2 >> year;
            if (!ss || dot1 != '.' || dot2 != '.')
                continue;
        }

        int hour = 0;
        int minute = 0;

        {
            std::stringstream ss(r->getTime());
            char colon;
            ss >> hour >> colon >> minute;
            if (!ss || colon != ':')
                continue;
        }

        if (day == dayCur && month == monthCur && year == yearCur)
        {
            bool passed =
                (hour < hourCur) ||
                (hour == hourCur && minute <= minuteCur);

            if (passed)
                std::cout << r->getInfo() << "\n";
        }
    }
}

