#pragma once
#include "ImmersiveCameraView.hpp"
#include "ImmersiveMovementSpeed.hpp"

// was: class PlayerCellChangeEvent : public IBEvent
class PlayerCellChangeEvent : public RE::BSTEventSink<RE::BGSActorCellEvent> {
public:
    PlayerCellChangeEvent(void) = default;
    PlayerCellChangeEvent(std::shared_ptr<ImmersiveBehaviorMap> immersiveBehaviors);
    ~PlayerCellChangeEvent() = default;

    /**
     * @brief Processes an event triggered by the player changing cells.
     * 
     * @param [in]	event Pointer to the input event pointer that we want to process.
     * @return RE::BSEventNotifyControl::kContinue 
     * @return RE::BSEventNotifyControl::kStop 
     */
    RE::BSEventNotifyControl ProcessEvent(const RE::BGSActorCellEvent* event, RE::BSTEventSource<RE::BGSActorCellEvent>*) override;

private:
    std::shared_ptr<ImmersiveBehaviorMap> immersiveBehaviors;
    std::optional<bool> lastCellIsInterior;
    
    /**
     * @brief Executes any time a player enters or leaves a cell (meaning this function will run twice each time the player transitions between cells, first due to them exiting the old cell and again due to them entering the new cell).
     * 
     */
    void onPlayerCellTransition(void);

    /**
     * @brief Calls an update for certain behaviors dependent upon the player entering a cell.
     * 
     */
    void onPlayerCellEntry(void);

    /**
     * @brief Calls an update for certain behaviors dependent upon the player leaving a cell.
     * 
     */
    void onPlayerCellExit(void);

};