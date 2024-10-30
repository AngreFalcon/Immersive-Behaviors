#include "ImmersiveCameraView.hpp"
#include "Config.hpp"
#include "helpers.hpp"

void ICVConfig::recordZoomLevel() {
    if (!isEnabled() || !helpers::isPlayerInThirdPerson()) {
        return;
    }
    if (helpers::isPlayerInInterior()) {
        interiorZoom = reinterpret_cast<RE::ThirdPersonState*>(RE::PlayerCamera::GetSingleton()->currentState.get())->targetZoomOffset;
    }
    else {
        exteriorZoom = reinterpret_cast<RE::ThirdPersonState*>(RE::PlayerCamera::GetSingleton()->currentState.get())->targetZoomOffset;
    }
    return;
}

void ICVConfig::restoreZoomLevel() {
    if (!isEnabled()) {
        return;
    }
    RE::ThirdPersonState* thirdPersonState = reinterpret_cast<RE::ThirdPersonState*>(RE::PlayerCamera::GetSingleton()->currentState.get());
    // if the player is now in an interior and we're
    // being prompted to restore zoom levels, we should
    // use the interior third person zoom value rather
    // than the exterior value
    if (helpers::isPlayerInInterior()) {
        thirdPersonState->targetZoomOffset = thirdPersonState->savedZoomOffset = thirdPersonState->currentZoomOffset = interiorZoom;
    }
    else {
        thirdPersonState->targetZoomOffset = thirdPersonState->savedZoomOffset = thirdPersonState->currentZoomOffset = exteriorZoom;
    }
    return;
}

void from_json(const nlohmann::json& nlohmann_json_j, ICVConfig& nlohmann_json_t) {
    ICVConfig nlohmann_json_default_obj;
    nlohmann_json_t.contextMap = nlohmann_json_default_obj.contextMap;
    for (const std::string& context : nlohmann_json_j["firstPerson"].get<std::vector<std::string>>()) {
        nlohmann_json_t.contextMap[context] = VIEW_TYPE::FIRST_PERSON;
        logs::debug("\tSuccessfully parsed: {} as: First Person", context);
    }
    for (const std::string& context : nlohmann_json_j["thirdPerson"].get<std::vector<std::string>>()) {
        nlohmann_json_t.contextMap[context] = VIEW_TYPE::THIRD_PERSON;
        logs::debug("\tSuccessfully parsed: {} as: Third Person", context);
    }
    nlohmann_json_t.interiorZoom = nlohmann_json_j.value("interiorZoom", nlohmann_json_default_obj.interiorZoom);
    nlohmann_json_t.exteriorZoom = nlohmann_json_j.value("exteriorZoom", nlohmann_json_default_obj.exteriorZoom);
    nlohmann_json_t.setEnabled(nlohmann_json_j.value("enabled", nlohmann_json_default_obj.isEnabled()));
}

ImmersiveCameraView::ImmersiveCameraView(void) {
    logs::debug("");
    logs::debug("constructing ImmersiveCameraView");
    // -0.2 is set as the default, which places
    // the camera just behind the player character
    config = Config::get<ICVConfig>("immersiveCameraView");
    for (const auto& context : config.contextMap) {
        logs::debug("\tcontext: {} -> {}", context.first, static_cast<bool>(context.second) ? "thirdPerson" : "firstPerson");
    }
    logs::debug("\tIs behavior enabled? {}", config.isEnabled());
}

void ImmersiveCameraView::shiftCameraPerspective(const std::string& context) {
    if (!config.isEnabled()) {
        return;
    }
    // todo: make sure config[key] exists first
    switch (config.contextMap[context]) {
    case VIEW_TYPE::FIRST_PERSON:
        shiftCameraPerspectiveToFirstPerson();
        break;
    case VIEW_TYPE::THIRD_PERSON:
        shiftCameraPerspectiveToThirdPerson();
        break;
    default:
        break;
    }
    return;
}

void ImmersiveCameraView::shiftCameraPerspectiveToFirstPerson(void) {
    RE::PlayerCamera::GetSingleton()->ForceFirstPerson();
    return;
}

void ImmersiveCameraView::shiftCameraPerspectiveToThirdPerson(void) {
    RE::PlayerCamera::GetSingleton()->ForceThirdPerson();
    config.restoreZoomLevel();
    return;
}