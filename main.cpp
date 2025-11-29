#include <iostream>
#include <windows.h>
#include "Calendar.h"
#include "Diary.h"
#include "MainTypes/Note.h"
#include "MainTypes/Event.h"
#include "MainTypes/Reminder.h"
#include "Managers/Factory.h"
#include "Managers/SecurityManager.h"
#include "Managers/InputManager.h"
#include "Managers/StorageManager.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    SecurityManager sec;
    sec.loadPassword();

    if (!sec.login())
    {
        std::cout << "Неверный логин или пароль.\n";
        return 0;
    }

    Diary diary;
    bool isExit = false;
    do
    {
        std::cout
        << "+------------------------------+\n"
        << "|            Меню              |\n"
        << "+------------------------------+\n"
        << "| 1. Добавить заметку          |\n"
        << "| 2. Добавить событие          |\n"
        << "| 3. Добавить напоминание      |\n"
        << "+------------------------------+\n"
        << "| 4. Показать все              |\n"
        << "| 5. Удалить                   |\n"
        << "| 6. Изменить                  |\n"
        << "| 7. Отменить действие         |\n"
        << "+------------------------------+\n"
        << "| 8. Календарь                 |\n"
        << "| 9. Изменить логин            |\n"
        << "| 10. Изменить пароль          |\n"
        << "+------------------------------+\n"
        << "| Перед загрузкой данные       |\n"
        << "| будут стерты                 |\n"
        << "+------------------------------+\n"
        << "| 11. Сохранить зашифровано    |\n"
        << "| 12. Загрузить зашифровано    |\n"
        << "| 13. Сохранить текстом        |\n"
        << "| 14. Загрузить текстом        |\n"
        << "+------------------------------+\n"
        << "| 0. Выход                     |\n"
        << "+------------------------------+\n";

        switch (InputManager::inputInt("Выбор: ", 0, 13))
        {
            case 0: isExit = true; break;
            case 1:
            {
                system("cls");

                int id = InputManager::inputInt("ID: ", 0, 9999);
                std::string title = InputManager::inputString("Заголовок: ");
                std::string text = InputManager::inputString("Текст: ");
                diary.add(makeItem<Note>(id, title, text));
                break;
            }
            case 2:
            {
                system("cls");

                int id = InputManager::inputInt("ID: ", 0, 9999);
                std::string title = InputManager::inputString("Заголовок: ");

                std::cout << "Дата:" << "\n";
                int d {0}, m {0}, y {0};
                while (true)
                {
                    d = InputManager::inputInt("День: ", 1, 31);
                    m = InputManager::inputInt("Месяц: ", 1, 12);
                    y = InputManager::inputInt("Год: ", 1900, 3000);

                    if (InputManager::isValidDate(d, m, y))
                        break;
                    std::cout << "Неверная дата\nПроверьте не поставили ли Вы:\n -прошедшую дату\n -несуществующую дату\n -дату после 3000 года" << std::endl;
                }

                diary.add(makeItem<Event>(id, title, (std::to_string(d) + "." + std::to_string(m) + "." + std::to_string(y))));
                break;
            }
            case 3:
            {
                system("cls");

                int id = InputManager::inputInt("ID: ", 0, 9999);
                std::string title = InputManager::inputString("Заголовок: ");

                std::cout << "Дата:" << "\n";
                int d {0}, m {0}, y {0};
                while (true)
                {
                    d = InputManager::inputInt("День: ", 1, 31);
                    m = InputManager::inputInt("Месяц: ", 1, 12);
                    y = InputManager::inputInt("Год: ", 1900, 3000);

                    if (InputManager::isValidDate(d, m, y))
                        break;
                    std::cout << "Неверная дата\nПроверьте не поставили ли Вы:\n -прошедшую дату\n -несуществующую дату\n -дату после 3000 года" << std::endl;
                }

                std::string time;
                do
                {
                    time = InputManager::inputString("Время оповещения: ");
                }while (!InputManager::isValidTime(time));

                diary.add(makeItem<Reminder>(id, title, (std::to_string(d) + "." + std::to_string(m) + "." + std::to_string(y)),time));
                break;
            }
            case 4:
            {
                system("cls");

                diary.list();
                break;
            }
            case 5:
            {
                system("cls");

                int id = InputManager::inputInt("ID: ", 0, 9999);
                diary.remove(id);

                break;
            }
            case 6:
            {
                system("cls");

                int id = InputManager::inputInt("ID: ", 0, 9999);
                diary.edit(id);

                break;
            }
            case 7:
            {
                system("cls");

                diary.undo();
                break;
            }
            case 8:
            {
                system("cls");

                int month = InputManager::inputInt("Месяц: ", 0, 12);
                int year = InputManager::inputInt("Год: ", 1900, 3000);

                Calendar::printMonth(month,year, diary.items);
                break;
            }
            case 9:
            {
                system("cls");

                sec.changeName();

                break;
            }
            case 10:
            {
                system("cls");

                sec.changePassword();

                break;
            }
            case 11:
            {
                system("cls");

                std::string pathToFile = InputManager::inputString("Введите путь к файлу: ");
                StorageManager::save(diary.items, pathToFile);

                break;
            }
            case 12:
            {
                system("cls");


                std::string pathToFile = InputManager::inputString("Введите путь к файлу: ");
                diary.clear();
                StorageManager::load(diary.items, pathToFile);

                break;
            }

            case 13:
            {
                system("cls");

                std::string pathToFile = InputManager::inputString("Введите путь к файлу: ");
                StorageManager::saveTxt(diary.items, pathToFile);

                break;
            }
            case 14:
            {
                system("cls");

                std::string pathToFile = InputManager::inputString("Введите путь к файлу: ");
                diary.clear();
                StorageManager::loadTxt(diary.items, pathToFile);

                break;
            }
            default: break;
        }
    }while (!isExit);
    return 0;
}
