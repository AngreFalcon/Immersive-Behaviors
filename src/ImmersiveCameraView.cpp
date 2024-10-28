#include "ImmersiveCameraView.hpp"
#include "helpers.hpp"

ImmersiveCameraView::ImmersiveCameraView() {
    // -0.2 is set as the default, which places
    // the camera just behind the player character
    cameraState = { -0.2, -0.2 };
}

void ImmersiveCameraView::shiftCameraPerspectiveToFirstPerson(void) {
    if (isEnabled()) {
        return;
    }
    RE::PlayerCamera::GetSingleton()->ForceFirstPerson();
    return;
}

void ImmersiveCameraView::shiftCameraPerspectiveToThirdPerson(void) {
    if (isEnabled()) {
        return;
    }
    RE::PlayerCamera::GetSingleton()->ForceThirdPerson();
    restoreZoomLevel();
    return;
}

void ImmersiveCameraView::recordZoomLevel(void) {
    if (!isEnabled()) {
        return;
    }
    // if the player is in an interior cell,
    // record the interior cell's zoom record
    if (helpers::isPlayerInInterior()) {
        cameraState.interiorThirdPersonZoom = reinterpret_cast<RE::ThirdPersonState*>(RE::PlayerCamera::GetSingleton()->currentState.get())->targetZoomOffset;
        //logs::info("Interior Zoom Level: {}", cameraState.interiorThirdPersonZoom);
    }
    else {
        cameraState.exteriorThirdPersonZoom = reinterpret_cast<RE::ThirdPersonState*>(RE::PlayerCamera::GetSingleton()->currentState.get())->targetZoomOffset;
        //logs::info("Exterior Zoom Level: {}", cameraState.exteriorThirdPersonZoom);
    }
    return;
}

void ImmersiveCameraView::restoreZoomLevel(void) {
    if (!isEnabled()) {
        return;
    }
    RE::ThirdPersonState* thirdPersonState = reinterpret_cast<RE::ThirdPersonState*>(RE::PlayerCamera::GetSingleton()->currentState.get());
    // if the player is now in an interior and we're
    // being prompted to restore zoom levels, we should
    // use the interior third person zoom value rather
    // than the exterior value
    if (helpers::isPlayerInInterior()) {
        thirdPersonState->targetZoomOffset = thirdPersonState->savedZoomOffset = thirdPersonState->currentZoomOffset = cameraState.interiorThirdPersonZoom;
    }
    else {
        thirdPersonState->targetZoomOffset = thirdPersonState->savedZoomOffset = thirdPersonState->currentZoomOffset = cameraState.exteriorThirdPersonZoom;
    }
    return;
}