#pragma once
#include "nlohmann/json.hpp"
#include <optional>

class Config {
public:
    template <typename T>
    static inline T get(const std::string& configName) {
        static Config instance;
        return instance.json.contains(configName) ? instance.json[configName].template get<T>() : T();
    }
    nlohmann::json json;

private:
    Config();
    ~Config();
    
    /* functions */
};