#include "RE/P/PlayerCharacter.h"
#include "helpers.hpp"


using player = RE::PlayerCharacter;

namespace helpers {
    bool isPlayerInInterior(void) {
        return RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())->IsInteriorCell();
    }

    bool isPlayerInCombat(void) {
        return player::GetSingleton()->IsInCombat();
    }

    bool isPlayerWeaponDrawn(void) {
        return player::GetSingleton()->AsActorState()->IsWeaponDrawn();
    }

    bool isPlayerInWater(void) {
        return player::GetSingleton()->IsInWater();
    }

    bool isPlayerSwimming(void) {
        return player::GetSingleton()->AsActorState()->IsSwimming();
    }

    bool isPlayerSitting(void) {
        return player::GetSingleton()->AsActorState()->IsSitting();
    }

    bool isPlayerSneaking(void) {
        return player::GetSingleton()->AsActorState()->IsSneaking();
    }

    bool isPlayerMounted(void) {
        return player::GetSingleton()->IsOnMount();
    }

    bool isPlayerTrespassing(void) {
        return player::GetSingleton()->IsTrespassing();
    }

    bool isPlayerWalking(void) {
        return !RE::PlayerControls::GetSingleton()->data.running;
    }

    bool isPlayerInThirdPerson(void) {
        return RE::PlayerCamera::GetSingleton()->IsInThirdPerson();
    }
}