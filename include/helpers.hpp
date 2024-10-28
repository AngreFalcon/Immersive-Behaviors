#pragma once

// here we will define any functions that have
// generic utility for the rest of our classes
// and may be used to create wrappers or
// aliases for otherwise unwieldy calls

namespace helpers {
    // functions to check player's status
    bool isPlayerInInterior(void);
    bool isPlayerInCombat(void);
    bool isPlayerWeaponDrawn(void);
    bool isPlayerInWater(void);
    bool isPlayerSwimming(void);
    bool isPlayerSitting(void);
    bool isPlayerSneaking(void);
    bool isPlayerMounted(void);
    bool isPlayerTrespassing(void);
    bool isPlayerWalking(void);

    // functions to check player's camera status
    bool isPlayerInThirdPerson(void);
}