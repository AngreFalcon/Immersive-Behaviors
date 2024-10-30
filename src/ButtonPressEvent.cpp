#include "ButtonPressEvent.hpp"
#include "helpers.hpp"
#include "ImmersiveMovementSpeed.hpp"

ButtonPressEvent::ButtonPressEvent(const std::shared_ptr<BehaviorMap> behaviors) {
    this->behaviors = behaviors;
}

RE::BSEventNotifyControl ButtonPressEvent::ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*) {
    if (!a_event) {
        return RE::BSEventNotifyControl::kContinue;
    }
    for (RE::InputEvent* event = *a_event; event; event = event->next) {
        if (const RE::ButtonEvent* buttonEvent = event->AsButtonEvent()) {
            initializeKeyCodes(buttonEvent);
            routeButtonEvents(buttonEvent->GetIDCode(), buttonEvent);
        }
        return RE::BSEventNotifyControl::kContinue;
    }
}

void ButtonPressEvent::initializeKeyCodes(const RE::ButtonEvent* buttonEvent) {
    buttonStates.SprintKey = RE::ControlMap::GetSingleton()->GetMappedKey("Sprint", buttonEvent->GetDevice());
    buttonStates.ToggleRunKey = RE::ControlMap::GetSingleton()->GetMappedKey("Toggle Always Run", buttonEvent->GetDevice());
    return;
}

void ButtonPressEvent::routeButtonEvents(const uint32_t dxScanCode, const RE::ButtonEvent* buttonEvent) {
    if (buttonStates.SprintKey != -1 && dxScanCode == buttonStates.SprintKey) {
        sprintKeyEvent(buttonEvent);
    }
    else if (buttonStates.ToggleRunKey != -1 && dxScanCode == buttonStates.ToggleRunKey) {
        toggleRunKeyEvent(buttonEvent);
    }
    return;
}

void ButtonPressEvent::sprintKeyEvent(const RE::ButtonEvent* buttonEvent) {
    if (buttonEvent->IsDown()) {
        behaviors->get<ImmersiveMovementSpeed>()->sprintKeyPressed();
    }
    else {
        behaviors->get<ImmersiveMovementSpeed>()->sprintKeyReleased();
    }
    return;
}

void ButtonPressEvent::toggleRunKeyEvent(const RE::ButtonEvent* buttonEvent) {
    if (buttonEvent->IsDown()) {
        return;
    }
    else if (buttonEvent->IsUp()) {
        if (helpers::isPlayerWalking()) {
            behaviors->get<ImmersiveMovementSpeed>()->contextualMoveSpeed("toggledWalk");
        }
        else {
            behaviors->get<ImmersiveMovementSpeed>()->contextualMoveSpeed("toggledRun");
        }
    }
    //logs::info("Toggle running");
    return;
}
