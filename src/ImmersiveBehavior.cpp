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

// this makes me want to kill myself
// but, until a better solution is decided upon, this is necessary
void ImmersiveBehavior::updateTempState(void) {
	for (const std::string keyword : this->config.keywordList) {
		if (helpers::conditionChecks[keyword] && contextMapContains(keyword)) this->tempState = keyword;
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