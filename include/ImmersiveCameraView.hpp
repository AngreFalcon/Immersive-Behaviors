#pragma once
#include "Behaviors.hpp"

enum class VIEW_TYPE {
    FIRST_PERSON,
    THIRD_PERSON
};

class ImmersiveCameraView : public Behaviors {
public:
    ImmersiveCameraView(void);
    ~ImmersiveCameraView() = default;

    struct Config {
        VIEW_TYPE interior;
        VIEW_TYPE exterior;
        VIEW_TYPE combat;
        VIEW_TYPE swimming;
    } config;

    /* functions */
    void shiftCameraPerspectiveToFirstPerson(void);
    void shiftCameraPerspectiveToThirdPerson(void);
    void recordZoomLevel(void);

private:
    struct CameraState {
        float interiorThirdPersonZoom;
        float exteriorThirdPersonZoom;
    } cameraState;

    /* functions */
    void restoreZoomLevel(void);
};
