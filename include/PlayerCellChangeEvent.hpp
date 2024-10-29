#pragma once
#include "IBEvent.hpp"
#include "ImmersiveCameraView.hpp"
#include "ImmersiveMovementSpeed.hpp"

// was: class PlayerCellChangeEvent : public IBEvent
class PlayerCellChangeEvent : public RE::BSTEventSink<RE::BGSActorCellEvent> {
public:
    PlayerCellChangeEvent(void) = default;
    PlayerCellChangeEvent(std::shared_ptr<ImmersiveCameraView> immersiveCameraView, std::shared_ptr<ImmersiveMovementSpeed> immersiveMovementSpeed);
    ~PlayerCellChangeEvent() = default;

    RE::BSEventNotifyControl ProcessEvent(const RE::BGSActorCellEvent* event, RE::BSTEventSource<RE::BGSActorCellEvent>* source);
    void onPlayerCellTransition(void);
    void onPlayerCellEntry(void);
    void onPlayerCellExit(void);
    void affectBehavior(void);

private:
    std::shared_ptr<ImmersiveCameraView> immersiveCameraView;
    std::shared_ptr<ImmersiveMovementSpeed> immersiveMovementSpeed;
    bool lastCellIsInterior;
};