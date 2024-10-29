#pragma once
#include "ImmersiveCameraView.hpp"
#include "ImmersiveMovementSpeed.hpp"

class ButtonPressEvent : public RE::BSTEventSink<RE::InputEvent*> {
public:
    ButtonPressEvent(void) = default;
    ButtonPressEvent(std::shared_ptr<BehaviorMap> behaviors);
    ~ButtonPressEvent() = default;

    /* functions */
    RE::BSEventNotifyControl ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*) override;
    void sprintKeyPressed(const RE::ButtonEvent* buttonEvent);
    void toggleRunKeyPressed(const RE::ButtonEvent* buttonEvent);

private:
    std::shared_ptr<BehaviorMap> behaviors;
    struct ButtonStates {
        int64_t SprintKey = -1;
        int64_t ToggleRunKey = -1;
    } buttonStates;
};

/* Below is a list of valid eventIDs and devices taken from here: https://ck.uesp.net/wiki/GetMappedKey_-_Input
Control: The name of the controls as a string. Valid controls listed below.
    Activate
    Auto-Move
    Back
    CameraPath
    Console
    Favorites
    Forward
    Hotkey1
    Hotkey2
    Hotkey3
    Hotkey4
    Hotkey5
    Hotkey6
    Hotkey7
    Hotkey8
    Journal
    Jump
    Left Attack/Block
    Look
    Move
    Multi-Screenshot
    Pause
    Quick Inventory
    Quick Magic
    Quick Map
    Quick Stats
    Quickload
    Quicksave
    Ready Weapon
    Right Attack/Block
    Run
    Screenshot
    Shout
    Sneak
    Sprint
    Strafe Left
    Strafe Right
    Toggle Always Run
    Toggle POV
    Tween Menu
    Wait
    Zoom In
    Zoom Out
DeviceType: The device type used. Valid devices listed below.
    0xFF = 255 = Auto detect (Default)
    0x00 = 0 = Keyboard
    0x01 = 1 = Mouse
    0x02 = 2 = Gamepad
*/