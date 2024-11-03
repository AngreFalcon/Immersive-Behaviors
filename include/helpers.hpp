#pragma once

// here we will define any functions that have
// generic utility for the rest of our classes
// and may be used to create wrappers or
// aliases for otherwise unwieldy calls

using player = RE::PlayerCharacter;
using controls = RE::PlayerControls;
using camera = RE::PlayerCamera;

namespace helpers {
	/**
	 * @brief 
	 * 
	 * @return true 
	 * @return false 
	 */
	bool doesPlayerExist(void);

    /**
     * @brief Get whether player is currently in an interior cell or not.
     * 
     * @return true
     * @return false
     */
    bool isPlayerInInterior(void);

	/**
	 * @brief Get whether player is currently in a hostile location or not.
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isPlayerInHostileZone(void);

	/**
	 * @brief Get whether player is currently in a friendly location or not.
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isPlayerInFriendlyZone(void);

    // need to work on implementation
	//bool isPlayerBeingPursued(void);
	//bool isPlayerInDialogue(void);

    /**
     * @brief Get whether player is currently engaged in combat or not.
     * 
     * @return true
     * @return false
     */
    bool isPlayerInCombat(void);

    /**
     * @brief Get whether the player's weapon is currently drawn or not.
     * 
     * @return true
     * @return false
     */
    bool isPlayerWeaponDrawn(void);

    /**
     * @brief Get whether the player is currently standing in water or not.
     * 
     * @return true
     * @return false
     */
    bool isPlayerInWater(void);

    /**
     * @brief Get whether the player is currently swimming or not.
     * 
     * @return true
     * @return false
     */
    bool isPlayerSwimming(void);

    /**
     * @brief Get whether the player is currently sitting or not.
     * 
     * @return true
     * @return false
     */
    bool isPlayerSitting(void);
    
    /**
     * @brief Get whether the player is currently sneaking or not.
     * 
     * @return true
     * @return false
     */
    bool isPlayerSneaking(void);

    /**
     * @brief Get whether the player is currently riding a mount or not.
     * 
     * @return true
     * @return false
     */
    bool isPlayerMounted(void);

    /**
     * @brief Get whether the player is currently trespassing or not.
     * 
     * @return true
     * @return false
     */
    bool isPlayerTrespassing(void);

    /**
     * @brief Get whether the player is currently walking or not.
     * 
     * @return true
     * @return false
     */
    bool isPlayerWalking(void);

    /**
     * @brief Get whether the player is in third person or not.
     * 
     * @return true
     * @return false
     */
    bool isPlayerInThirdPerson(void);

	/**
	 * @brief Print the list of keywords belonging to the player's current location to the debug log.
	 * 
	 */
	void printPlayerLocKeywords(void);
	
	// this does not work
	static const std::unordered_map<std::string, std::function<bool()>> conditionChecks = {
		{ "swimming", isPlayerSwimming },
		{ "combat", isPlayerInCombat },
		{ "sitting", isPlayerSitting },
		{ "weaponDrawn", isPlayerWeaponDrawn },
		{ "hostileZone", isPlayerInHostileZone },
		{ "friendlyZone", isPlayerInFriendlyZone },
		{ "sneaking", isPlayerSneaking },
		{ "mounted", isPlayerMounted },
		{ "trespassing", isPlayerTrespassing },
		{ "inWater", isPlayerInWater }
	};
}