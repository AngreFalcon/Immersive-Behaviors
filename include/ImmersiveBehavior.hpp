#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>

struct IBConfig {
public:
    IBConfig()
        : enabled(false) { }
    
    /**
     * @brief Set the ImmersiveBehavior's enable state
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
	 * @brief 
	 * 
	 */
	void updateTempState(void);

	/**
	 * @brief Get the Active State object
	 * 
	 * @return const std::string 
	 */
	const std::string getActiveState(void);
	
	/**
	 * @brief 
	 * 
	 */
	virtual void updateImmersiveBehavior(void) = 0;

	/**
	 * @brief 
	 * 
	 * @return true 
	 * @return false 
	 */
	virtual bool contextMapContains(const std::string&) = 0;

protected:
	/**
	 * @brief 
	 * 
	 * @param cellState 
	 */
	void updateCellState(const std::string& cellState);

private:
	std::string cellState;
	std::string tempState;

};