#pragma once
#include "IBEvent.hpp"
#include "ImmersiveCameraView.hpp"
#include "ImmersiveMovementSpeed.hpp"

class ButtonPressEvent : public RE::BSTEventSink<RE::InputEvent*> {
public:
    ButtonPressEvent(void) = default;
    ButtonPressEvent(std::shared_ptr<ImmersiveCameraView> immersiveCameraView, std::shared_ptr<ImmersiveMovementSpeed> immersiveMovementSpeed);
    ~ButtonPressEvent() = default;

    RE::BSEventNotifyControl ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*) override;
    void sprintKeyPressed(const RE::ButtonEvent* buttonEvent);
    void toggleRunKeyPressed(const RE::ButtonEvent* buttonEvent);

private:
    std::shared_ptr<ImmersiveCameraView> immersiveCameraView;
    std::shared_ptr<ImmersiveMovementSpeed> immersiveMovementSpeed;
    struct ButtonStates {
        int32_t SprintKey = -1;
        int32_t ToggleRunKey = -1;
    } buttonStates;
};