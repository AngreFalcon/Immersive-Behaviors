#include "PlayerCellChangeEvent.hpp"
#include "RE/T/TESCondition.h"
#include "REL/Version.h"
#include "SKSE/Interfaces.h"
#include "SKSE/Version.h"
#include <span>

void MessageHandler(SKSE::MessagingInterface::Message*);

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    logs::info("");
    // RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink<RE::TESActorLocationChangeEvent>(new EventHandler());

    auto messaging = SKSE::GetMessagingInterface();
    if (!messaging->RegisterListener("SKSE", MessageHandler)) {
        logs::critical("Could not register MessageHandler"sv);
        return false;
    }

    return true;
}

void MessageHandler(SKSE::MessagingInterface::Message* a_msg) {
    ImmersiveCameraView immersiveCameraView{};
    ImmersiveMovementSpeed immersiveMovementSpeed{};
    switch (a_msg->type) {
    case SKSE::MessagingInterface::kDataLoaded: {
        RE::PlayerCharacter::GetSingleton()->AsBGSActorCellEventSource()->AddEventSink(new PlayerCellChangeEvent(immersiveCameraView, immersiveMovementSpeed));
        // input event
        // auto inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
        // inputDeviceManager->AddEventSink();
        break;
    }
    default:
        break;
    }
    return;
}
