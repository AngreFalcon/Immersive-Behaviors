#pragma once
#include "ImmersiveCameraView.hpp"
#include "ImmersiveMovementSpeed.hpp"

// was: class PlayerCellChangeEvent : public IBEvent
class PlayerCellChangeEvent : public RE::BSTEventSink<RE::BGSActorCellEvent> {
public:
    PlayerCellChangeEvent(void) = default;
    PlayerCellChangeEvent(std::shared_ptr<BehaviorMap> behaviors);
    ~PlayerCellChangeEvent() = default;

    /**
     * @brief 
     * 
     * @param event 
     * @param source 
     * @return RE::BSEventNotifyControl 
     */
    RE::BSEventNotifyControl ProcessEvent(const RE::BGSActorCellEvent* event, RE::BSTEventSource<RE::BGSActorCellEvent>* source) override;

private:
    std::shared_ptr<BehaviorMap> behaviors;
    std::optional<bool> lastCellIsInterior;
    
    /**
     * @brief 
     * 
     */
    void onPlayerCellTransition(void);

    /**
     * @brief 
     * 
     */
    void onPlayerCellEntry(void);

    /**
     * @brief 
     * 
     */
    void onPlayerCellExit(void);

    /**
     * @brief 
     * 
     */
    void affectBehavior(void);

};