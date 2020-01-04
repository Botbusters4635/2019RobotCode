//
// Created by Abiel on 8/13/18.
//

#include "InputHandlers/SystemInputHandlers/TankDifferentialDrive.h"
#include "InputHandlers/InputUtils.h"

TankDifferentialDrive::TankDifferentialDrive(const TankDifferentialDriveConfig &config) {
	this->config = config;
}

void TankDifferentialDrive::init() {
	;
}

InputValue TankDifferentialDrive::calculateInputs(const InputValue &joystickInputs) const {
	InputValue outputValue = joystickInputs;

	if (config.enableDeadzone) {
		outputValue.setLeftVel(InputUtils::applyDeadzone(joystickInputs.getLeftVel(), config.leftDeadzone));
		outputValue.setRightVel(InputUtils::applyDeadzone(joystickInputs.getRightVel(), config.rightDeadzone));
	}

	if (config.enableExponential) {
		outputValue.setLeftVel(InputUtils::applyExponentialCurve(outputValue.getLeftVel(), config.leftExponential));
		outputValue.setRightVel(InputUtils::applyExponentialCurve(outputValue.getRightVel(), config.rightDeadzone));
	}

	return outputValue;
}