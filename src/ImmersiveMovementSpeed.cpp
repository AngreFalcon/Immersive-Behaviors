#include "ImmersiveMovementSpeed.hpp"
#include "helpers.hpp"

void ImmersiveMovementSpeed::makePlayerWalk(void) {
    if (!isEnabled()) {
        return;
    }
    if (helpers::isPlayerWalking()) {
        return;
    }
    RE::PlayerControls::GetSingleton()->data.running = false;
    return;
}

void ImmersiveMovementSpeed::makePlayerRun(void) {
    if (!isEnabled()) {
        return;
    }
    if (!helpers::isPlayerWalking()) {
        return;
    }
    RE::PlayerControls::GetSingleton()->data.running = true;
    return;
}

void ImmersiveMovementSpeed::makePlayerRunWhenSprint(void) {
    if (!isEnabled()) {
        return;
    }
    // when the player holds their sprint key while walking, they'll run instead
    return;
}