#include "ImmersiveCameraView.hpp"

ImmersiveCameraView::CameraState ImmersiveCameraView::cameraState{};
bool ImmersiveCameraView::isInterior = false;

void ImmersiveCameraView::shiftCameraPerspective() {
    if (RE::PlayerCamera::GetSingleton()->IsInThirdPerson()) {
        cameraState.exteriorThirdPersonZoom = reinterpret_cast<RE::ThirdPersonState*>(RE::PlayerCamera::GetSingleton()->currentState.get())->targetZoomOffset;
    }
    if (PlayerCellChangeEvent::isPlayerInInterior() && !isInterior) {
        RE::PlayerCamera::GetSingleton()->ForceFirstPerson();
        isInterior = true;
    }
    else if (RE::TES::GetSingleton()->GetCell(RE::PlayerCharacter::GetSingleton()->GetPosition())->IsExteriorCell() && isInterior) {
        RE::PlayerCamera::GetSingleton()->ForceThirdPerson();
        auto thirdPersonState = reinterpret_cast<RE::ThirdPersonState*>(RE::PlayerCamera::GetSingleton()->currentState.get());
        thirdPersonState->targetZoomOffset = thirdPersonState->savedZoomOffset = thirdPersonState->currentZoomOffset = cameraState.exteriorThirdPersonZoom;
        isInterior = false;
    }
    return;
}