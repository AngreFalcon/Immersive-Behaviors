#pragma once
#include "ImmersiveCameraView.hpp"
#include "ImmersiveMovementSpeed.hpp"

// was: class PlayerCellChangeEvent : public IBEvent
class CombatEvent : public RE::BSTEventSink<RE::TESCombatEvent> {
public:
    CombatEvent(void) = default;
    CombatEvent(std::shared_ptr<BehaviorMap> behaviors);
    ~CombatEvent() = default;

    /* functions */
    RE::BSEventNotifyControl ProcessEvent(const RE::TESCombatEvent* a_event, RE::BSTEventSource<RE::TESCombatEvent>*) override;

private:
    std::shared_ptr<BehaviorMap> behaviors;
    
    /* functions */

};