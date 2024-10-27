#include "EventHandler.hpp"
#include "RE/B/BGSKeyword.h"
#include "RE/B/BGSLocation.h"
#include "RE/P/PlayerCharacter.h"
#include "RE/T/TESActorLocationChangeEvent.h"
#include "ImmersiveCameraView.hpp"
#include "PlayerCellChangeEvent.hpp"
#include <sstream>

RE::FormID EventHandler::oldFormID;

void onPlayerCellTransition(const RE::BGSLocation* loc) {
    const auto player = RE::PlayerCharacter::GetSingleton();
    std::stringstream keywordList = {};

    if (loc) {
        for (const auto* keyword : loc->GetKeywords()) {
            RE::DebugNotification(keyword->GetName());
            keywordList << keyword->formEditorID.c_str() << "\n";
        }
    }
    std::string locName = (loc ? loc->GetFullName() : "Wilderness");
    std::string debugMsg = std::format("Location: {}\nIs Interior: {}\nKeywords: {}", locName, PlayerCellChangeEvent::isPlayerInInterior(), keywordList.str());
    logs::info("{}", debugMsg);
    // auto message = std::format("Player activated {}", itemName);
    // Popup a "Debug MessageBox" (with an OK button)
    // RE::DebugMessageBox(debugMsg.c_str());

    // Show a "Debug Notification" (displays in the top-left corner of  game)
    RE::DebugNotification(locName.c_str());
}

void onPlayerCellEntry() {
    ImmersiveCameraView::shiftCameraPerspective();
}

void onPlayerCellExit() { }

RE::BSEventNotifyControl EventHandler::ProcessEvent(const RE::BGSActorCellEvent* event, RE::BSTEventSource<RE::BGSActorCellEvent>* source) {
    const auto player = RE::PlayerCharacter::GetSingleton();
    if (!event->actor || event->actor.get().get() != player) {
        return RE::BSEventNotifyControl::kContinue;
    }
    if (event->flags == RE::BGSActorCellEvent::CellFlag::kEnter) {
        onPlayerCellEntry();
    }
    else {
        onPlayerCellExit();
    }
    oldFormID = event->cellID;
    onPlayerCellTransition(RE::TES::GetSingleton()->GetCell(player->GetPosition())->GetLocation());
    return RE::BSEventNotifyControl::kContinue;
}
