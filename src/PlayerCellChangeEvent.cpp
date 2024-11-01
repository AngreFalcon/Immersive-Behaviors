#include "PlayerCellChangeEvent.hpp"
#include "ImmersiveCameraView.hpp"
#include "helpers.hpp"

using player = RE::PlayerCharacter;

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
    const RE::BGSLocation* loc = player::GetSingleton()->GetCurrentLocation();
    std::stringstream keywordList = {};
    logs::debug("");
    logs::debug("Player Cell Transition Event:");
    if (loc) {
        for (const RE::BGSKeyword* keyword : loc->GetKeywords()) {
            keywordList << keyword->formEditorID.c_str() << "\n";
        }
        std::string locName = (loc->GetFullName() ? loc->GetFullName() : "Wilderness");
        std::string debugMsg = std::format("Location: {}\nIs Interior: {}\nKeywords: {}", locName, helpers::isPlayerInInterior(), keywordList.str());
        logs::debug("\t{}", debugMsg);
        // auto message = std::format("Player activated {}", itemName);
        // RE::DebugMessageBox(debugMsg.c_str());

        // Show a "Debug Notification" (displays in the top-left corner of  game)
        RE::DebugNotification(locName.c_str());
    }
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
    if (!helpers::isPlayerInThirdPerson()) {
        return;
    }
    return;
}