#include "RE/P/PlayerCharacter.h"
#include "helpers.hpp"

using player = RE::PlayerCharacter;

namespace helpers {
    bool isPlayerInInterior(void) {
        return RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())->IsInteriorCell();
    }

	bool isPlayerInHostileZone(void) {
		static const std::array safeZoneKeywords = { "LocSetMilitaryCamp", "LocTypeBarracks", "LocTypeCastle", "LocTypeCemetery", "LocTypeCity", "LocTypeDwelling", "LocTypeFarm", "LocTypeGuild", "LocTypeHabitation", "LocTypeHabitationHasInn", "LocTypeHouse", "LocTypeInn", "LocTypeJail", "LocTypeLumberMill", "LocTypeMilitaryCamp", "LocTypeOrcStronghold", "LocTypePlayerHouse", "LocTypeSettlement", "LocTypeShip", "LocTypeStewardsDwelling", "LocTypeStore", "LocTypeTemple", "LocTypeTown" };
		if (!player::GetSingleton() || !player::GetSingleton()->GetCurrentLocation()) {
			return false;
		}
		for (const RE::BGSKeyword* keyword : player::GetSingleton()->GetCurrentLocation()->GetKeywords()) {
			if (std::ranges::contains(safeZoneKeywords, keyword->formEditorID.c_str())) {
				return false;
			}
		}
		return true;
	}

    bool isPlayerInCombat(void) {
        return player::GetSingleton()->IsInCombat();
    }

    bool isPlayerWeaponDrawn(void) {
		switch (player::GetSingleton()->AsActorState()->GetWeaponState()) {
		case RE::WEAPON_STATE::kDrawn:
		case RE::WEAPON_STATE::kDrawing:
		case RE::WEAPON_STATE::kWantToDraw:
			return true;
		default:
			return false;
		}
    }

    bool isPlayerInWater(void) {
        return player::GetSingleton()->IsInWater();
    }

    bool isPlayerSwimming(void) {
        return player::GetSingleton()->AsActorState()->IsSwimming();
    }

    bool isPlayerSitting(void) {
        return player::GetSingleton()->AsActorState()->GetSitSleepState() == RE::SIT_SLEEP_STATE::kIsSitting;
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
