#include "CombatEvent.hpp"

CombatEvent::CombatEvent(std::shared_ptr<ImmersiveBehaviorMap> immersiveBehaviors) {
    this->immersiveBehaviors = immersiveBehaviors;
}

RE::BSEventNotifyControl CombatEvent::ProcessEvent(const RE::TESCombatEvent* a_event, RE::BSTEventSource<RE::TESCombatEvent>*) {
	const auto isPlayerRef = [](auto&& a_ref) {
		return a_ref && a_ref->IsPlayerRef();
	};
	if (a_event && (isPlayerRef(a_event->actor) || isPlayerRef(a_event->targetActor))) {
		switch (*a_event->newState) {
		case RE::ACTOR_COMBAT_STATE::kCombat:
            this->combatEngaged();
		case RE::ACTOR_COMBAT_STATE::kSearching:
            this->beingPursued();
			break;
		default:
    		this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->updateImmersiveBehavior();
    		this->immersiveBehaviors->get<ImmersiveCameraView>()->updateImmersiveBehavior();
			break;
		}
	}
	return RE::BSEventNotifyControl::kContinue;
}

void CombatEvent::combatEngaged(void) {
    return;
}

void CombatEvent::beingPursued(void) {

    return;
}