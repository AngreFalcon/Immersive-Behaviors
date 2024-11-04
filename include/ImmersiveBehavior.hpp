#pragma once
#include "nlohmann/json.hpp"
#include "helpers.hpp"

struct IBConfig {
friend class ImmersiveBehavior;
public:
	static std::set<std::string> keywordList;
	static struct LocKeywords {
		static std::vector<std::string> hostileZone;
		static std::vector<std::string> friendlyZone;
	} locKeywords;

    IBConfig()
        : enabled(false) { }
    
    /**
     * @brief Set the ImmersiveBehavior's enable state.
     * 
     * @param [in] enableImmersiveBehavior Should the ImmersiveBehavior be enabled or not.
     */
    void setEnabled(const bool enableImmersiveBehavior);

    /**
     * @brief Returns whether the ImmersiveBehavior is enabled or disabled.
     * 
     * @return true
     * @return false
     */
    bool isEnabled(void);
    
protected:
	static const std::unordered_map<std::string, std::function<bool()>> conditionChecks;

private:
    bool enabled;

};

/**
 * @brief Reads in data from our config JSON file and then stores the appropriate values to our config struct.
 * 
 * @param [in]	nlohmann_json_j 
 * @param [out]	nlohmann_json_t 
 */
void from_json(const nlohmann::json& nlohmann_json_j, IBConfig& nlohmann_json_t);

class ImmersiveBehavior {
friend class PlayerCellChangeEvent;
public:
    ImmersiveBehavior(void);
    virtual ~ImmersiveBehavior() = default;
	IBConfig config;

	/**
	 * @brief 
	 * 
	 */
	template <typename T>
	inline void debugLogging(void) const {
    	logs::debug("");
    	logs::debug("constructed {}", typeid(T).name());
		return;
	}

	/**
	 * @brief Performs a series of checks to determine the player's state and then updates our tempState variable with the highest priority keyword, if any, that applies.
	 * 
	 */
	void updateTempState(void);

	/**
	 * @brief Get whether the active state is the tempState or the cellState.
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isActiveStateTemp(void);

	/**
	 * @brief Get the tempState, or if tempState is not active, returns the cellState instead.
	 * 
	 * @return const std::string Either tempState or cellState.
	 */
	const std::string getActiveState(void);
	
	/**
	 * @brief Calls updateTempState() and then performs an update to our behavior based on the getActiveState() value.
	 * 
	 */
	virtual void updateImmersiveBehavior(void) = 0;

	/**
	 * @brief Verifies whether the behavior's contextMap contains a specified context keyword.
	 * 
	 * @return true 
	 * @return false 
	 */
	virtual bool contextMapContains(const std::string&) = 0;

protected:
	/**
	 * @brief Updates our cellState to the specified value. Only called by PlayerCellChangeEvent.
	 * 
	 * @param [in]	cellState The new cellState that should be stored in this->cellState.
	 */
	void updateCellState(const std::string& cellState);

private:
	std::string cellState;
	std::string tempState;

};