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
     * @brief Decide via the user's config file whether the user should be walking or running based on the event that's been triggered.
     *
     * @param [in]	context The context of the function call, to compare to the user's config and decide whether the player should start running or walking.
     */
    void contextualMoveSpeed(const std::string& context);

    /**
     * @brief Wrapper function used to decide what actions to perform when we receive an event that the user's sprint key has been depressed.
     *
     */
    void sprintKeyPressed(void);

    /**
     * @brief Wrapper function used to decide what actions to perform when we receive an event that the user's sprint key has been released.
     *
     */
    void sprintKeyReleased(void);

private:
    bool immersiveWalkModeActive;

    /**
     * @brief Change the player's always run status to false and set a flag that the player is now walking.
     *
     */
    void makePlayerWalk(void);

    /**
     * @brief Change the player's always run status to true and set a flag that the player is now running.
     *
     */
    void makePlayerRun(void);

    /**
     * @brief This function is currently non-functional.
     * Make the user stop sprinting.
     *
     */
    void stopSprinting(void);
};