#pragma once
#include "BehaviorMap.hpp"
#include "nlohmann/json.hpp"

enum class MOVE_TYPE : int {
    WALK,
    RUN
};

struct IMSConfig {
public:
    std::unordered_map<std::string, MOVE_TYPE> contextMap;
    IMSConfig()
        : enabled(false)
        , contextMap({ { "interior", MOVE_TYPE::WALK }, { "exterior", MOVE_TYPE::RUN }, { "combat", MOVE_TYPE::RUN } }) { }
        
    void setEnabled(bool);
    bool isEnabled(void);
private:
    bool enabled;
};

void from_json(const nlohmann::json& nlohmann_json_j, IMSConfig& nlohmann_json_t);

class ImmersiveMovementSpeed : public Behavior {
public:
    ImmersiveMovementSpeed(void);
    ~ImmersiveMovementSpeed() = default;

    IMSConfig config;

    void contextualMoveSpeed(const std::string& context);
    void makePlayerWalk(void);
    void makePlayerRun(void);
    void sprintKeyPressed(void);
    void sprintKeyReleased(void);
    void stopSprinting(void);

private:
    bool immersiveWalkModeActive;
};