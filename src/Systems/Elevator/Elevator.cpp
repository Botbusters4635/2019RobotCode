//
// Created by Abiel on 9/9/19.
//

#include "Elevator.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>
#include <iostream>

Elevator::Elevator(const std::string &elevatorName, const std::shared_ptr<EctoMotor> &motor,
                   const ElevatorConfig &config) : System(elevatorName) {
	this->config = config;
	this->motor = motor;
	
	pidConfig.p = 0.000140;
	pidConfig.i = 0.000000;
	pidConfig.d = 0.0000004;
	pidConfig.deadband = 0.005;
	
	motor->setPIDConfig(pidConfig, 0);
	
	if (config.gearReduction <= 0 || config.winchDiameter <= 0) {
		log->error("Invalid gear reduction: {} or winch diameter: {}", config.gearReduction, config.winchDiameter);
		throw std::runtime_error("Invalid gear reduction or winch diameter");
	}
	
	winchCircumference = config.winchDiameter * M_PI;
	
	if (config.useMagicMotion) {
		if (config.maximumVelocity <= 0 || config.maximumAcceleration <= 0) {
			log->error("Invalid maximum velocity: {} or maximum acceleration: {}", config.maximumVelocity,
			           config.maximumAcceleration);
		}
		
		motor->configureMotionMagicVelocity(convertHeightToRadians(config.maximumVelocity));
		motor->configureMotionMagicAcceleration(convertHeightToRadians(config.maximumAcceleration));
		motor->setControlMode(EctoControlMode::MotionMagic);
	} else {
		motor->setControlMode(EctoControlMode::Position);
	}
	
	/**
	 * Motor Config
	 */
	motor->setClosedLoopRampRate(0.01);
	
	motor->setMotorCurrentLimit(30);
	motor->enableMotorCurrentLimit(true);
	
	motor->invert(true);
	
	motor->setSwitchPolarity(true);
	motor->enableLimitSwitches(true);
	
	motor->setBrakeOnIdle(true);
	
	motor->setForwardSoftLimit(convertHeightToRadians(config.forwardHeightLimit));
	log->info("Height to radians: {} radians to height: {}", convertHeightToRadians(config.forwardHeightLimit),
	          convertRadiansToHeight(convertHeightToRadians(config.forwardHeightLimit)));
	motor->setReverseSoftLimit(convertHeightToRadians(config.reverseHeightLimit));
	
	motor->enableForwardSoftLimit(config.enableForwardSoftLimt);
	motor->enableReverseSoftLimit(config.enableReverseSoftLimit);
	
	motor->setArbitraryFeedForward(1.5);
}

void Elevator::setHeight(double height) {
	frc::SmartDashboard::PutNumber("Elevator/SetHeight", height);
	
	if (!hasAutoHomed) {
		return;
	}
	
	if(previousHeight == height){
		return;
	}
	
	if (config.voltageTestMode) {
		motor->setControlMode(EctoControlMode::Percent);
		motor->set(height);
		return;
	}
	
	if (height > config.forwardHeightLimit || height < config.reverseHeightLimit) {
		log->error("Invalid height: {} given to elevator: {}", height, getName());
	}
	
	motor->set(convertHeightToRadians(height), EctoControlMode::MotionMagic);
	previousHeight = height;
}

double Elevator::getHeight() const {
	return convertRadiansToHeight(motor->getPosition());
}


inline double Elevator::convertHeightToRadians(double height) const {
	return (height / winchCircumference) * (M_PI * 2.0) * config.gearReduction;
}

inline double Elevator::convertRadiansToHeight(double radians) const {
	return (radians / (M_PI * 2.0)) / config.gearReduction * winchCircumference;
}

void Elevator::homeElevator() {
	hasAutoHomed = false;
	homeStartTime = frc::Timer::GetFPGATimestamp();
}

void Elevator::initRobot() {
	homeStartTime = frc::Timer::GetFPGATimestamp();
	hasAutoHomed = false;
}

void Elevator::updateRobot() {
	frc::SmartDashboard::PutNumber("Elevator/ElevatorHeight", getHeight());
	frc::SmartDashboard::PutBoolean("Elevator/HasAutoHomed", hasAutoHomed);
	
	/**
	 * Limit switch checking
	 */
	if (!hasAutoHomed and frc::Timer::GetFPGATimestamp() - lastHomeCheckTime > homeCheckWaitTime) {
		frc::SmartDashboard::PutBoolean("Elevator/HomeLimitSwitch", motor->getReverseLimitSwitch());
		if (motor->getReverseLimitSwitch()){
			motor->setPosition(0.1);
			motor->setControlMode(EctoControlMode::MotionMagic);
			hasAutoHomed = true;
			return;
		}
		
		if(frc::Timer::GetFPGATimestamp() - homeStartTime >= autoHomeTimeout){
			log->warn("{} auto home has timed out, disabling elevator", getName());
			motor->set(0, EctoControlMode::Percent);
		} else {
			motor->setPosition(1.0);
			motor->set(-0.4, EctoControlMode::Percent);
		}
		
		lastHomeCheckTime = frc::Timer::GetFPGATimestamp();
		return;
	}
	
	if (frc::Timer::GetFPGATimestamp() - lastLimitSwitchCheck > limitSwitchCheckTimeout) {
		if (motor->getReverseLimitSwitch()) {
			motor->setPosition(0);
		}
		
		lastLimitSwitchCheck = frc::Timer::GetFPGATimestamp();
	}
	
	const double elevatorHeight = getHeight();
	
	if(elevatorHeight > .2666 and elevatorHeight < .515){
		frc::SmartDashboard::PutBoolean("Elevator/IsCameraBlocked", true);
	} else {
		frc::SmartDashboard::PutBoolean("Elevator/IsCameraBlocked", false);
	}
}

void Elevator::initDisabled() {
	//Reset home timeout
	homeStartTime = frc::Timer::GetFPGATimestamp();
}

bool Elevator::isAutoHoming() const {
	return !hasAutoHomed;
}