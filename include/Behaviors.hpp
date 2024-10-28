#pragma once

class Behaviors {
public:
    Behaviors(void) = default;
    ~Behaviors() = default;

    bool isEnabled(void);

private:
    bool enabled;
};