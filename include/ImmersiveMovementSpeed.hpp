#pragma once
#include "Behaviors.hpp"

class ImmersiveMovementSpeed : public Behaviors {
public:
    ImmersiveMovementSpeed(void);
    ~ImmersiveMovementSpeed() = default;

    void makePlayerWalk(void);
    void makePlayerRun(void);
    void makePlayerRunWhenSprint(void);
    bool isWalkModeActive(void);

private:
    bool walkModeActive;
};