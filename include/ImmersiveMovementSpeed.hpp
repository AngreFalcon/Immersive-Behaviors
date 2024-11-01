#pragma once
#include "ImmersiveBehaviorMap.hpp"
#include "nlohmann/json.hpp"

enum class MOVE_TYPE : int {
    WALK,
    RUN,
	DISABLED
};

struct IMSConfig : public IBConfig {
public:
    std::unordered_map<std::string, MOVE_TYPE> contextMap;
	bool alwaysRespectMoveSpeedToggle;

    IMSConfig(void)
		: alwaysRespectMoveSpeedToggle(false) {	
		for (const std::string keyword : this->keywordList) {
			this->contextMap[keyword] = MOVE_TYPE::DISABLED;
		}
	}

private:

};

/**
 * @brief Reads in data from our config JSON file and then stores the appropriate values to our config struct.
 * 
 * @param nlohmann_json_j 
 * @param nlohmann_json_t 
 */
void from_json(const nlohmann::json& nlohmann_json_j, IMSConfig& nlohmann_json_t);

class ImmersiveMovementSpeed : public ImmersiveBehavior {
friend class ButtonPressEvent;
public:
    ImmersiveMovementSpeed(void);
    ~ImmersiveMovementSpeed() = default;

    IMSConfig config;

	/**
	 * @brief Calls updateTempState() and then performs an update to our behavior based on the getActiveState() value.
	 * 
	 */
	void updateImmersiveBehavior(void) override;

protected:
	/**
	 * @brief Inverts this->moveSpeedToggled.
	 * 
	 */
	void toggleMoveSpeed(void);

    /**
     * @brief Checks if the player is currently walking, and if so, makes the player run (not sprint).
     *
     */
    void sprintKeyPressed(void);

    /**
     * @brief Checks if immersiveWalkModeActive is true and if so, makes the player walk. Else, calls stopSprinting().
     *
     */
    void sprintKeyReleased(void);

private:
    bool immersiveWalkModeActive;
	bool moveSpeedToggled = false;

	/**
	 * @brief Verifies whether the behavior's contextMap contains a specified context keyword.
	 * 
	 * @return true 
	 * @return false 
	 */
	bool contextMapContains(const std::string&) override;

	/**
	 * @brief Sets this->immersiveWalkModeActive to !run != this->moveSpeedToggled.
	 * Additionally, force an update to the player's move speed. Sets the player's running status to be equivalent to !this->immersiveWalkModeActive.
	 * (i.e., if the player should be running but this->moveSpeedToggled is true after the user presses their 'Toggle Always Run' key, this->immersiveWalkModeActive will be true and running status will be false).
	 * 
	 * @param [in]	run The player should be running.
	 */
	void changeMoveSpeed(bool run = false);

    /**
     * @brief This method is currently non-functional.
     * Force the player to stop sprinting.
     *
     */
    void stopSprinting(void);
};