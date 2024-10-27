#pragma once

#include "IBEvent.hpp"

class PlayerCellChangeEvent : IBEvent {
public:
    PlayerCellChangeEvent() = default;
    ~PlayerCellChangeEvent() = default;

    static bool isPlayerInInterior();

private:
    
};