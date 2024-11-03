#include "ImmersiveMovementSpeed.hpp"
#include "Config.hpp"
#include "helpers.hpp"

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
	nlohmann_json_t.alwaysRespectMoveSpeedToggle = nlohmann_json_j.value("alwaysRespectMoveSpeedToggle", nlohmann_json_default_obj.alwaysRespectMoveSpeedToggle);
	return;
}

ImmersiveMovementSpeed::ImmersiveMovementSpeed(void) {
	this->debugLogging<decltype(this)>();
    this->config = Config::get<IMSConfig>("immersiveMovementSpeed");
    this->immersiveWalkModeActive = false;
}

void ImmersiveMovementSpeed::updateImmersiveBehavior(void) {
	if (!this->config.isEnabled()) {
		return;
	}
	this->updateTempState();
	this->changeMoveSpeed(static_cast<bool>(this->config.contextMap[this->getActiveState()]));
	return;
}

void ImmersiveMovementSpeed::toggleMoveSpeed(void) {
	if (!this->config.isEnabled()) {
		return;
	}
	this->moveSpeedToggled = !this->moveSpeedToggled;
	std::string msg = this->moveSpeedToggled ? "Move speed toggle on" : "Move speed toggle off";
    RE::DebugNotification(msg.c_str());
	return;
}

void ImmersiveMovementSpeed::sprintKeyPressed(void) {
	if (!this->config.isEnabled()) {
		return;
	}
    if (helpers::isPlayerWalking()) {
        controls::GetSingleton()->data.running = true;
    }
    return;
}

void ImmersiveMovementSpeed::sprintKeyReleased(void) {
	if (!this->config.isEnabled()) {
		return;
	}
    if (immersiveWalkModeActive) {
		controls::GetSingleton()->data.running = false;
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
    this->immersiveWalkModeActive = (!run != (this->moveSpeedToggled && (!this->isActiveStateTemp() || this->config.alwaysRespectMoveSpeedToggle)));
    controls::GetSingleton()->data.running = !this->immersiveWalkModeActive;
    return;
}

// this function currently doesn't work
void ImmersiveMovementSpeed::stopSprinting(void) {
    player::GetSingleton()->AsActorState()->actorState1.sprinting = !player::GetSingleton()->AsActorState()->IsSprinting();
    return;
}