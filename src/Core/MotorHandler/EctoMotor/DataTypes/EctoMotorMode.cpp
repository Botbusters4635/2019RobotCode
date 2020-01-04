//
// Created by hiram on 9/08/19.
//

#include <stdexcept>
#include "EctoMotorMode.h"

std::string getStringFromControlMode(EctoControlMode mode) {
	switch (mode) {
		case EctoControlMode::Percent:
			return "Percent";
		case EctoControlMode::Velocity:
			return "Velocity";
		case EctoControlMode::Position:
			return "Position";
		default:
			throw std::invalid_argument("Control mode not yet implemented");
	}
}

EctoControlMode getControlModeFromString(const std::string &mode) {
	if (compareIgnoringCase(mode, "Percent")) return EctoControlMode::Percent;
	else if (compareIgnoringCase(mode, "Velocity")) return EctoControlMode::Velocity;
	else if (compareIgnoringCase(mode, "Position")) return EctoControlMode::Position;
	else throw std::invalid_argument(mode + " is not a valid control mode, options are Percent, Velocity and Position");
}
