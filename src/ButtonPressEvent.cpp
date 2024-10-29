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
        if (helpers::isPlayerWalking()) {
            behaviors->get<ImmersiveMovementSpeed>()->makePlayerRunWhenSprint();
            //logs::info("Start running");
        }
    }
    else {
        if (behaviors->get<ImmersiveMovementSpeed>()->isWalkModeActive()) {
            behaviors->get<ImmersiveMovementSpeed>()->makePlayerWalk();
            //logs::info("Stop running");
        }
        else {
            behaviors->get<ImmersiveMovementSpeed>()->stopSprinting();
            //logs::info("Stop sprinting");
        }
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
            behaviors->get<ImmersiveMovementSpeed>()->makePlayerWalk();
        }
        else {
            behaviors->get<ImmersiveMovementSpeed>()->makePlayerRun();
        }
    }
    //logs::info("Toggle running");
    return;
}
