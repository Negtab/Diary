//
// Created by User on 28.11.2025.
//

#ifndef DIARY_EDITTEXTCOMMAND_H
#define DIARY_EDITTEXTCOMMAND_H
#include <string>
#include "../Diary.h"
#include "../MainTypes/Note.h"

class EditTextCommand : public Command
{
    Note* note;
    std::string oldText;
    std::string newText;

public:
    EditTextCommand(Note* n, const std::string& o, const std::string& s)
        : note(n), oldText(o), newText(s) {}

    void execute(Diary&) override { note->setText(newText); }
    void undo(Diary&) override { note->setText(oldText); }
};


#endif //DIARY_EDITTEXTCOMMAND_H