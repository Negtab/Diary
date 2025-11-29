cmake_minimum_required(VERSION 4.0)
project(Diary)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


add_executable(Diary main.cpp
        MainTypes/Event.h
        MainTypes/BaseComponent.h
        MainTypes/DataComponent.h
        MainTypes/Note.h
        MainTypes/Reminder.h
        Commands/Command.h
        Commands/AddCommand.h
        Commands/DeleteCommand.h
        Commands/EditTitleCommand.h
        Diary.h
        Diary.cpp
        Managers/SecurityManager.cpp
        Managers/SecurityManager.h
        Calendar.cpp
        Calendar.h
        Managers/StorageManager.cpp
        Managers/StorageManager.h
        Managers/InputManager.h
        Managers/InputManager.cpp
        Commands/ClearCommand.h
        Commands/EditTextCommand.h
        Commands/EditTextCommand.h
        Commands/EditDateCommand.h
        Commands/EditTimeCommand.h
        Managers/Factory.h
)
