#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "Behavior.hpp"

class BehaviorMap {
public:
    BehaviorMap() = default;
    ~BehaviorMap() = default;
    
    /**
     * @brief Used to insert a new behavior into the event's behavior map via class name.
     * 
     * @tparam T Child of Behavior class.
     */
    template <typename T>
    inline void insert() {
        if (!behaviorMap.contains(std::type_index(typeid(T)))) {
            behaviorMap[std::type_index(typeid(T))] = std::make_unique<T>();
        }
        return;
    }

    /**
     * @brief Used to retrieve a pointer to the specified child object from our map of parent class pointers
     * 
     * @tparam T Child of Behavior class.
     * @return T* Pointer to object of Behavior child class.
     */
    template <typename T>
    inline T* get() noexcept {
        return dynamic_cast<T*>(behaviorMap.at(std::type_index(typeid(T))).get());
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<Behavior>> behaviorMap;

};
