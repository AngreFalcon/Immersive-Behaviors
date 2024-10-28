#pragma once
#include "nlohmann/json.hpp"

class Config {
public:
    static Config& get(void);
    nlohmann::json json;

private:
    Config(const std::filesystem::path& configPath);
    ~Config();
};