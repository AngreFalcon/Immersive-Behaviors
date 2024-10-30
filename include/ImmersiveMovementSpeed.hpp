#pragma once
#include "ImmersiveBehaviorMap.hpp"
#include "nlohmann/json.hpp"

enum class MOVE_TYPE : int {
    WALK,
    RUN
};

struct IMSConfig : public IBConfig {
public:
    std::unordered_map<std::string, MOVE_TYPE> contextMap;
    IMSConfig()
        : contextMap({ { "interior", MOVE_TYPE::WALK }, { "exterior", MOVE_TYPE::RUN }, { "combat", MOVE_TYPE::RUN } }) { }

private:
};

/**
 * @brief 
 * 
 * @param nlohmann_json_j 
 * @param nlohmann_json_t 
 */
void from_json(const nlohmann::json& nlohmann_json_j, IMSConfig& nlohmann_json_t);

class ImmersiveMovementSpeed : public ImmersiveBehavior {
public:
    ImmersiveMovementSpeed(void);
    ~ImmersiveMovementSpeed() = default;

    IMSConfig config;

	/**
	 * @brief 
	 * 
	 */
	void updateImmersiveBehavior(void) override;

	/**
	 * @brief 
	 * 
	 */
	void toggleMoveSpeed(void);

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
	bool moveSpeedToggled = false;

	/**
	 * @brief 
	 * 
	 * @return true 
	 * @return false 
	 */
	bool contextMapContains(const std::string&) override;

	/**
	 * @brief 
	 * 
	 * @param run 
	 */
	void changeMoveSpeed(bool run = false);

    /**
     * @brief This function is currently non-functional.
     * Make the user stop sprinting.
     *
     */
    void stopSprinting(void);
};