#include "PlayerCellChangeEvent.hpp"
#include "ImmersiveCameraView.hpp"
#include "helpers.hpp"

PlayerCellChangeEvent::PlayerCellChangeEvent(std::shared_ptr<ImmersiveBehaviorMap> immersiveBehaviors) {
    this->immersiveBehaviors = immersiveBehaviors;
    this->lastCellIsInterior = std::nullopt;
}

RE::BSEventNotifyControl PlayerCellChangeEvent::ProcessEvent(const RE::BGSActorCellEvent* event, RE::BSTEventSource<RE::BGSActorCellEvent>*) {
    if (!event->actor || event->actor.get().get() != player::GetSingleton()) {
        return RE::BSEventNotifyControl::kContinue;
    }
    //onPlayerCellTransition();
    if (event->flags == RE::BGSActorCellEvent::CellFlag::kEnter) {
        this->onPlayerCellEntry();
    }
    else {
        this->onPlayerCellExit();
    }
    return RE::BSEventNotifyControl::kContinue;
}

void PlayerCellChangeEvent::onPlayerCellTransition(void) {
    logs::debug("");
    logs::debug("Player Cell Transition Event:");
	helpers::printPlayerLocKeywords();
    return;
}

void PlayerCellChangeEvent::onPlayerCellEntry(void) {
    std::string context = helpers::isPlayerInInterior() ? "interior" : "exterior";
    if (!this->lastCellIsInterior || (helpers::isPlayerInInterior() != this->lastCellIsInterior)) { // only change the player's perspective if lastCellIsInterior does not have a value (game was just started) or the player has just changed from an interior to exterior or vice versa
		this->immersiveBehaviors->get<ImmersiveCameraView>()->updateCellState(context);
		this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->updateCellState(context);
		this->immersiveBehaviors->get<ImmersiveCameraView>()->updateImmersiveBehavior();
		this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->updateImmersiveBehavior();
    }
    this->lastCellIsInterior = helpers::isPlayerInInterior();
    return;
}

void PlayerCellChangeEvent::onPlayerCellExit(void) {
    return;
}