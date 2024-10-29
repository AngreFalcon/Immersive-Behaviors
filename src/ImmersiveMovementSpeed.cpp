#include "ImmersiveMovementSpeed.hpp"
#include "Config.hpp"
#include "helpers.hpp"
#include <algorithm>

void IMSConfig::setEnabled(bool enabled) {
    this->enabled = enabled;
    return;
}
bool IMSConfig::isEnabled(void) {
    return this->enabled;
}

void from_json(const nlohmann::json& nlohmann_json_j, IMSConfig& nlohmann_json_t) {
    IMSConfig nlohmann_json_default_obj;
    nlohmann_json_t.setEnabled(nlohmann_json_j.value("enabled", nlohmann_json_default_obj.isEnabled()));
}

ImmersiveMovementSpeed::ImmersiveMovementSpeed(void) {
    logs::debug("constructing ImmersiveMovementSpeed");
    config = Config::get<IMSConfig>("immersiveMovementSpeed");
    logs::debug("Is behavior enabled? {}", config.isEnabled());
    walkModeActive = false;
}

void ImmersiveMovementSpeed::contextualMoveSpeed(const std::string& context) {
    if (!config.isEnabled()) {
        return;
    }
    // todo: make sure config[key] exists first
    switch (config.contextMap[context]) {
    case MOVE_TYPE::WALK:
        makePlayerWalk();
        break;
    case MOVE_TYPE::RUN:
        makePlayerRun();
        break;
    default:
        break;
    }
    return;
}

void ImmersiveMovementSpeed::makePlayerWalk(void) {
    if (!config.isEnabled()) {
        return;
    }
    RE::PlayerControls::GetSingleton()->data.running = false;
    walkModeActive = true;
    return;
}

void ImmersiveMovementSpeed::makePlayerRun(void) {
    if (!config.isEnabled()) {
        return;
    }
    RE::PlayerControls::GetSingleton()->data.running = true;
    walkModeActive = false;
    return;
}

void ImmersiveMovementSpeed::makePlayerRunWhenSprint(void) {
    if (!config.isEnabled()) {
        return;
    }
    RE::PlayerControls::GetSingleton()->data.running = true;
    return;
}

bool ImmersiveMovementSpeed::isWalkModeActive(void) {
    return walkModeActive;
}

void ImmersiveMovementSpeed::stopSprinting(void) {
    RE::PlayerCharacter::GetSingleton()->AsActorState()->actorState1.sprinting = 0;
    return;
}