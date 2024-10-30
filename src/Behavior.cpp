#include "Behavior.hpp"

void IBConfig::setEnabled(bool enableBehavior) {
    this->enabled = enableBehavior;
    return;
}

bool IBConfig::isEnabled(void) {
    return this->enabled;
}