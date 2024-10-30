#include "BehaviorMap.hpp"
#include "ButtonPressEvent.hpp"
#include "CombatEvent.hpp"
#include "PlayerCellChangeEvent.hpp"
#include "RE/T/TESCondition.h"
#include "REL/Version.h"
#include "SKSE/Interfaces.h"
#include "SKSE/Version.h"
#include <span>
#include <typeindex>

void MessageHandler(SKSE::MessagingInterface::Message* a_msg);

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    // RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink<RE::TESActorLocationChangeEvent>(new EventHandler());
    const SKSE::MessagingInterface* messaging = SKSE::GetMessagingInterface();
    if (!messaging->RegisterListener("SKSE", MessageHandler)) {
        logs::critical("Could not register MessageHandler"sv);
        return false;
    }
    return true;
}

void MessageHandler(SKSE::MessagingInterface::Message* a_msg) {
    switch (a_msg->type) {
    case SKSE::MessagingInterface::kDataLoaded: {
        std::shared_ptr<BehaviorMap> behaviors = std::make_shared<BehaviorMap>();
        behaviors->insert<ImmersiveCameraView>();
        behaviors->insert<ImmersiveMovementSpeed>();

        RE::PlayerCharacter::GetSingleton()->AsBGSActorCellEventSource()->AddEventSink(new PlayerCellChangeEvent(behaviors));
        RE::BSInputDeviceManager::GetSingleton()->AddEventSink(new ButtonPressEvent(behaviors));
        RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink<RE::TESCombatEvent>(new CombatEvent(behaviors));
        
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
