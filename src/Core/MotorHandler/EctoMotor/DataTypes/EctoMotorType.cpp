//
// Created by hiram on 9/08/19.
//

#include <stdexcept>
#include "EctoMotorType.h"

std::string getStringFromMotorType(EctoMotorType type) {
	switch (type) {
		case EctoMotorType::PWM:
			return "PWM";
		case EctoMotorType::TalonSRX:
			return "TalonSRX";
		case EctoMotorType::SparkMax:
			return "SparkMax";
		case EctoMotorType::Empty:
			return "Empty";
		default:
			return "InvalidType";
	}
}

EctoMotorType getMotorTypeFromString(const std::string &type) {
	if (compareIgnoringCase(type, "PWM")) return EctoMotorType::PWM;
	else if (compareIgnoringCase(type, "TalonSRX")) return EctoMotorType::TalonSRX;
	else if (compareIgnoringCase(type, "SparkMax")) return EctoMotorType::SparkMax;
	else {
		throw std::runtime_error("Type " + type + " doesn't exist.");
	}
}
