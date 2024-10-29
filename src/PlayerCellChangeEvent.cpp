#include "PlayerCellChangeEvent.hpp"
#include "ImmersiveCameraView.hpp"
#include "helpers.hpp"

using player = RE::PlayerCharacter;

PlayerCellChangeEvent::PlayerCellChangeEvent(std::shared_ptr<ImmersiveCameraView> immersiveCameraView, std::shared_ptr<ImmersiveMovementSpeed> immersiveMovementSpeed) {
    this->immersiveCameraView = immersiveCameraView;
    this->immersiveMovementSpeed = immersiveMovementSpeed;
    lastCellIsInterior = false;
}

RE::BSEventNotifyControl PlayerCellChangeEvent::ProcessEvent(const RE::BGSActorCellEvent* event, RE::BSTEventSource<RE::BGSActorCellEvent>* source) {
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

void PlayerCellChangeEvent::onPlayerCellTransition(void) {
    const RE::BGSLocation* loc = RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())->GetLocation();
    std::stringstream keywordList = {};
    if (loc) {
        for (const auto* keyword : loc->GetKeywords()) {
            RE::DebugNotification(keyword->GetName());
            keywordList << keyword->formEditorID.c_str() << "\n";
        }
        std::string locName = (loc->GetFullName() ? loc->GetFullName() : "Wilderness");
        std::string debugMsg = std::format("Location: {}\nIs Interior: {}\nKeywords: {}", locName, helpers::isPlayerInInterior(), keywordList.str());
        //logs::info("{}", debugMsg);
        // auto message = std::format("Player activated {}", itemName);
        // Popup a "Debug MessageBox" (with an OK button)
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
    if (helpers::isPlayerInThirdPerson()) {
        immersiveCameraView->recordZoomLevel();
    }
    return;
}

void PlayerCellChangeEvent::affectBehavior(void) {
    if (helpers::isPlayerInInterior() && !lastCellIsInterior) {
        immersiveCameraView->shiftCameraPerspectiveToFirstPerson();
        immersiveMovementSpeed->makePlayerWalk();
        lastCellIsInterior = true;
    }
    else if (RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())->IsExteriorCell() && lastCellIsInterior) {
        immersiveCameraView->shiftCameraPerspectiveToThirdPerson();
        immersiveMovementSpeed->makePlayerRun();
        lastCellIsInterior = false;
    }
    return;
}