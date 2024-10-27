#pragma once
#include "RE/B/BGSKeyword.h"

class EventHandler : public RE::BSTEventSink<RE::BGSActorCellEvent> {
public:
    //RE::BSEventNotifyControl ProcessEvent(const RE::TESActorLocationChangeEvent*, RE::BSTEventSource<RE::TESActorLocationChangeEvent>*) override;
    RE::BSEventNotifyControl ProcessEvent(const RE::BGSActorCellEvent*, RE::BSTEventSource<RE::BGSActorCellEvent>*) override;

private:
    static RE::FormID oldFormID;
};
