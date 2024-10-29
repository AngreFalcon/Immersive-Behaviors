#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "Behavior.hpp"

class BehaviorMap {
public:
    BehaviorMap() = default;
    ~BehaviorMap() = default;
    
    template <typename T>
    inline void insert() {
        if (!behaviorMap.contains(std::type_index(typeid(T)))) {
            behaviorMap[std::type_index(typeid(T))] = std::make_unique<T>();
        }
        return;
    }

    template <typename T>
    inline T* get() noexcept {
        return dynamic_cast<T*>(behaviorMap.at(std::type_index(typeid(T))).get());
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<Behavior>> behaviorMap;
};
