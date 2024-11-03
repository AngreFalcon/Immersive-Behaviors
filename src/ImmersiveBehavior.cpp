#include "ImmersiveBehavior.hpp"
#include "Config.hpp"
#include "helpers.hpp"

std::set<std::string> IBConfig::keywordList{};

void IBConfig::setEnabled(const bool enableImmersiveBehavior) {
    this->enabled = enableImmersiveBehavior;
    return;
}

bool IBConfig::isEnabled(void) {
    return this->enabled;
}

void from_json(const nlohmann::json& nlohmann_json_j, IBConfig& nlohmann_json_t) {
    IBConfig nlohmann_json_default_obj;
    nlohmann_json_t.keywordList = nlohmann_json_default_obj.keywordList;
    for (const std::string& keyword : nlohmann_json_j["keywordList"].get<std::vector<std::string>>()) {
        nlohmann_json_t.keywordList.emplace(keyword);
        logs::debug("\tSuccessfully parsed keyword: {}", keyword);
    }
	return;
}

ImmersiveBehavior::ImmersiveBehavior(void) {
    this->config = Config::get<IBConfig>("immersiveBehavior");
}

// this is a bandaid solution due to our map of functions not executing when called
bool getCondition(const std::string& keyword) {
	if (keyword == "swimming") return helpers::isPlayerSwimming();
	else if (keyword == "combat") return helpers::isPlayerInCombat();
	else if (keyword == "sitting") return helpers::isPlayerSitting();
	else if (keyword == "weaponDrawn") return helpers::isPlayerWeaponDrawn();
	else if (keyword == "hostileZone") return helpers::isPlayerInHostileZone();
	else if (keyword == "friendlyZone") return helpers::isPlayerInFriendlyZone();
	else if (keyword == "sneaking") return helpers::isPlayerSneaking();
	else if (keyword == "mounted") return helpers::isPlayerMounted();
	else if (keyword == "trespassing") return helpers::isPlayerTrespassing();
	else if (keyword == "inWater") return helpers::isPlayerInWater();
	else return false;
}

void ImmersiveBehavior::updateTempState(void) {
	for (const std::string keyword : this->config.keywordList) {
		logs::debug("checking keywork: {}", keyword);
		if (getCondition(keyword) && contextMapContains(keyword)) {
			this->tempState = keyword;
			logs::debug("keyword {} set as tempState", keyword);
			return;
		}
	}
	this->tempState = "";
	return;
}

void ImmersiveBehavior::updateCellState(const std::string& newCellState) {
	this->cellState = newCellState;
	return;
}

const std::string ImmersiveBehavior::getActiveState(void) {
	if (this->tempState != "") {
		return this->tempState;
	}
	else {
		return this->cellState;
	}
}

bool ImmersiveBehavior::isActiveStateTemp(void) {
	return this->tempState != "";
}