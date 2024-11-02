#include "Config.hpp"

const std::string CONFIG_FILENAME = "./Data/SKSE/Plugins/ImmersiveBehaviors.json";

Config::Config() {
    using Json = nlohmann::json;
    try {
        this->json = nlohmann::json::parse(std::ifstream(CONFIG_FILENAME));
    } catch (...) {
        logs::warn("config file wasn't present or parsing failed - will use defaults instead");
    }
}

Config::~Config() {
    try {
        std::ofstream(CONFIG_FILENAME) << json;
    } catch (...) { }
}
