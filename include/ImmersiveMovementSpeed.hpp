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

private:

};

void from_json(const nlohmann::json& nlohmann_json_j, IMSConfig& nlohmann_json_t);

class ImmersiveMovementSpeed : public Behavior {
public:
    ImmersiveMovementSpeed(void);
    ~ImmersiveMovementSpeed() = default;

    IMSConfig config;

    /**
     * @brief 
     * 
     * @param context 
     */
    void contextualMoveSpeed(const std::string& context);

    /**
     * @brief 
     * 
     */
    void sprintKeyPressed(void);

    /**
     * @brief 
     * 
     */
    void sprintKeyReleased(void);

private:
    bool immersiveWalkModeActive;
    
    /**
     * @brief 
     * 
     */
    void makePlayerWalk(void);

    /**
     * @brief 
     * 
     */
    void makePlayerRun(void);

    /**
     * @brief 
     * 
     */
    void stopSprinting(void);

};