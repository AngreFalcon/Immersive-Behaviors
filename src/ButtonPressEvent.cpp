#include "ButtonPressEvent.hpp"
#include "helpers.hpp"
#include "ImmersiveMovementSpeed.hpp"

ButtonPressEvent::ButtonPressEvent(const std::shared_ptr<ImmersiveBehaviorMap> immersiveBehaviors) {
    this->immersiveBehaviors = immersiveBehaviors;
}

RE::BSEventNotifyControl ButtonPressEvent::ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*) {
    if (!a_event) {
        return RE::BSEventNotifyControl::kContinue;
    }
    for (RE::InputEvent* event = *a_event; event; event = event->next) {
        if (const RE::ButtonEvent* buttonEvent = event->AsButtonEvent()) {
            this->initializeKeyCodes(buttonEvent);
            this->routeButtonEvents(buttonEvent);
        }
        return RE::BSEventNotifyControl::kContinue;
    }
    return RE::BSEventNotifyControl::kContinue;
}

void ButtonPressEvent::initializeKeyCodes(const RE::ButtonEvent* buttonEvent) {
    this->buttonCodes.SprintKey = RE::ControlMap::GetSingleton()->GetMappedKey("Sprint", buttonEvent->GetDevice());
    this->buttonCodes.ToggleRunKey = RE::ControlMap::GetSingleton()->GetMappedKey("Toggle Always Run", buttonEvent->GetDevice());
    this->buttonCodes.UnsheathKey = RE::ControlMap::GetSingleton()->GetMappedKey("Ready Weapon", buttonEvent->GetDevice());
    this->buttonCodes.ZoomIn = RE::ControlMap::GetSingleton()->GetMappedKey("Zoom In", buttonEvent->GetDevice());
    this->buttonCodes.ZoomOut = RE::ControlMap::GetSingleton()->GetMappedKey("Zoom Out", buttonEvent->GetDevice());
	this->buttonCodes.TogglePOV = RE::ControlMap::GetSingleton()->GetMappedKey("Toggle POV", buttonEvent->GetDevice());
    return;
}

void ButtonPressEvent::routeButtonEvents(const RE::ButtonEvent* buttonEvent) {
	if (buttonEvent->GetIDCode() == -1) {
		return;
	}
    if (buttonEvent->GetIDCode() == this->buttonCodes.SprintKey) {
        this->sprintKeyEvent(buttonEvent);
    }
    else if (buttonEvent->GetIDCode() == this->buttonCodes.ToggleRunKey) {
        this->toggleRunKeyEvent(buttonEvent);
    }
    else if (buttonEvent->GetIDCode() == this->buttonCodes.UnsheathKey) {
        this->readyWeaponEvent(buttonEvent);
    }
	else if (buttonEvent->GetIDCode() == this->buttonCodes.ZoomIn || buttonEvent->GetIDCode() == this->buttonCodes.ZoomOut) {
		// unfortunately only executes if not receiving any other input
		// unless a workaround is found, we instead record our zoom level with each and every input
		//this->cameraZoom(buttonEvent);
	}
	else if (buttonEvent->GetIDCode() == this->buttonCodes.TogglePOV) {
		this->POVToggled(buttonEvent);
	}
	this->immersiveBehaviors->get<ImmersiveCameraView>()->config.recordZoomLevel();
    return;
}

void ButtonPressEvent::sprintKeyEvent(const RE::ButtonEvent* buttonEvent) {
    if (buttonEvent->IsDown()) {
        this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->sprintKeyPressed();
    }
    else {
        this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->sprintKeyReleased();
    }
    return;
}

void ButtonPressEvent::toggleRunKeyEvent(const RE::ButtonEvent* buttonEvent) {
    if (buttonEvent->IsDown()) {
        this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->toggleMoveSpeed();
		this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->updateImmersiveBehavior();
    }
    else if (buttonEvent->IsUp()) { }
    return;
}

void ButtonPressEvent::readyWeaponEvent(const RE::ButtonEvent* buttonEvent) {
    if (buttonEvent->IsDown()) {
        this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->updateImmersiveBehavior();
        this->immersiveBehaviors->get<ImmersiveCameraView>()->updateImmersiveBehavior();
    }
    else if (buttonEvent->IsUp()) { }
    return;
}

void ButtonPressEvent::cameraZoom(const RE::ButtonEvent*) {
	this->immersiveBehaviors->get<ImmersiveCameraView>()->config.recordZoomLevel();
    RE::DebugNotification(std::to_string(reinterpret_cast<RE::ThirdPersonState*>(RE::PlayerCamera::GetSingleton()->currentState.get())->targetZoomOffset).c_str());
	return;
}

void ButtonPressEvent::POVToggled(const RE::ButtonEvent* buttonEvent) {
	if (buttonEvent->IsDown()) { }
	else if (buttonEvent->IsUp()) {
		this->immersiveBehaviors->get<ImmersiveCameraView>()->config.restoreZoomLevel();
	}
	return;
}