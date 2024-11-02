#pragma once
#include <typeindex>
#include "ImmersiveBehavior.hpp"

class ImmersiveBehaviorMap {
public:
    ImmersiveBehaviorMap(void) = default;
    ~ImmersiveBehaviorMap() = default;
    
    /**
     * @brief Inserts a new ImmersiveBehavior into the event's ImmersiveBehaviorMap via class name.
     * 
     * @tparam T Child of ImmersiveBehavior class.
     */
    template <typename T>
    inline void insert(void) {
        if (!this->immersiveBehaviorMap.contains(std::type_index(typeid(T)))) {
            this->immersiveBehaviorMap[std::type_index(typeid(T))] = std::make_unique<T>();
        }
        return;
    }

    /**
     * @brief Retrieves a pointer to the specified child object from our map of parent class pointers.
     * 
     * @tparam T Child of ImmersiveBehavior class.
     * @return T* Pointer to object of ImmersiveBehavior child class.
     */
    template <typename T>
    inline T* get(void) noexcept {
        return dynamic_cast<T*>(this->immersiveBehaviorMap.at(std::type_index(typeid(T))).get());
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<ImmersiveBehavior>> immersiveBehaviorMap;

};
