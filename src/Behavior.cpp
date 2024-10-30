#include "Behavior.hpp"

void IBConfig::setEnabled(bool enabled) {
    this->enabled = enabled;
    return;
}

bool IBConfig::isEnabled(void) {
    return this->enabled;
}