#include "ImmersiveCameraView.hpp"
#include "Config.hpp"
#include "helpers.hpp"

void ICVConfig::recordZoomLevel() {
    if (!isEnabled() || !helpers::isPlayerInThirdPerson()) {
        return;
    }
    (helpers::isPlayerInInterior() ? this->interiorZoom : this->exteriorZoom) = reinterpret_cast<RE::ThirdPersonState*>(camera::GetSingleton()->currentState.get())->targetZoomOffset;
    return;
}

void ICVConfig::restoreZoomLevel() {
    if (!isEnabled() || !helpers::isPlayerInThirdPerson()) {
        return;
    }
    RE::ThirdPersonState* thirdPersonState = reinterpret_cast<RE::ThirdPersonState*>(camera::GetSingleton()->currentState.get());
	float zoomValue = (helpers::isPlayerInInterior() ? this->interiorZoom : this->exteriorZoom);
	zoomValue = (zoomValue < -0.2f ? -0.2f : (zoomValue > 1.0f ? 1.0f : zoomValue));
    thirdPersonState->targetZoomOffset = thirdPersonState->savedZoomOffset = thirdPersonState->currentZoomOffset = zoomValue;
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
	nlohmann_json_t.alwaysRespectPOVToggle = nlohmann_json_j.value("alwaysRespectPOVToggle", nlohmann_json_default_obj.alwaysRespectPOVToggle);
	return;
}

ImmersiveCameraView::ImmersiveCameraView(void) {
	this->debugLogging<decltype(this)>();
    this->config = Config::get<ICVConfig>("immersiveCameraView");
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
	std::string msg = this->povToggled ? "POV toggle on" : "POV toggle off";
    RE::DebugNotification(msg.c_str());
	return;
}

bool ImmersiveCameraView::contextMapContains(const std::string& context) {
	return (this->config.contextMap.contains(context) && this->config.contextMap[context] != VIEW_TYPE::DISABLED);
}

void ImmersiveCameraView::shiftCameraPerspective() {
	VIEW_TYPE viewType = static_cast<VIEW_TYPE>(static_cast<int>(config.contextMap[getActiveState()]) ^ (povToggled && (!this->isActiveStateTemp() || this->config.alwaysRespectPOVToggle)));
	// only respect player's POV toggle if we're not in a temp state (e.g., in combat, swimming, etc.)
	// unless the player has enabled alwaysRespectPOVToggle in their config
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
    camera::GetSingleton()->ForceFirstPerson();
    return;
}

void ImmersiveCameraView::shiftCameraPerspectiveToThirdPerson(void) {
    camera::GetSingleton()->ForceThirdPerson();
    this->config.restoreZoomLevel();
    return;
}