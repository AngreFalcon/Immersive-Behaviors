#include "Behaviors.hpp"

bool Behaviors::isEnabled(void) {
    return enabled;
}

void Behaviors::enableBehavior(void) {
    enabled = true;
    return;
}

void Behaviors::disableBehavior(void) {
    enabled = false;
    return;
}