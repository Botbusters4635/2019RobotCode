//
// Created by abiel on 9/10/19.
//

#include "MotorCharacterizationHelper.h"

MotorCharacterizationHelper::MotorCharacterizationHelper(const std::string &name,
                                                         const std::shared_ptr<EctoMotor> &motor) : System(name) {
	this->motor = motor;
	motor->setControlMode(EctoControlMode::Percent);
}

void MotorCharacterizationHelper::initRobot() {
	log->warn("MotorCharacterizationHelper enabled for motor: {}", motor->getName());
	nt::NetworkTableInstance::GetDefault().SetUpdateRate(0.010);
	
	motor->set(0);
}

void MotorCharacterizationHelper::updateRobot() {
	frc::SmartDashboard::PutNumber("encoder_pos", (motor->getPosition() / (M_PI * 2.0)));
	frc::SmartDashboard::PutNumber("encoder_rate", (motor->getVelocity() / (M_PI * 2.0)));
	
	double batteryVoltage = frc::RobotController::GetInputVoltage();
	double motorVoltage = motor->getMotorVoltage();
	
	double autoSpeed = autoSpeedEntry.GetDouble(0);
	priorAutoSpeed = autoSpeed;
	
	double numberArray[]{frc::Timer::GetFPGATimestamp(),
	                     batteryVoltage,
	                     autoSpeed,
	                     motorVoltage,
	                     motor->getPosition() / (M_PI * 2.0),
	                     motor->getVelocity() / (M_PI * 2.0)};
	
	motor->set(autoSpeed);
	
	telemetryEntry.SetDoubleArray(numberArray);
}