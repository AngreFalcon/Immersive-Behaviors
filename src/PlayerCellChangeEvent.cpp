#include "PlayerCellChangeEvent.hpp"
#include "RE/P/PlayerCharacter.h"

bool PlayerCellChangeEvent::isPlayerInInterior() {
    return RE::TES::GetSingleton()->GetCell(RE::PlayerCharacter::GetSingleton()->GetPosition())->IsInteriorCell();
}