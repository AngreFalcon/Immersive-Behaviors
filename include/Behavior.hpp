#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>



struct IBConfig {
public:
    IBConfig()
        : enabled(false) { }
    
    /**
     * @brief Set the behavior's enable state
     * 
     * @param [in] enableBehavior Should the behavior be enabled or not.
     */
    void setEnabled(const bool enableBehavior);

    /**
     * @brief Returns whether the behavior is enabled or disabled.
     * 
     * @return true
     * @return false
     */
    bool isEnabled(void);
    
private:
    bool enabled;

};

class Behavior {
public:
    Behavior(void) = default;
    virtual ~Behavior() = default;

private:

};