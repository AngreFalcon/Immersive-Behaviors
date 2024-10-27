#pragma once
#include "PlayerCellChangeEvent.hpp"

enum class VIEW_TYPE {
    FIRST_PERSON,
    THIRD_PERSON
};

class ImmersiveCameraView {
public:
    static void shiftCameraPerspective();

    struct Config {
        VIEW_TYPE interior;
        VIEW_TYPE exterior;
        VIEW_TYPE combat;
        VIEW_TYPE swimming;
    } config;

private:
    static bool isInterior;
    static struct CameraState {
        float interiorThirdPersonZoom;
        float exteriorThirdPersonZoom;
    } cameraState;
};
