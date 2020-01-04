//
// Created by abiel on 9/11/19.
//

#include "MotorPidTunerHelper.h"

MotorPIDTunerHelper::MotorPIDTunerHelper(const std::string &name, const MotorPIDTunerHelperConfig &config,
                                         const std::shared_ptr<EctoMotor> &motor) : System(name) {
	this->config = config;
	
	motor->setControlMode(config.motorMode);
	
	motor->setPIDConfig(config.pidConfig, 0);
	
	motor->setClosedLoopOutputRange(-config.maximumPercent, config.maximumPercent);
	motor->setMotorCurrentLimit(config.currentLimit);
	
	motor->setClosedLoopRampRate(config.closedLoopRampRate);
}