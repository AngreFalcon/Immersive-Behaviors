#pragma once
#include "ImmersiveCameraView.hpp"
#include "ImmersiveMovementSpeed.hpp"

class CombatEvent : public RE::BSTEventSink<RE::TESCombatEvent> {
public:
    CombatEvent(void) = default;
    CombatEvent(std::shared_ptr<ImmersiveBehaviorMap> immersiveBehaviors);
    ~CombatEvent() = default;

    /**
     * @brief Processes an event triggered by the player being pursued for or engaged in combat.
     * 
     * @param [in]	a_event Pointer to the combat event pointer that we want to process.
     * @return RE::BSEventNotifyControl::kContinue 
     * @return RE::BSEventNotifyControl::kStop 
     */
    RE::BSEventNotifyControl ProcessEvent(const RE::TESCombatEvent* a_event, RE::BSTEventSource<RE::TESCombatEvent>*) override;

private:
    std::shared_ptr<ImmersiveBehaviorMap> immersiveBehaviors;
    
    /**
     * @brief Calls an update for certain behaviors dependent upon the player being engaged in combat.
     * 
     */
    void combatEngaged(void);
    
    /**
     * @brief Calls an update for certain behaviors dependent upon the player being pursued by an aggressor.
     * 
     */
    void beingPursued(void);

};