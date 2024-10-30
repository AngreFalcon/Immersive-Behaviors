#pragma once
#include "ImmersiveBehaviorMap.hpp"
#include "nlohmann/json.hpp"

enum class VIEW_TYPE : int {
    FIRST_PERSON,
    THIRD_PERSON
};

struct ICVConfig : public IBConfig {
public:
    std::unordered_map<std::string, VIEW_TYPE> contextMap;
    float interiorZoom;
    float exteriorZoom;

    ICVConfig()
        : contextMap({ { "interior", VIEW_TYPE::FIRST_PERSON }, { "exterior", VIEW_TYPE::THIRD_PERSON }, { "combat", VIEW_TYPE::FIRST_PERSON }, { "swimming", VIEW_TYPE::FIRST_PERSON } })
        , interiorZoom(-2.0f)
        , exteriorZoom(-2.0f) { }
        
    /**
     * @brief 
     * 
     */
    void recordZoomLevel();

    /**
     * @brief 
     * 
     */
    void restoreZoomLevel();

private:

};

/**
 * @brief 
 * 
 * @param nlohmann_json_j 
 * @param nlohmann_json_t 
 */
void from_json(const nlohmann::json& nlohmann_json_j, ICVConfig& nlohmann_json_t);

class ImmersiveCameraView : public ImmersiveBehavior {
public:
    ImmersiveCameraView(void);
    ~ImmersiveCameraView() = default;
    ICVConfig config;

	/**
	 * @brief 
	 * 
	 */
	void updateImmersiveBehavior(void) override;

private:

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
     * @param [in]	context 
     */
    void shiftCameraPerspective(const std::string& context);

    /**
     * @brief 
     * 
     */
    void shiftCameraPerspectiveToFirstPerson(void);

    /**
     * @brief 
     * 
     */
    void shiftCameraPerspectiveToThirdPerson(void);

};
