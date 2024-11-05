#include "ImmersiveBehaviorMap.hpp"
#include "ButtonPressEvent.hpp"
#include "CombatEvent.hpp"
#include "PlayerCellChangeEvent.hpp"

/**
 * @brief 
 * 
 * @param [in]	a_msg 
 */
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
        std::shared_ptr<ImmersiveBehaviorMap> immersiveBehaviors = std::make_shared<ImmersiveBehaviorMap>();
        immersiveBehaviors->insert<ImmersiveCameraView>();
        immersiveBehaviors->insert<ImmersiveMovementSpeed>();

        RE::PlayerCharacter::GetSingleton()->AsBGSActorCellEventSource()->AddEventSink(new PlayerCellChangeEvent(immersiveBehaviors));
        RE::BSInputDeviceManager::GetSingleton()->AddEventSink(new ButtonPressEvent(immersiveBehaviors));
        RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink(new CombatEvent(immersiveBehaviors));
        break;
    }
    default:
        break;
    }
    return;
}
