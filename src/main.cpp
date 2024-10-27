#include "EventHandler.hpp"
#include "RE/T/TESCondition.h"
#include "REL/Version.h"
#include "SKSE/Interfaces.h"
#include "SKSE/Version.h"
#include <span>

void MessageHandler(SKSE::MessagingInterface::Message*);

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);

    logs::info("");

    // We need to do *something* in the game to activate our "MessageBox" and "Notification".
    // This registers an "EventHandler" to handle whenever any object in the game is "Activated".
    // If the *player* activated the object, the name of the activated object is passed to OnPlayerActivateItem() above.
    // If you are curious about the event handler, see EventHandler.h
    // But you can also see more examples of game event handlers in the template:
    //                                                       https://github.com/SkyrimScripting/SKSE_Template_GameEvents
    // RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink<RE::TESActorLocationChangeEvent>(new EventHandler());

    auto messaging = SKSE::GetMessagingInterface();
    if (!messaging->RegisterListener("SKSE", MessageHandler)) {
        logs::critical("Could not register MessageHandler"sv);
        return false;
    }

    return true;
}

void MessageHandler(SKSE::MessagingInterface::Message* a_msg) {
    switch (a_msg->type) {
    case SKSE::MessagingInterface::kDataLoaded: {
        RE::PlayerCharacter::GetSingleton()->AsBGSActorCellEventSource()->AddEventSink(new EventHandler());
        // input event
        // auto inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
        // inputDeviceManager->AddEventSink();
        break;
    }
    default:
        break;
    }
}
