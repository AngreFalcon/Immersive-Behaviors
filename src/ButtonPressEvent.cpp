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
    return;
}

void ButtonPressEvent::routeButtonEvents(const RE::ButtonEvent* buttonEvent) {
    if (this->buttonCodes.SprintKey != -1 && buttonEvent->GetIDCode() == this->buttonCodes.SprintKey) {
        this->sprintKeyEvent(buttonEvent);
    }
    else if (this->buttonCodes.ToggleRunKey != -1 && buttonEvent->GetIDCode() == this->buttonCodes.ToggleRunKey) {
        this->toggleRunKeyEvent(buttonEvent);
    }
    else if (this->buttonCodes.UnsheathKey != -1 && buttonEvent->GetIDCode() == this->buttonCodes.UnsheathKey) {
        this->readyWeaponEvent(buttonEvent);
    }
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
    else if (buttonEvent->IsUp()) {
    }
    return;
}

void ButtonPressEvent::readyWeaponEvent(const RE::ButtonEvent* buttonEvent) {
    if (buttonEvent->IsDown()) {
        this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->updateImmersiveBehavior();
    }
    else if (buttonEvent->IsUp()) {
    }
    return;
}