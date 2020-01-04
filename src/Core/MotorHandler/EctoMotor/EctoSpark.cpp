//
// Created by hiram on 8/08/19.
//
#include "EctoSpark.h"
#include "EctoMotor.h"

EctoSpark::EctoSpark(int id, const std::string &name) : EctoMotor(id, name) {
	sparkBase = std::make_unique<rev::CANSparkMax>(id, rev::CANSparkMax::MotorType::kBrushless);
	sparkBase->RestoreFactoryDefaults();
	sparkBase->GetEncoder().SetPosition(0);
	pidControllerBase = std::make_unique<rev::CANPIDController>(sparkBase->GetPIDController());
	
	encoderSensor = std::make_unique<rev::CANEncoder>(sparkBase->GetEncoder());
	
	analogSensor = std::make_unique<rev::CANAnalog>(sparkBase->GetAnalog(rev::CANAnalog::AnalogMode::kAbsolute));
	
	forwardLimitSwitch = std::make_unique<rev::CANDigitalInput>(
			sparkBase->GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyOpen));
	reverseLimitSwitch = std::make_unique<rev::CANDigitalInput>(
			sparkBase->GetReverseLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyOpen));
}

void EctoSpark::setClosedLoopOutputRange(double minimum, double maximum) {
	pidControllerBase->SetOutputRange(minimum, maximum);
}

void EctoSpark::invert(bool state) {
	sparkBase->SetInverted(state);
}

bool EctoSpark::isInverted() const {
	return sparkBase->GetInverted();
}

bool EctoSpark::isSensorInverted() const {
	switch (feedbackMode) {
		case EctoMotorFeedback::None:
			return false;
		case EctoMotorFeedback::QuadEncoder:
			return encoderSensor->GetInverted();
		case EctoMotorFeedback::Potentiometer:
			return analogSensor->GetInverted();
		default:
			return false;
	}
}

void EctoSpark::setPIDConfig(const PIDConfig &pidConfig, int profileSlot) {
	//TODO use profile slot
	pidControllerBase->SetP(pidConfig.p);
	pidControllerBase->SetI(pidConfig.i);
	pidControllerBase->SetD(pidConfig.d);
}

void EctoSpark::enableMotorCurrentLimit(bool state) {
	//No way to disable the current limit (probably not a good idea to do so)
	if (state) {
		sparkBase->SetSmartCurrentLimit((unsigned int) std::abs(currentLimit));
	} else {
		log->warn("Current limit for spark motor: {} disabled", getName());
		sparkBase->SetSmartCurrentLimit((unsigned int) std::abs(maximumCurrentLimit));
	}
}

void EctoSpark::setMotorCurrentLimit(double current) {
	sparkBase->SetSmartCurrentLimit((unsigned int) std::abs(current));
}

void EctoSpark::setMotorCurrentTarget(double value) {
	pidControllerBase->SetReference(value,
	                                rev::ControlType::kCurrent, 0, currentFeedForward);
}

void EctoSpark::setClosedLoopRampRate(double rampRate) {
	sparkBase->SetClosedLoopRampRate(rampRate);
}

void EctoSpark::setOpenLoopRampRate(double rampRate) {
	sparkBase->SetOpenLoopRampRate(rampRate);
}

void EctoSpark::setBrakeOnIdle(bool state) {
	sparkBase->SetIdleMode(state ? rev::CANSparkMax::IdleMode::kBrake : rev::CANSparkMax::IdleMode::kCoast);
}


void EctoSpark::invertSensor(bool state) {
	if (feedbackMode == EctoMotorFeedback::None || feedbackMode == EctoMotorFeedback::QuadEncoder) {
		throw std::runtime_error("Cannot invert sensor as it is not defined or its a brushless encoder");
	}
	
	analogSensor->SetInverted(state);
}

double EctoSpark::getPercentOutput() const {
	return sparkBase->Get();
}

void EctoSpark::setPercentOutput(double value) {
	sparkBase->Set(value);
}

void EctoSpark::setPosition(double position) {
	sparkBase->GetEncoder().SetPosition(position / (2.0 * M_PI));
}

void EctoSpark::setVelocityTarget(double velocity) {
	pidControllerBase->SetReference(velocity * 60.0 / (2.0 * M_PI),
	                                rev::ControlType::kVelocity, 0, currentFeedForward);
}

void EctoSpark::setEncoderCodes(int codes) {
	if (codes == 0) {
		log->warn("Encoder codes set to zero in motor with name: {}, config not applied", codes);
		return;
	}
	
	sparkBase->GetEncoder().SetPositionConversionFactor(42.0 / codes);
	sparkBase->GetEncoder().SetVelocityConversionFactor(42.0 / codes);
	
}

int EctoSpark::getEncoderCodes() const {
	return sparkBase->GetEncoder().GetPositionConversionFactor() * 42;
}


double EctoSpark::getMotorTemperature() const {
	return sparkBase->GetMotorTemperature();
}

double EctoSpark::getMotorCurrent() const {
	return sparkBase->GetOutputCurrent();
}

double EctoSpark::getMotorVoltage() const {
	return sparkBase->GetBusVoltage();
}

void EctoSpark::setArbitraryFeedForward(double feedForward) {
	if (std::abs(feedForward) > 32.0) {
		log->error("Invalid feedforward: {} given to EctoSpark with id: {}", feedForward, id);
		return;
	}
	
	this->currentFeedForward = feedForward;
}

void EctoSpark::disable() {
	sparkBase->Disable();
	disabled = true;
}

bool EctoSpark::isDisabled() const {
	return disabled;
}

void EctoSpark::factoryReset() {
	sparkBase->RestoreFactoryDefaults(false);
}

void EctoSpark::enableLimitSwitches(bool state) {
	forwardLimitSwitch->EnableLimitSwitch(state);
	reverseLimitSwitch->EnableLimitSwitch(state);
}

void EctoSpark::setForwardSoftLimit(double radians) {
	sparkBase->SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, ((radians / (2.0 * M_PI))));
}

void EctoSpark::enableForwardSoftLimit(bool state) {
	sparkBase->EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, state);
}

void EctoSpark::setReverseSoftLimit(double radians) {
	sparkBase->SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, (radians / (2.0 * M_PI)));
}

void EctoSpark::enableReverseSoftLimit(bool state) {
	sparkBase->EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, state);
}

void EctoSpark::disableLimits() {
	log->warn("Disabling limits for motor: {}", name);
	
	setForwardSoftLimit(false);
	setReverseSoftLimit(false);
	
	enableLimitSwitches(false);
}

void EctoSpark::configureMotionMagicVelocity(double velocity) {
	//rad/s to rpm
	pidControllerBase->SetSmartMotionMaxVelocity((velocity / (M_PI * 2.0)) * 60.0);
}

void EctoSpark::configureMotionMagicAcceleration(double acceleration) {
	//rad/s^2 to rpm/min
	pidControllerBase->SetSmartMotionMaxAccel((acceleration / (M_PI * 2.0)) * std::pow(60.0, 2.0));
}

void EctoSpark::configureMotionMagicSCurve(double sCurve) {
	log->error("Motion magic SCurves are still not implemented in Spark Max API");
}

void EctoSpark::setMotionMagicTarget(double value) {
	pidControllerBase->SetReference(value / (2.0 * M_PI),
	                                rev::ControlType::kSmartMotion, 0, currentFeedForward);
}


void EctoSpark::setAnalogPositionConversionFactor(double conversionFactor) {
	analogSensor->SetPositionConversionFactor(conversionFactor);
}

void EctoSpark::setAnalogVelocityConversionFactor(double conversionFactor) {
	analogSensor->SetVelocityConversionFactor(conversionFactor);
}

void EctoSpark::setPositionTarget(double position) {
	pidControllerBase->SetReference(position / (2.0 * M_PI),
	                                rev::ControlType::kPosition, 0, currentFeedForward);
}

#include <frc/Timer.h>

double EctoSpark::getPotPosition() const {
	double currentTime = frc::Timer::GetFPGATimestamp();
	if (currentTime - lastPotRunTime >= sensorReadTimeout) {
		double pos = analogSensor->GetPosition();
		pos -= analogOffset;
		
		if (pos < 0) {
			pos += 2 * M_PI;
		} else if (pos > 2 * M_PI) {
			pos -= 2 * M_PI;
		}
		
		if (pos > M_PI) {
			pos -= 2 * M_PI;
		} else if (pos < -M_PI) {
			pos += 2 * M_PI;
		}
		
		lastPotSensorRead = pos;
		lastPotRunTime = currentTime;
	}
	return lastPotSensorRead;
}

double EctoSpark::getPotVelocity() const {
	return analogSensor->GetVelocity();
}

double EctoSpark::getQuadPosition() const {
	return encoderSensor->GetPosition() * (2.0 * M_PI);
}

double EctoSpark::getQuadVelocity() const {
	return (analogSensor->GetVelocity() / 60.0) * (2.0 * M_PI);
}

void EctoSpark::setPotAsClosedLoopSource() {
	pidControllerBase->SetFeedbackDevice(*analogSensor);
}

void EctoSpark::setQuadAsClosedLoopSource() {
	pidControllerBase->SetFeedbackDevice(*encoderSensor);
}

void EctoSpark::setAnalogOffset(double analogOffset) {
	EctoSpark::analogOffset = analogOffset;
}

std::string EctoSpark::getFirmwareVersion() const {
	return sparkBase->GetFirmwareString();
}

void EctoSpark::setSwitchPolarity(bool normallyClosed) {
	if (normallyClosed) {
		forwardLimitSwitch = std::make_unique<rev::CANDigitalInput>(
				sparkBase->GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed));
		reverseLimitSwitch = std::make_unique<rev::CANDigitalInput>(
				sparkBase->GetReverseLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed));
	} else {
		forwardLimitSwitch = std::make_unique<rev::CANDigitalInput>(
				sparkBase->GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyOpen));
		reverseLimitSwitch = std::make_unique<rev::CANDigitalInput>(
				sparkBase->GetReverseLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyOpen));
	}
	
}

bool EctoSpark::getReverseLimitSwitch() const {
	return reverseLimitSwitch->Get();
}

bool EctoSpark::getForwardLimitSwitch() const {
	return forwardLimitSwitch->Get();
}