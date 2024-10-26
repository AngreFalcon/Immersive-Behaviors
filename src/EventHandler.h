#pragma once

#include "RE/B/BGSKeyword.h"
#include <span>

// ... shhh ... don't worry about this part of the code ... you can learn about it in:
//                                                          https://github.com/SkyrimScripting/SKSE_Template_GameEvents

void OnPlayerCellTransition(const RE::TESActorLocationChangeEvent*);

class EventHandler : public RE::BSTEventSink<RE::TESActorLocationChangeEvent> {
public:
    RE::BSEventNotifyControl ProcessEvent(const RE::TESActorLocationChangeEvent* event,
                                          RE::BSTEventSource<RE::TESActorLocationChangeEvent>*) override {
        if (event->actor == nullptr) {
            logs::warn("event->actor == nullptr");
            return RE::BSEventNotifyControl::kContinue;
        }
        if (event->newLoc == nullptr) {
            logs::warn("event->newLoc == nullptr");
            return RE::BSEventNotifyControl::kContinue;
        }
        if (event->actor.get() != RE::PlayerCharacter::GetSingleton()) {
            logs::warn("event->actor.get() != RE::PlayerCharacter::GetSingleton()");
            return RE::BSEventNotifyControl::kContinue;
        }
        if (event->actor.get()->GetParentCell() == nullptr) {
            logs::warn("event->actor.get()->GetParentCell() == nullptr");
            return RE::BSEventNotifyControl::kContinue;
        }
        OnPlayerCellTransition(event);
        return RE::BSEventNotifyControl::kContinue;
    }
};