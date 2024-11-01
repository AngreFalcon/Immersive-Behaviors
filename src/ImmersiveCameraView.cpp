#include "ImmersiveCameraView.hpp"
#include "Config.hpp"
#include "helpers.hpp"

void ICVConfig::recordZoomLevel() {
    if (!isEnabled() || !helpers::isPlayerInThirdPerson()) {
        return;
    }
    if (helpers::isPlayerInInterior()) {
        this->interiorZoom = reinterpret_cast<RE::ThirdPersonState*>(RE::PlayerCamera::GetSingleton()->currentState.get())->targetZoomOffset;
    }
    else {
        this->exteriorZoom = reinterpret_cast<RE::ThirdPersonState*>(RE::PlayerCamera::GetSingleton()->currentState.get())->targetZoomOffset;
    }
    return;
}

void ICVConfig::restoreZoomLevel() {
    if (!isEnabled() || !helpers::isPlayerInThirdPerson()) {
        return;
    }
    RE::ThirdPersonState* thirdPersonState = reinterpret_cast<RE::ThirdPersonState*>(RE::PlayerCamera::GetSingleton()->currentState.get());
    // if the player is now in an interior and we're
    // being prompted to restore zoom levels, we should
    // use the interior third person zoom value rather
    // than the exterior value
    if (helpers::isPlayerInInterior()) {
        thirdPersonState->targetZoomOffset = thirdPersonState->savedZoomOffset = thirdPersonState->currentZoomOffset = (this->interiorZoom < -0.2f ? -0.2f : (this->interiorZoom > 1.0f ? 1.0f : this->interiorZoom));
    }
    else {
        thirdPersonState->targetZoomOffset = thirdPersonState->savedZoomOffset = thirdPersonState->currentZoomOffset = (this->exteriorZoom < -0.2f ? -0.2f : (this->exteriorZoom > 1.0f ? 1.0f : this->exteriorZoom));
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
    this->config = Config::get<ICVConfig>("immersiveCameraView");
    for (const std::pair<const std::string, VIEW_TYPE>& context : this->config.contextMap) {
        logs::debug("\tcontext: {} -> {}", context.first, static_cast<bool>(context.second) ? "thirdPerson" : "firstPerson");
    }
    logs::debug("\tIs ImmersiveBehavior enabled? {}", this->config.isEnabled());
}

void ImmersiveCameraView::updateImmersiveBehavior() {
	if (!this->config.isEnabled()) {
		return;
	}
	this->updateTempState();
	this->shiftCameraPerspective();
	return;
}

void ImmersiveCameraView::togglePOV(void) {
	this->povToggled = !this->povToggled;
	return;
}

bool ImmersiveCameraView::contextMapContains(const std::string& context) {
	return (this->config.contextMap.contains(context) && this->config.contextMap[context] != VIEW_TYPE::DISABLED);
}

void ImmersiveCameraView::shiftCameraPerspective() {
	VIEW_TYPE viewType = config.contextMap[getActiveState()];
	if (!this->isActiveStateTemp() && povToggled) {
		viewType = static_cast<VIEW_TYPE>(static_cast<int>(viewType) ^ povToggled);
	}
    switch (viewType) {
    case VIEW_TYPE::FIRST_PERSON:
        this->shiftCameraPerspectiveToFirstPerson();
        break;
    case VIEW_TYPE::THIRD_PERSON:
        this->shiftCameraPerspectiveToThirdPerson();
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
    this->config.restoreZoomLevel();
    return;
}