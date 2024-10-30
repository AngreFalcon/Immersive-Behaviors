#pragma once
#include "BehaviorMap.hpp"
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

void from_json(const nlohmann::json& nlohmann_json_j, ICVConfig& nlohmann_json_t);

class ImmersiveCameraView : public Behavior {
public:
    ImmersiveCameraView(void);
    ~ImmersiveCameraView() = default;
    ICVConfig config;

    /**
     * @brief 
     * 
     * @param context 
     */
    void shiftCameraPerspective(const std::string& context);

private:

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
