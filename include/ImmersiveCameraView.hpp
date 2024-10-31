#pragma once
#include "ImmersiveBehaviorMap.hpp"
#include "nlohmann/json.hpp"

enum class VIEW_TYPE : int {
    FIRST_PERSON,
    THIRD_PERSON
};

struct ICVConfig : public IBConfig {
friend class ImmersiveCameraView;
public:
    std::unordered_map<std::string, VIEW_TYPE> contextMap;
    float interiorZoom;
    float exteriorZoom;

    ICVConfig(void)
        : contextMap({ { "interior", VIEW_TYPE::FIRST_PERSON }, { "exterior", VIEW_TYPE::THIRD_PERSON }, { "combat", VIEW_TYPE::FIRST_PERSON }, { "swimming", VIEW_TYPE::FIRST_PERSON } })
        , interiorZoom(-2.0f)
        , exteriorZoom(-2.0f) { }
        
    /**
     * @brief Checks whether the player is currently in an interior or exterior cell and then records the current zoom level to either this->interiorZoom or this->exteriorZoom.
     * 
     */
    void recordZoomLevel(void);

    /**
     * @brief Checks whether the player is currently in an interior or exterior cell and then restores the RE::PlayerCamera state to the recorded zoom level.
     * 
     */
    void restoreZoomLevel(void);

private:

};

/**
 * @brief Reads in data from our config JSON file and then stores the appropriate values to our config struct.
 * 
 * @param [in]	nlohmann_json_j 
 * @param [out]	nlohmann_json_t 
 */
void from_json(const nlohmann::json& nlohmann_json_j, ICVConfig& nlohmann_json_t);

class ImmersiveCameraView : public ImmersiveBehavior {
public:
    ImmersiveCameraView(void);
    ~ImmersiveCameraView() = default;
    ICVConfig config;

	/**
	 * @brief Calls updateTempState() and then performs an update to our behavior based on the getActiveState() value.
	 * 
	 */
	void updateImmersiveBehavior() override;

	/**
	 * @brief Inverts this->povToggled.
	 * 
	 */
	void togglePOV(void);

private:
	bool povToggled = false;

	/**
	 * @brief Verifies whether the behavior's contextMap contains a specified context keyword.
	 * 
	 * @return true 
	 * @return false 
	 */
	bool contextMapContains(const std::string&) override;

    /**
     * @brief Grabs the activeState from getActiveState() and then references this->config.contextMap to determine whether shiftCameraPerspectiveToFirstPerson() or shiftCameraPerspectiveToThirdPerson() should be called.
     * 
     */
    void shiftCameraPerspective();

    /**
     * @brief Forces the player's camera perspective to switch to first person.
     * 
     */
    void shiftCameraPerspectiveToFirstPerson(void);

    /**
     * @brief Forces the player's camera perspective to switch to third person and then calls this->config.restoreZoomLevel().
     * 
     */
    void shiftCameraPerspectiveToThirdPerson(void);

};
