//
// Created by hiram on 9/17/19.
//

#include "MotorStaticVoltageHelper.h"

MotorStaticVoltageHelper::MotorStaticVoltageHelper(const std::string &name, const std::shared_ptr<EctoMotor> &motor) : System(
		name) {
	this->motor = motor;
}

void MotorStaticVoltageHelper::updateRobot() {
	double voltage = motor->getMotorVoltage();
	if (motor->getVelocity() > 0.5 && voltage < voltageToMove) {
		voltageToMove = voltage;
	}
}

double MotorStaticVoltageHelper::getVoltageToMove() const {
	return voltageToMove;
}


