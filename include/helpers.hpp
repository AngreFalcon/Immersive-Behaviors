#pragma once

// here we will define any functions that have
// generic utility for the rest of our classes
// and may be used to create wrappers or
// aliases for otherwise unwieldy calls

namespace helpers {
    /**
     * @brief 
     * 
     * @return true Player is in interior cell.
     * @return false Player is in exterior cell.
     */
    bool isPlayerInInterior(void);

    /**
     * @brief 
     * 
     * @return true Player is in combat.
     * @return false Player is not in combat.
     */
    bool isPlayerInCombat(void);

    /**
     * @brief 
     * 
     * @return true Player has weapon drawn.
     * @return false Player does not have weapon drawn.
     */
    bool isPlayerWeaponDrawn(void);

    /**
     * @brief 
     * 
     * @return true Player is standing in water.
     * @return false Player is not standing in water.
     */
    bool isPlayerInWater(void);

    /**
     * @brief 
     * 
     * @return true Player is swimming.
     * @return false Player is not swimming
     */
    bool isPlayerSwimming(void);

    /**
     * @brief 
     * 
     * @return true Player is sitting.
     * @return false Player is not sitting.
     */
    bool isPlayerSitting(void);
    
    /**
     * @brief 
     * 
     * @return true Player is sneaking.
     * @return false Player is not sneaking.
     */
    bool isPlayerSneaking(void);

    /**
     * @brief 
     * 
     * @return true Player is riding mount.
     * @return false Player is not riding mount.
     */
    bool isPlayerMounted(void);

    /**
     * @brief 
     * 
     * @return true Player is trespassing.
     * @return false Player is not trespassing.
     */
    bool isPlayerTrespassing(void);

    /**
     * @brief 
     * 
     * @return true Player is walking.
     * @return false Player is not walking.
     */
    bool isPlayerWalking(void);

    /**
     * @brief 
     * 
     * @return true Player is in third person.
     * @return false Player is in first person.
     */
    bool isPlayerInThirdPerson(void);
}