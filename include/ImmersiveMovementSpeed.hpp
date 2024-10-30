#pragma once
#include "BehaviorMap.hpp"
#include "nlohmann/json.hpp"

enum class MOVE_TYPE : int {
    WALK,
    RUN
};

struct IMSConfig : public IBConfig {
public:
    std::unordered_map<std::string, MOVE_TYPE> contextMap;
    IMSConfig()
        : contextMap({ { "interior", MOVE_TYPE::WALK }, { "exterior", MOVE_TYPE::RUN }, { "combat", MOVE_TYPE::RUN }, { "toggledRun", MOVE_TYPE::RUN }, { "toggledWalk", MOVE_TYPE::WALK } }) { }

    /* functions */

private:

    /* functions */

};

void from_json(const nlohmann::json& nlohmann_json_j, IMSConfig& nlohmann_json_t);

class ImmersiveMovementSpeed : public Behavior {
public:
    ImmersiveMovementSpeed(void);
    ~ImmersiveMovementSpeed() = default;

    IMSConfig config;

    /* functions */
    void contextualMoveSpeed(const std::string& context);
    void sprintKeyPressed(void);
    void sprintKeyReleased(void);

private:
    bool immersiveWalkModeActive;
    
    /* functions */
    void makePlayerWalk(void);
    void makePlayerRun(void);
    void stopSprinting(void);

};