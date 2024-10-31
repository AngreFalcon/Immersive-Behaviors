#pragma once

// here we will define any functions that have
// generic utility for the rest of our classes
// and may be used to create wrappers or
// aliases for otherwise unwieldy calls

namespace helpers {
    /**
     * @brief Get whether player is currently in an interior cell or not.
     * 
     * @return true
     * @return false
     */
    bool isPlayerInInterior(void);

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
}