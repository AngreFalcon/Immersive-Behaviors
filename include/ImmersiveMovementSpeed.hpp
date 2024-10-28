#pragma once
#include "Behaviors.hpp"

class ImmersiveMovementSpeed : public Behaviors {
public:
    ImmersiveMovementSpeed(void) = default;
    ~ImmersiveMovementSpeed() = default;

    void makePlayerWalk(void);
    void makePlayerRun(void);
    void makePlayerRunWhenSprint(void);

private:
};