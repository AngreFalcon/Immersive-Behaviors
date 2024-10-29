#pragma once

class Behaviors {
public:
    Behaviors(void) = default;
    ~Behaviors() = default;

    bool isEnabled(void);
    // behaviors will be disable by default
    // and enabled when detected via config file
    // for development, behaviors will be enabled via constructor
    void enableBehavior(void);

private:
    bool enabled = false;
};