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
    config = Config::get<IMSConfig>("immersiveMovementSpeed");
    logs::debug("\tIs behavior enabled? {}", config.isEnabled());
    immersiveWalkModeActive = false;
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
    immersiveWalkModeActive = true;
    return;
}

void ImmersiveMovementSpeed::makePlayerRun(void) {
    if (!config.isEnabled()) {
        return;
    }
    RE::PlayerControls::GetSingleton()->data.running = true;
    immersiveWalkModeActive = false;
    return;
}

void ImmersiveMovementSpeed::sprintKeyPressed(void) {
    if (!config.isEnabled()) {
        return;
    }
    if (helpers::isPlayerWalking()) {
        RE::PlayerControls::GetSingleton()->data.running = true;
        //logs::info("Start running");
    }
    return;
}

void ImmersiveMovementSpeed::sprintKeyReleased(void) {
    if (!config.isEnabled()) {
        return;
    }
    if (immersiveWalkModeActive) {
        makePlayerWalk();
        //logs::info("Stop running");
    }
    else {
        //stopSprinting();
        //logs::info("Stop sprinting");
    }
    return;
}

// this function currently doesn't work
void ImmersiveMovementSpeed::stopSprinting(void) {
    RE::PlayerCharacter::GetSingleton()->AsActorState()->actorState1.sprinting = !RE::PlayerCharacter::GetSingleton()->AsActorState()->IsSprinting();
    return;
}