#include "CombatEvent.hpp"

CombatEvent::CombatEvent(std::shared_ptr<ImmersiveBehaviorMap> immersiveBehaviors) {
    this->immersiveBehaviors = immersiveBehaviors;
}

RE::BSEventNotifyControl CombatEvent::ProcessEvent(const RE::TESCombatEvent* a_event, RE::BSTEventSource<RE::TESCombatEvent>*) {
	//if (!Settings::CloseInCombat()) {
	//	return RE::BSEventNotifyControl::kContinue;
    //}
	using CombatState = RE::ACTOR_COMBAT_STATE;
	const auto isPlayerRef = [](auto&& a_ref) {
		return a_ref && a_ref->IsPlayerRef();
	};
	if (a_event && (isPlayerRef(a_event->actor) || isPlayerRef(a_event->targetActor))) {
		switch (*a_event->newState) {
		case CombatState::kCombat:
            this->combatEngaged();
		case CombatState::kSearching:
            this->beingPursued();
			break;
		default:
			break;
		}
	}
	return RE::BSEventNotifyControl::kContinue;
}

void CombatEvent::combatEngaged(void) {
    this->immersiveBehaviors->get<ImmersiveMovementSpeed>()->updateImmersiveBehavior();
    return;
}

void CombatEvent::beingPursued(void) {

    return;
}