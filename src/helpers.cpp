#include "helpers.hpp"

namespace helpers {
    bool doesPlayerExist(void) {
        return player::GetSingleton();
    }

    bool isPlayerInInterior(void) {
        if (!player::GetSingleton() || !RE::TES::GetSingleton() || !RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())) {
            return false;
        }
        return RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())->IsInteriorCell();
    }

    bool isPlayerInHostileZone(void) {
        static const std::array hostileZoneKeywords = { "LocSetCave", "LocSetCaveIce", "LocSetDwarvenRuin", "LocSetNordicRuin", "LocSetOutdoor", "LocTypeAnimalDen", "LocTypeBanditCamp", "LocTypeDragonLair", "LocTypeDragonPriestLair", "LocTypeDraugrCrypt", "LocTypeDungeon", "LocTypeDwarvenAutomatons", "LocTypeFalmerHive", "LocTypeForswornCamp", "LocTypeGiantCamp", "LocTypeHagravenNest", "LocTypeShipwreck", "LocTypeSprigganGrove", "LocTypeVampireLair", "LocTypeWarlockLair", "LocTypeWerewolfLair" };
        if (!player::GetSingleton() || !RE::TES::GetSingleton() || !RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition()) || !RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())->GetLocation()) {
            return false;
        }
        for (const RE::BGSKeyword* keyword : RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())->GetLocation()->GetKeywords()) {
            if (std::ranges::contains(hostileZoneKeywords, keyword->formEditorID.c_str())) {
                return true;
            }
        }
        return false;
    }

	bool isPlayerInFriendlyZone(void) {
        static const std::array hostileZoneKeywords = { "LocTypeBarracks", "LocTypeCastle", "LocTypeCemetery", "LocTypeCity", "LocTypeDwelling", "LocTypeFarm", "LocTypeGuild", "LocTypeHabitation", "LocTypeHabitationHasInn", "LocTypeHouse", "LocTypeInn", "LocTypeJail", "LocTypeLumberMill", "LocTypeMilitaryCamp", "LocTypeOrcStronghold", "LocTypePlayerHouse", "LocTypeSettlement", "LocTypeShip", "LocTypeStewardsDwelling", "LocTypeStore", "LocTypeTemple", "LocTypeTown" };
        if (!player::GetSingleton() || !RE::TES::GetSingleton() || !RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition()) || !RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())->GetLocation()) {
            return false;
        }
        for (const RE::BGSKeyword* keyword : RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())->GetLocation()->GetKeywords()) {
            if (std::ranges::contains(hostileZoneKeywords, keyword->formEditorID.c_str())) {
                return true;
            }
        }
        return false;
    }

    bool isPlayerInCombat(void) {
		logs::debug("Is player in combat: {}", player::GetSingleton()->IsInCombat());
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
        return !controls::GetSingleton()->data.running;
    }

    bool isPlayerInThirdPerson(void) {
        return camera::GetSingleton()->IsInThirdPerson();
    }

	void printPlayerLocKeywords(void) {
    	const RE::BGSLocation* loc = player::GetSingleton()->GetCurrentLocation();
    	std::stringstream cellKeywordList = {};
    	if (loc) {
        	for (const RE::BGSKeyword* keyword : loc->GetKeywords()) {
            	cellKeywordList << keyword->formEditorID.c_str() << "\n";
        	}
        	std::string locName = (loc->GetFullName() ? loc->GetFullName() : "Wilderness");
        	std::string debugMsg = std::format("Location: {}\nIs Interior: {}\nKeywords: {}", locName, helpers::isPlayerInInterior(), cellKeywordList.str());
        	logs::debug("\t{}", debugMsg);
        	//RE::DebugMessageBox(debugMsg.c_str());
        	//RE::DebugNotification(locName.c_str());
    	}
		return;
	}
}
