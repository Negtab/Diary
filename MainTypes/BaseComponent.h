#ifndef DIARY_BASECOMPONENT_H
#define DIARY_BASECOMPONENT_H

#include <string>

class BaseComponent {
protected:
    int id;
public:
    explicit BaseComponent(int id) : id(id) {}
    virtual ~BaseComponent() = default;

    [[nodiscard]] virtual BaseComponent* clone() const = 0;
    [[nodiscard]] int getId() const { return id; }

    [[nodiscard]] virtual std::string getDate() const { return ""; }
    virtual void setDate(const std::string&) {}

    [[nodiscard]] virtual std::string getInfo() const = 0;
};

#endif //DIARY_BASECOMPONENT_H