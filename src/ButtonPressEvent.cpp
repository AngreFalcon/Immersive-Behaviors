#include "ButtonPressEvent.hpp"
#include "helpers.hpp"
#include "ImmersiveMovementSpeed.hpp"

ButtonPressEvent::ButtonPressEvent(std::shared_ptr<ImmersiveCameraView> immersiveCameraView, std::shared_ptr<ImmersiveMovementSpeed> immersiveMovementSpeed) {
    this->immersiveCameraView = immersiveCameraView;
    this->immersiveMovementSpeed = immersiveMovementSpeed;
}

RE::BSEventNotifyControl ButtonPressEvent::ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*) {
    if (!a_event) {
        return RE::BSEventNotifyControl::kContinue;
    }
    for (RE::InputEvent* event = *a_event; event; event = event->next) {
        if (const RE::ButtonEvent* buttonEvent = event->AsButtonEvent()) {
            buttonStates.SprintKey = RE::ControlMap::GetSingleton()->GetMappedKey("Sprint", buttonEvent->GetDevice());
            buttonStates.ToggleRunKey = RE::ControlMap::GetSingleton()->GetMappedKey("Toggle Always Run", buttonEvent->GetDevice());
            const uint32_t dxScanCode = buttonEvent->GetIDCode();
            if (buttonStates.SprintKey != -1 && dxScanCode == buttonStates.SprintKey) {
                sprintKeyPressed(buttonEvent);
            }
            else if (buttonStates.ToggleRunKey != -1 && dxScanCode == buttonStates.ToggleRunKey) {
                toggleRunKeyPressed(buttonEvent);
            }
        }
        return RE::BSEventNotifyControl::kContinue;
    }
}

void ButtonPressEvent::sprintKeyPressed(const RE::ButtonEvent* buttonEvent) {
    if (buttonEvent->IsDown()) {
        if (!helpers::isPlayerWalking()) {
            return;
        }
        immersiveMovementSpeed->makePlayerRunWhenSprint();
        logs::info("Start running");
    }
    else if (buttonEvent->IsUp() && immersiveMovementSpeed->isWalkModeActive()) {
        immersiveMovementSpeed->makePlayerWalk();
        logs::info("Stop running");    
    }
    return;
}

void ButtonPressEvent::toggleRunKeyPressed(const RE::ButtonEvent* buttonEvent) {
    // Button down
    if (buttonEvent->IsDown()) {
    }
    // immediately let go off the button
    else if (buttonEvent->IsUp()) {
        if (helpers::isPlayerWalking()) {
            immersiveMovementSpeed->makePlayerWalk();
        }
        else {
            immersiveMovementSpeed->makePlayerRun();
        }
    }
    logs::info("Toggle running");
    return;
}