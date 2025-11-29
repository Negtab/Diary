#ifndef DIARY_DATECOMPONENT_H
#define DIARY_DATECOMPONENT_H

#include "BaseComponent.h"
#include <string>

class DataComponent : public BaseComponent
{
protected:
    std::string title;
public:
    DataComponent(int id, const std::string& title)  : BaseComponent(id), title(title) {}

    void setTitle(const std::string& t) { title = t; }
    [[nodiscard]] std::string getTitle() const { return title; }
};


#endif //DIARY_DATECOMPONENT_H