#include "ButtonPressEvent.hpp"
#include "helpers.hpp"
#include "ImmersiveMovementSpeed.hpp"

ButtonPressEvent::ButtonPressEvent(const std::shared_ptr<ImmersiveBehaviorMap> immersiveBehaviors) {
    this->immersiveBehaviors = immersiveBehaviors;
}

RE::BSEventNotifyControl ButtonPressEvent::ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*) {
    if (!a_event || !*a_event) {
        return RE::BSEventNotifyControl::kContinue;
    }
    if (const RE::ButtonEvent* buttonEvent = (*a_event)->AsButtonEvent()) {
        this->initializeKeyCodes(buttonEvent);
        if (helpers::doesPlayerExist()) this->routeButtonEvents(buttonEvent);
    }
    return RE::BSEventNotifyControl::kContinue;
}

void ButtonPressEvent::initializeKeyCodes(const RE::ButtonEvent* buttonEvent) {
	static constexpr std::array keyNames = {"Sprint", "Toggle Always Run", "Ready Weapon", "Zoom In", "Zoom Out", "Toggle POV" };
	for (std::string keyName : keyNames) {
		this->buttonCodes[keyName] = RE::ControlMap::GetSingleton()->GetMappedKey(keyName, buttonEvent->GetDevice());
	}
    return;
}

void ButtonPressEvent::routeButtonEvents(const RE::ButtonEvent* buttonEvent) {
	if (buttonEvent->GetIDCode() == -1) {
		return;
	}
    if (buttonEvent->GetIDCode() == this->buttonCodes["Sprint"]) {
        this->sprintKeyEvent(buttonEvent);
    }
    else if (buttonEvent->GetIDCode() == this->buttonCodes["Toggle Always Run"]) {
        this->toggleRunKeyEvent(buttonEvent);
    }
    else if (buttonEvent->GetIDCode() == this->buttonCodes["Ready Weapon"]) {
        this->readyWeaponKeyEvent(buttonEvent);
    }
	else if (buttonEvent->GetIDCode() == this->buttonCodes["Zoom In"] || buttonEvent->GetIDCode() == this->buttonCodes["Zoom Out"]) {
		// unfortunately only executes if not receiving any other input
		// unless a workaround is found, we instead record our zoom level with each and every input
		//this->zoomKeyEvent(buttonEvent);
	}
	else if (buttonEvent->GetIDCode() == this->buttonCodes["Toggle POV"]) {
		this->togglePOVKeyEvent(buttonEvent);
	}
	this->immersiveBehaviors->get<ImmersiveCameraView>()->config.recordZoomLevel();
    return;
}

void ButtonPressEvent::sprintKeyEvent(const RE::ButtonEvent* buttonEvent) {
    if (buttonEvent->IsPressed() || buttonEvent->IsHeld()) {
        this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->sprintKeyPressed();
    }
    else if (buttonEvent->IsUp()) {
        this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->sprintKeyReleased();
    }
    return;
}

void ButtonPressEvent::toggleRunKeyEvent(const RE::ButtonEvent* buttonEvent) {
    if (buttonEvent->IsPressed()) {
        this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->toggleMoveSpeed();
		this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->updateImmersiveBehavior();
    }
    return;
}

void ButtonPressEvent::readyWeaponKeyEvent(const RE::ButtonEvent* buttonEvent) {
    if (buttonEvent->IsPressed()) {
        this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->updateImmersiveBehavior();
        this->immersiveBehaviors->get<ImmersiveCameraView>()->updateImmersiveBehavior();
    }
    return;
}

void ButtonPressEvent::zoomKeyEvent(const RE::ButtonEvent* buttonEvent) {
	if (buttonEvent->IsPressed()) {
		this->immersiveBehaviors->get<ImmersiveCameraView>()->config.recordZoomLevel();
	}
	return;
}

void ButtonPressEvent::togglePOVKeyEvent(const RE::ButtonEvent* buttonEvent) {
	if (buttonEvent->IsUp()) {
		this->immersiveBehaviors->get<ImmersiveCameraView>()->togglePOV();
		this->immersiveBehaviors->get<ImmersiveCameraView>()->updateImmersiveBehavior();
	}
	return;
}