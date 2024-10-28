#pragma once

class Behaviors {
public:
    Behaviors(void) = default;
    ~Behaviors() = default;

    bool isEnabled(void);
    void enableBehavior(void);
    void disableBehavior(void);

private:
    bool enabled = true;
};