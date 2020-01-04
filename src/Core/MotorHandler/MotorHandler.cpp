//
// Created by alberto on 31/07/19.
//

#include "MotorHandler.h"
#include "EctoMotor/EctoTalon.h"
#include "EctoMotor/EctoSpark.h"
#include "EctoMotor/EctoPWM.h"
#include "EctoMotor/EctoMotorSimulated.h"
#include <iostream>
#include "Utilities/Sendable/SendableUtils.h"


MotorHandler::MotorHandler() : Manager("MotorHandler") {
	log->info("Initializing EctoMotors...");
	rawMotorConfig = settings->getAllOfGroup("Motors");
	//log->warn("SparkMax maxPercentOutput has not been implemented.");
	//log->warn("SparkMax deadband has not been implemented");

#ifdef SIMULATION
	log->warn("Running in simulation mode!");
	initializeSimulatedMotors();
#else
	initializeMotors();
#endif
}

//TODO Motor health doesn't work
void MotorHandler::initializeMotors() {
	// Iterate over all lines in the configuration file
	std::vector<EctoMotorConfig> newConfigs;
	
	for (auto const &it : rawMotorConfig) {
		// Parse the value of the current line
		size_t idSeparator = it.first.find('_');
		size_t propertySeparator = it.first.find('.');
		
		std::string type = it.first.substr(0, idSeparator);
		int id = std::stoi(it.first.substr(idSeparator + 1, propertySeparator));
		
		std::string property = it.first.substr(propertySeparator + 1);
		
		// Search if a newConfig with that type and id exists already.
		auto selectedConfig = std::find_if(newConfigs.begin(), newConfigs.end(),
		                                   [&id, &type, this](const EctoMotorConfig &value) {
			                                   return (value.id == id) && (value.type == getMotorTypeFromString(type));
		                                   });
		
		// If the newConfig doesn't exist, create a new newConfig.
		if (selectedConfig == newConfigs.end()) {
			EctoMotorConfig newConfig;
			newConfig.type = getMotorTypeFromString(type);
			newConfig.id = id;
			newConfigs.emplace_back(newConfig);
			selectedConfig = newConfigs.end() - 1;
		}
		
		// Check which property needs to be modified, and modify the configuration's respective property.
		selectedConfig->modifyProperty(it.second, property);
		
		//log->info("Initialized motor with id: {} with type: {} with name: {}", id, type, selectedConfig->name);
	}
	
	// Create the respective EctoControllers for each motor
	for (const EctoMotorConfig &config : newConfigs) {
		std::string firmwareVer;
		
		switch (config.type) {
			case EctoMotorType::TalonSRX:
				motorControllers.emplace_back(std::make_shared<EctoTalon>(config.id, config.name));
				
				firmwareVer = motorControllers.back()->getFirmwareVersion();
				
				if (firmwareVer != talonVersion) {
					log->error("Outdated Talon Firmware! Expected: {} but got: {}", talonVersion, firmwareVer);
				}
				break;
			case EctoMotorType::SparkMax:
				motorControllers.emplace_back(std::make_shared<EctoSpark>(config.id, config.name));
				
				firmwareVer = motorControllers.back()->getFirmwareVersion();
				
				if (firmwareVer != sparkMaxVersion) {
					log->error("Outdated Spark MAX Firmware! Expected: {} but got: {}", sparkMaxVersion, firmwareVer);
				}
				break;
			
			default:
				throw std::runtime_error("Motor is of incorrect type or is not yet implemented: " +
				                         getStringFromMotorType(config.type));
		}
	}
}

void MotorHandler::initializeSimulatedMotors() {
	// Iterate over all lines in the configuration file
	std::vector<EctoMotorConfig> newConfigs;
	
	for (auto const &it : rawMotorConfig) {
		// Parse the value of the current line
		size_t idSeparator = it.first.find('_');
		size_t propertySeparator = it.first.find('.');
		
		std::string type = it.first.substr(0, idSeparator);
		int id = std::stoi(it.first.substr(idSeparator + 1, propertySeparator));
		
		std::string property = it.first.substr(propertySeparator + 1);
		
		// Search if a newConfig with that type and id exists already.
		auto selectedConfig = std::find_if(newConfigs.begin(), newConfigs.end(),
		                                   [&id, &type, this](const EctoMotorConfig &value) {
			                                   return (value.id == id) && (value.type == getMotorTypeFromString(type));
		                                   });
		
		// If the newConfig doesn't exist, create a new newConfig.
		if (selectedConfig == newConfigs.end()) {
			EctoMotorConfig newConfig;
			newConfig.type = getMotorTypeFromString(type);
			newConfig.id = id;
			newConfigs.emplace_back(newConfig);
			selectedConfig = newConfigs.end() - 1;
		}
		
		// Check which property needs to be modified, and modify the configuration's respective property.
		selectedConfig->modifyProperty(it.second, property);
		
		//log->info("Initialized motor with id: {} with type: {} with name: {}", id, type, selectedConfig->name);
	}
	
	// Create the respective EctoControllers for each motor
	for (const EctoMotorConfig &config : newConfigs) {
		motorControllers.emplace_back(std::make_shared<EctoMotorSimulated>(config.id, config.name));
	}
	
}

void MotorHandler::update() {
#ifdef SIMULATION
	for(auto &motor : motorControllers) {
		//log->info("Sending: {}", motor->getName());
		EctoSendableUtils::sendToNT(motor, "Motors/" + motor->getName());
	}
#endif
}

std::shared_ptr<EctoMotor> &MotorHandler::getMotor(const std::string &name) {
	for (auto &motor : motorControllers) {
		//log->info("Motor Name: {}", motor->getName());
		if (compareIgnoringCase(motor->getName(), name)) {
			return motor;
		}
	}
	throw std::invalid_argument("Could not get motor with the name '" + name + "', it does not exist");
}
