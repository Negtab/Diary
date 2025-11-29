#ifndef DIARY_FACTORY_H
#define DIARY_FACTORY_H

#include <utility>

template<typename T, typename... Args>
T* makeItem(Args&&... args) {
    return new T(std::forward<Args>(args)...);
}

#endif //DIARY_FACTORY_H