#include "PlayerCellChangeEvent.hpp"
#include "ImmersiveCameraView.hpp"
#include "helpers.hpp"

using player = RE::PlayerCharacter;

PlayerCellChangeEvent::PlayerCellChangeEvent(std::shared_ptr<BehaviorMap> behaviors) {
    this->behaviors = behaviors;
    lastCellIsInterior = std::nullopt;
}

RE::BSEventNotifyControl PlayerCellChangeEvent::ProcessEvent(const RE::BGSActorCellEvent* event, RE::BSTEventSource<RE::BGSActorCellEvent>*) {
    if (!event->actor || event->actor.get().get() != player::GetSingleton()) {
        return RE::BSEventNotifyControl::kContinue;
    }
    onPlayerCellTransition();
    if (event->flags == RE::BGSActorCellEvent::CellFlag::kEnter) {
        onPlayerCellEntry();
    }
    else {
        onPlayerCellExit();
    }
    return RE::BSEventNotifyControl::kContinue;
}

// this function is currently only used to print debug messages
void PlayerCellChangeEvent::onPlayerCellTransition(void) {
    const RE::BGSLocation* loc = RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())->GetLocation();
    std::stringstream keywordList = {};
    logs::debug("");
    logs::debug("Player Cell Transition Event:");
    if (loc) {
        for (const auto* keyword : loc->GetKeywords()) {
            RE::DebugNotification(keyword->GetName());
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
    affectBehavior();
    return;
}

void PlayerCellChangeEvent::onPlayerCellExit(void) {
    behaviors->get<ImmersiveCameraView>()->config.recordZoomLevel();
    return;
}

void PlayerCellChangeEvent::affectBehavior(void) {
    std::string context;
    if (helpers::isPlayerInInterior() && (!lastCellIsInterior || !lastCellIsInterior.value())) {
        context = "interior";
        //behaviors->get<ImmersiveCameraView>()->shiftCameraPerspective("interior");
        //behaviors->get<ImmersiveMovementSpeed>()->contextualMoveSpeed("interior");
        lastCellIsInterior = true;
    }
    else if (RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())->IsExteriorCell() && (!lastCellIsInterior || lastCellIsInterior.value())) {
        context = "exterior";
        //behaviors->get<ImmersiveCameraView>()->shiftCameraPerspective("exterior");
        //behaviors->get<ImmersiveMovementSpeed>()->contextualMoveSpeed("exterior");
        lastCellIsInterior = false;
    }
    behaviors->get<ImmersiveCameraView>()->shiftCameraPerspective(context);
    behaviors->get<ImmersiveMovementSpeed>()->contextualMoveSpeed(context);
    return;
}