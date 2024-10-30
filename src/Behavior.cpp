#include "Behavior.hpp"

void IBConfig::setEnabled(const bool enableBehavior) {
    this->enabled = enableBehavior;
    return;
}

bool IBConfig::isEnabled(void) {
    return this->enabled;
}