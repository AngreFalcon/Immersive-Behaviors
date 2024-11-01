#include "ImmersiveMovementSpeed.hpp"
#include "Config.hpp"
#include "helpers.hpp"
#include <algorithm>

void IMSConfig::initializeToDefault(void) {
	for (const std::string keyword : this->keywordList) {
		this->contextMap[keyword] = MOVE_TYPE::DISABLED;
	}
	return;
}

void from_json(const nlohmann::json& nlohmann_json_j, IMSConfig& nlohmann_json_t) {
    IMSConfig nlohmann_json_default_obj;
    nlohmann_json_t.contextMap = nlohmann_json_default_obj.contextMap;
    for (const std::string& context : nlohmann_json_j["walk"].get<std::vector<std::string>>()) {
        nlohmann_json_t.contextMap[context] = MOVE_TYPE::WALK;
        logs::debug("\tSuccessfully parsed: {} as: Walk", context);
    }
    for (const std::string& context : nlohmann_json_j["run"].get<std::vector<std::string>>()) {
        nlohmann_json_t.contextMap[context] = MOVE_TYPE::RUN;
        logs::debug("\tSuccessfully parsed: {} as: Run", context);
    }
    nlohmann_json_t.setEnabled(nlohmann_json_j.value("enabled", nlohmann_json_default_obj.isEnabled()));
}

ImmersiveMovementSpeed::ImmersiveMovementSpeed(void) {
    logs::debug("");
    logs::debug("constructing ImmersiveMovementSpeed");
    this->config = Config::get<IMSConfig>("immersiveMovementSpeed");
    logs::debug("\tIs ImmersiveBehavior enabled? {}", this->config.isEnabled());
    this->immersiveWalkModeActive = false;
}

void ImmersiveMovementSpeed::updateImmersiveBehavior(void) {
	this->updateTempState();
	const std::string activeState = getActiveState();
	this->changeMoveSpeed(static_cast<bool>(this->config.contextMap[activeState]));
	return;
}

void ImmersiveMovementSpeed::toggleMoveSpeed(void) {
	this->moveSpeedToggled = !this->moveSpeedToggled;
	return;
}

void ImmersiveMovementSpeed::sprintKeyPressed(void) {
    if (!this->config.isEnabled()) {
        return;
    }
    if (helpers::isPlayerWalking()) {
        RE::PlayerControls::GetSingleton()->data.running = true;
    }
    return;
}

void ImmersiveMovementSpeed::sprintKeyReleased(void) {
    if (!this->config.isEnabled()) {
        return;
    }
    if (immersiveWalkModeActive) {
		RE::PlayerControls::GetSingleton()->data.running = false;
    }
    else {
        stopSprinting();
    }
    return;
}

bool ImmersiveMovementSpeed::contextMapContains(const std::string& context) {
	return (this->config.contextMap.contains(context) && this->config.contextMap[context] != MOVE_TYPE::DISABLED);
}

void ImmersiveMovementSpeed::changeMoveSpeed(bool run) {
    if (!this->config.isEnabled()) {
        return;
    }
    this->immersiveWalkModeActive = (!run != this->moveSpeedToggled);
    RE::PlayerControls::GetSingleton()->data.running = !this->immersiveWalkModeActive;
    return;
}

// this function currently doesn't work
void ImmersiveMovementSpeed::stopSprinting(void) {
    RE::PlayerCharacter::GetSingleton()->AsActorState()->actorState1.sprinting = !RE::PlayerCharacter::GetSingleton()->AsActorState()->IsSprinting();
    return;
}