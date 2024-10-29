#include "ImmersiveMovementSpeed.hpp"
#include "helpers.hpp"

ImmersiveMovementSpeed::ImmersiveMovementSpeed(void) {
    walkModeActive = false;
    enableBehavior();
}

void ImmersiveMovementSpeed::makePlayerWalk(void) {
    if (!isEnabled()) {
        return;
    }
    RE::PlayerControls::GetSingleton()->data.running = false;
    walkModeActive = true;
    return;
}

void ImmersiveMovementSpeed::makePlayerRun(void) {
    if (!isEnabled()) {
        return;
    }
    RE::PlayerControls::GetSingleton()->data.running = true;
    walkModeActive = false;
    return;
}

void ImmersiveMovementSpeed::makePlayerRunWhenSprint(void) {
    if (!isEnabled()) {
        return;
    }
    RE::PlayerControls::GetSingleton()->data.running = true;
    return;
}

bool ImmersiveMovementSpeed::isWalkModeActive(void) {
    return walkModeActive;
}