#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>

struct IBConfig {
public:
	static constexpr std::array<std::string, 10> keywordList = { "interior", "exterior", "combat", "swimming", "sitting", "weaponDrawn", "sneaking", "mounted", "trespassing", "inWater" };

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
    
private:
    bool enabled;

};

class ImmersiveBehavior {
friend class PlayerCellChangeEvent;
public:
    ImmersiveBehavior(void) = default;
    virtual ~ImmersiveBehavior() = default;

	/**
	 * @brief Performs a series of checks to determine the player's state and then updates our tempState variable with the highest priority keyword, if any, that applies.
	 * 
	 */
	void updateTempState(void);

	/**
	 * @brief Get the tempState, or if tempState is not active, returns the cellState instead.
	 * 
	 * @return const std::string Either tempState or cellState.
	 */
	const std::string getActiveState(void);

	/**
	 * @brief Get whether the active state is the tempState or the cellState.
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isActiveStateTemp(void);
	
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