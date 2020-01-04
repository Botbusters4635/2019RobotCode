//
// Created by abiel on 8/22/19.
//

#include "EctoPCM.h"
#include <boost/algorithm/string.hpp>

EctoPCM::EctoPCM() : Manager("EctoPCM") {
	log->info("Initializing EctoPCM...");
	
	pistonsConfig = settings->getAllOfGroup("Pistons");
	
	initializePistons();
}

void EctoPCM::initializePistons() {
	for (auto const &configEntry : pistonsConfig) {
		size_t propertySeparator = configEntry.first.find('.');
		
		std::string pistonName = configEntry.first.substr(0, propertySeparator);
		std::string propertyName = configEntry.first.substr(propertySeparator + 1);
		
		auto pistonIt = pistons.find(pistonName);
		
		if (pistonIt == pistons.end()) {
			pistonIt = pistons.emplace(pistonName, EctoPiston()).first;
		}
		
		if (propertyName == EctoPCMPropertyDict::id) {
			std::stringstream ss(configEntry.second);
			
			std::string token;
			std::vector<int> ids;
			while (std::getline(ss, token, ' ')) {
				ids.emplace_back(std::stoi(token));
			}
			
			if (ids.size() > 1) {
				pistonIt->second.isSingleSolenoid = false;
				pistonIt->second.aSolenoid = std::make_shared<frc::Solenoid>(ids.front());
				pistonIt->second.bSolenoid = std::make_shared<frc::Solenoid>(ids.at(1));
			} else if (!ids.empty()) {
				pistonIt->second.isSingleSolenoid = true;
				
				pistonIt->second.aSolenoid = std::make_shared<frc::Solenoid>(ids.front());
			} else {
				throw std::invalid_argument("No valid ID given for piston: " + pistonName);
			}
		}
		
		log->info("Added piston {}", pistonName);
	}
}

EctoPiston &EctoPCM::getPiston(const std::string &pistonName) {
	auto piston = pistons.find(boost::algorithm::to_lower_copy(pistonName));
	
	if (piston == pistons.end()) {
		log->error("Invalid piston name: {}", pistonName);
		throw std::runtime_error(fmt::format("Invalid piston name: {}", pistonName));
	}
	
	return piston->second;
}

void EctoPCM::setPiston(EctoPiston &piston, bool state) {
	if (state) {
		piston.aSolenoid->Set(true);
		piston.bSolenoid->Set(false);
	} else {
		piston.aSolenoid->Set(false);
		piston.bSolenoid->Set(true);
	}
	
	piston.currentState = state;
}

void EctoPCM::setPiston(const std::string &pistonName, bool state) {
	setPiston(getPiston(pistonName), state);
}

void EctoPCM::togglePiston(const std::string &pistonName) {
	auto piston = pistons.find(boost::algorithm::to_lower_copy(pistonName));
	
	if (piston == pistons.end()) {
		log->error("Invalid piston name: {}", pistonName);
		return;
	}
	
	piston->second.currentState = !piston->second.currentState;
	
	if (piston->second.currentState) {
		piston->second.aSolenoid->Set(true);
		piston->second.bSolenoid->Set(false);
	} else {
		piston->second.aSolenoid->Set(false);
		piston->second.bSolenoid->Set(true);
	}
}

void EctoPCM::update() {
	;
}