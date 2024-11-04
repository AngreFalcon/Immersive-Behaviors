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
	nlohmann_json_t.keywordList = nlohmann_json_j["keywordList"].get<std::set<std::string>>();
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
	for (const std::string keyword : this->config.keywordList) {
		if (helpers::conditionChecks.at(keyword)() && contextMapContains(keyword)) {
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