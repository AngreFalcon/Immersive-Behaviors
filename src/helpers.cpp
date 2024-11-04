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

	bool checkCellKeywords(const std::vector<std::string>& zoneKeywords) {
        if (!player::GetSingleton() || !RE::TES::GetSingleton() || !RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition()) || !RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())->GetLocation()) {
            return false;
        }
        for (const RE::BGSKeyword* cellKeyword : RE::TES::GetSingleton()->GetCell(player::GetSingleton()->GetPosition())->GetLocation()->GetKeywords()) {
			for (const std::string keyword : zoneKeywords) {
				if (cellKeyword->formEditorID.c_str() == keyword) return true;
			}
        }
        return false;
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
