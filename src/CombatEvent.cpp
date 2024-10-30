#include "CombatEvent.hpp"

CombatEvent::CombatEvent(std::shared_ptr<BehaviorMap> behaviors) {
    this->behaviors = behaviors;
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
            combatEngaged();
		case CombatState::kSearching:
            beingPursued();
			break;
		default:
			break;
		}
	}
	return RE::BSEventNotifyControl::kContinue;
}

void CombatEvent::combatEngaged(void) {
    behaviors->get<ImmersiveMovementSpeed>()->contextualMoveSpeed("combat");
    behaviors->get<ImmersiveCameraView>()->shiftCameraPerspective("combat");
    return;
}

void CombatEvent::beingPursued(void) {

    return;
}