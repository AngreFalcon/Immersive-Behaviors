#include "ImmersiveBehavior.hpp"
#include "helpers.hpp"

void IBConfig::setEnabled(const bool enableImmersiveBehavior) {
    this->enabled = enableImmersiveBehavior;
    return;
}

bool IBConfig::isEnabled(void) {
    return this->enabled;
}

// this makes me want to kill myself
// but, until a better solution is decided upon, this is necessary
void ImmersiveBehavior::updateTempState(void) {
	if (helpers::isPlayerSwimming() && contextMapContains("swimming")) this->tempState = "swimming";
	else if (helpers::isPlayerInCombat() && contextMapContains("combat")) this->tempState = "combat";
	else if (helpers::isPlayerSitting() && contextMapContains("sitting")) this->tempState = "sitting";
	else if (helpers::isPlayerWeaponDrawn() && contextMapContains("weaponDrawn")) this->tempState = "weaponDrawn";
	else if (helpers::isPlayerSneaking() && contextMapContains("sneaking")) this->tempState = "sneaking";
	else if (helpers::isPlayerMounted() && contextMapContains("mounted")) this->tempState = "mounted";
	else if (helpers::isPlayerTrespassing() && contextMapContains("trespassing")) this->tempState = "trespassing";
	else if (helpers::isPlayerInWater() && contextMapContains("inWater")) this->tempState = "inWater";
	else this->tempState = "";
	return;
}

void ImmersiveBehavior::updateCellState(const std::string& newCellState) {
	this->cellState = newCellState;
	return;
}

const std::string ImmersiveBehavior::getActiveState(void) {
	if (this->tempState != "") {
		return this->tempState;
	}
	else {
		return this->cellState;
	}
}

bool ImmersiveBehavior::isActiveStateTemp(void) {
	return this->tempState != "";
}