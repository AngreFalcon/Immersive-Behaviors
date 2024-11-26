#include "ImmersiveBehavior.hpp"
#include "Config.hpp"
#include "helpers.hpp"

std::set<std::string> IBConfig::keywordList{};
std::set<std::string> IBConfig::LocKeywords::hostileZone{};
std::set<std::string> IBConfig::LocKeywords::friendlyZone{};
const std::unordered_map<std::string, std::function<bool()>> IBConfig::conditionChecks = {
	{ "swimming", &helpers::isPlayerSwimming },
	{ "combat", &helpers::isPlayerInCombat },
	{ "sitting", &helpers::isPlayerSitting },
	{ "weaponDrawn", &helpers::isPlayerWeaponDrawn },
	{ "sneaking", &helpers::isPlayerSneaking },
	{ "mounted", &helpers::isPlayerMounted },
	{ "trespassing", &helpers::isPlayerTrespassing },
	{ "inWater", &helpers::isPlayerInWater },
	{ "hostileZone", [](){ return helpers::checkCellKeywords(locKeywords.hostileZone); } },
	{ "friendlyZone", [](){ return helpers::checkCellKeywords(locKeywords.friendlyZone); } }
};

void IBConfig::setEnabled(const bool enableImmersiveBehavior) {
    this->enabled = enableImmersiveBehavior;
    return;
}

std::set<std::string> IBConfig::getKeywordList() const {
	return this->keywordList;
}

bool IBConfig::isEnabled(void) const {
    return this->enabled;
}

void from_json(const nlohmann::json& nlohmann_json_j, IBConfig& nlohmann_json_t) {
    IBConfig nlohmann_json_default_obj;
    nlohmann_json_t.keywordList = nlohmann_json_default_obj.keywordList;
	nlohmann_json_t.locKeywords.hostileZone = nlohmann_json_default_obj.locKeywords.hostileZone;
	nlohmann_json_t.locKeywords.friendlyZone = nlohmann_json_default_obj.locKeywords.friendlyZone;
	nlohmann_json_t.keywordList = nlohmann_json_j["keywordList"].get<std::set<std::string>>();
	nlohmann_json_t.locKeywords.hostileZone = nlohmann_json_j["hostileZones"].get<std::set<std::string>>();
	nlohmann_json_t.locKeywords.friendlyZone = nlohmann_json_j["friendlyZones"].get<std::set<std::string>>();
	logs::debug("Successfully parsed keywords:");
	for (std::string keyword : nlohmann_json_t.keywordList) {
		logs::debug("\t{}", keyword);
	}
	return;
}

ImmersiveBehavior::ImmersiveBehavior(void) {
    this->config = Config::get<IBConfig>("immersiveBehavior");
}

void ImmersiveBehavior::updateTempState(void) {
	this->tempState = "";
	logs::debug("");
	for (const std::string keyword : this->config.keywordList) {
		logs::debug("\t\t\t{}", keyword);
		if (this->config.conditionChecks.at(keyword)() && contextMapContains(keyword)) {
			this->tempState = keyword;
			break;
		}
	}
	return;
}

void ImmersiveBehavior::updateCellState(const std::string& newCellState) {
	this->cellState = newCellState;
	return;
}

bool ImmersiveBehavior::isActiveStateTemp(void) const {
	return this->tempState != "";
}

std::string ImmersiveBehavior::getActiveState(void) const {
	return this->isActiveStateTemp() ? this->tempState : this->cellState;
}