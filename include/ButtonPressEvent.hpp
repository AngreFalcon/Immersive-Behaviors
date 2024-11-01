#pragma once
#include "ImmersiveCameraView.hpp"
#include "ImmersiveMovementSpeed.hpp"

class ButtonPressEvent : public RE::BSTEventSink<RE::InputEvent*> {
public:
    ButtonPressEvent(void) = default;
    ButtonPressEvent(std::shared_ptr<ImmersiveBehaviorMap> immersiveBehaviors);
    ~ButtonPressEvent() = default;

    /**
     * @brief Processes an event triggered by the player performing some input through their keyboard, controller, mouse, or some other interface device.
     * 
     * @param [in]	a_event Pointer to the input event pointer that we want to process.
     * @return RE::BSEventNotifyControl::kContinue 
     * @return RE::BSEventNotifyControl::kStop 
     */
    RE::BSEventNotifyControl ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*) override;

private:
    std::shared_ptr<ImmersiveBehaviorMap> immersiveBehaviors;
	bool weaponReadyRunState = false;
    struct ButtonCodes {
        int64_t SprintKey = -1;
        int64_t ToggleRunKey = -1;
		int64_t UnsheathKey = -1;
		int64_t ZoomIn = -1;
		int64_t ZoomOut = -1;
		int64_t TogglePOV = -1;
    } buttonCodes;

    /**
     * @brief Grabs the scan codes of the specified keys/buttons and stores them in our buttonStates struct.
     * 
     * @param [in]	buttonEvent Pointer to the buttonEvent that's being processed.
     */
    void initializeKeyCodes(const RE::ButtonEvent* buttonEvent);

    /**
     * @brief Compares the scan code of the button event to our struct of stored buttonCodes and then calls the relevant function to handle that input.
     * 
     * @param [in]	buttonEvent Pointer to the buttonEvent that's being processed.
     */
    void routeButtonEvents(const RE::ButtonEvent* buttonEvent);

    /**
     * @brief Calls an update for certain behaviors dependent upon an actuation of our 'Sprint' key.
     * 
     * @param [in]	buttonEvent Pointer to the buttonEvent that's being processed.
     */
    void sprintKeyEvent(const RE::ButtonEvent* buttonEvent);

    /**
     * @brief Calls an update for certain behaviors dependent upon an actuation of our 'Toggle Always Run' key.
     * 
     * @param [in]	buttonEvent Pointer to the buttonEvent that's being processed.
     */
    void toggleRunKeyEvent(const RE::ButtonEvent* buttonEvent);

	/**
	 * @brief Calls an update for certain behaviors dependent upon an actuation of our 'Ready Weapon' key.
	 * 
	 * @param [in]	buttonEvent Pointer to the buttonEvent that's being processed.
	 */
	void readyWeaponKeyEvent(const RE::ButtonEvent* buttonEvent);

	/**
	 * @brief Calls an update for certain behaviors dependent upon an actuation of our 'Zoom In' or 'Zoom Out' key.
	 * 
	 * @param [in]	buttonEvent Pointer to the buttonEvent that's being processed.
	 */
	void zoomKeyEvent(const RE::ButtonEvent* buttonEvent);
	
	/**
	 * @brief Calls an update for certain behaviors dependent upon an actuation of our 'Toggle POV' key.
	 * 
	 * @param [in]	buttonEvent Pointer to the buttonEvent that's being processed.
	 */
	void togglePOVKeyEvent(const RE::ButtonEvent* buttonEvent);

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