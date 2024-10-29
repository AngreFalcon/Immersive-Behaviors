#include "Config.hpp"
#include <fstream>

constexpr std::string CONFIG_FILENAME = "config.json";

Config& Config::get(void) {
    static Config instance(CONFIG_FILENAME);
    return instance;
}

Config::Config(const std::filesystem::path& configPath) {
    using Json = nlohmann::json;
    try {
        const Json config = nlohmann::json::parse(std::ifstream(configPath));
        auto s2 = config.get<std::string>();
    } catch(...) {
        logs::warn("config file wasn't present or parsing failed, using defaults");
    }
}

Config::~Config() {
    try {
        std::ofstream(CONFIG_FILENAME) << json;
    } catch(...) { }
}