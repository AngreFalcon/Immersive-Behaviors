#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>

struct IBConfig {
public:
    IBConfig()
        : enabled(false) { }
    
    /* functions */
    void setEnabled(bool);
    bool isEnabled(void);
    
private:
    bool enabled;

    /* functions */

};

class Behavior {
public:
    Behavior(void) = default;
    virtual ~Behavior() = default;

private:

    /* functions */

};