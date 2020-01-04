//
// Created by hiram on 8/08/19.
//
#include "EctoTalon.h"

//TODO Add support for aux closed loop (maybe)
EctoTalon::EctoTalon(int id, const std::string &name) : EctoMotor(id, name) {
	talonBase = std::make_unique<TalonSRX>(id);
	//talonBase->ConfigSelectedFeedbackSensor(TalonSRXFeedbackDevice::QuadEncoder);
	//talonBase->SetSelectedSensorPosition(0);
	
	this->setArbitraryFeedForward(0.0);
}

void EctoTalon::setClosedLoopOutputRange(double minimum, double maximum) {
	talonBase->ConfigClosedLoopPeakOutput(0, maximum);
}

void EctoTalon::invert(bool state) {
	talonBase->SetInverted(state);
}

bool EctoTalon::isInverted() const {
	return talonBase->GetInverted();
}

void EctoTalon::invertSensor(bool state) {
	talonBase->SetSensorPhase(state);
	sensorInverted = state;
}

bool EctoTalon::isSensorInverted() const {
	return sensorInverted;
}

double EctoTalon::getPercentOutput() const {
	return talonBase->GetMotorOutputPercent();
}

void EctoTalon::setPercentOutput(double value) {
	talonBase->Set(ControlMode::PercentOutput, value);
}

void EctoTalon::setPosition(double position) {
	talonBase->SetSelectedSensorPosition((int) ((position * (double) getEncoderCodes()) / (M_PI * 2.0)));
}

void EctoTalon::setPositionTarget(double position) {
	talonBase->Set(ControlMode::Position,
	               (position / (M_PI * 2.0)) * (double) getEncoderCodes(),
	               DemandType::DemandType_ArbitraryFeedForward, this->currentFeedForward);
}

void EctoTalon::setBrakeOnIdle(bool state) {
	talonBase->SetNeutralMode(state ? NeutralMode::Brake : NeutralMode::Coast);
}

void EctoTalon::setPIDConfig(const PIDConfig &pidConfig, int profileSlot) {
	talonBase->SelectProfileSlot(profileSlot, 0);
	talonBase->Config_kP(profileSlot, pidConfig.p);
	talonBase->Config_kI(profileSlot, pidConfig.i);
	talonBase->Config_kD(profileSlot, pidConfig.d);
	talonBase->Config_kF(profileSlot, pidConfig.f);
}

void EctoTalon::enableMotorCurrentLimit(bool state) {
	talonBase->EnableCurrentLimit(state);
}

void EctoTalon::setMotorCurrentLimit(double current) {
	talonBase->ConfigContinuousCurrentLimit(current);
}

void EctoTalon::setClosedLoopRampRate(double rampRate) {
	talonBase->ConfigClosedloopRamp(rampRate);
}

void EctoTalon::setOpenLoopRampRate(double rampRate) {
	talonBase->ConfigOpenloopRamp(rampRate);
}

double EctoTalon::getMotorTemperature() const {
	return talonBase->GetTemperature();
}

double EctoTalon::getMotorCurrent() const {
	return talonBase->GetOutputCurrent();
}

void EctoTalon::setMotorCurrentTarget(double value) {
	talonBase->Set(ControlMode::Current, value, DemandType_ArbitraryFeedForward, this->currentFeedForward);
}

double EctoTalon::getMotorVoltage() const {
	return talonBase->GetBusVoltage();
}

void EctoTalon::setArbitraryFeedForward(double feedForward) {
	if (feedForward == 0) {
		this->currentFeedForward = 0;
		return;
	}
	
	this->currentFeedForward = getMotorVoltage() / feedForward;
}

void EctoTalon::disable() {
	talonBase->Set(ControlMode::Disabled, 0);
	disabled = true;
}

void EctoTalon::enableLimitSwitches(bool state) {
	talonBase->OverrideLimitSwitchesEnable(state);
	areLimitSwitchesEnabled = state;
}

void EctoTalon::setForwardSoftLimit(double radians) {
	talonBase->ConfigForwardSoftLimitThreshold((int) (radians / (M_PI * 2.0)) * getEncoderCodes());
}

void EctoTalon::enableForwardSoftLimit(bool state) {
	talonBase->ConfigForwardSoftLimitEnable(state);
}

void EctoTalon::setReverseSoftLimit(double radians) {
	talonBase->ConfigReverseSoftLimitThreshold((int) (radians / (M_PI * 2.0)) * getEncoderCodes());
}

void EctoTalon::enableReverseSoftLimit(bool state) {
	talonBase->ConfigReverseSoftLimitEnable(state);
}

void EctoTalon::disableLimits() {
	log->warn("Disabling limits for motor: {}", name);
}

void EctoTalon::configureMotionMagicVelocity(double velocity) {
	talonBase->ConfigMotionCruiseVelocity((int) (((velocity / (M_PI * 2.0)) * getEncoderCodes()) / 10.0));
}

void EctoTalon::configureMotionMagicAcceleration(double acceleration) {
	talonBase->ConfigMotionAcceleration((int) (((acceleration / (M_PI * 2.0)) * getEncoderCodes()) / 10.0));
}

void EctoTalon::configureMotionMagicSCurve(double sCurve) {
	talonBase->ConfigMotionSCurveStrength(sCurve);
}

void EctoTalon::setAnalogPositionConversionFactor(double conversionFactor) {
	throw std::runtime_error("2 lazy to implement right now");
}

void EctoTalon::setAnalogVelocityConversionFactor(double conversionFactor) {
	throw std::runtime_error("2 lazy to implement right now");
}

void EctoTalon::setEncoderCodes(int codes) {
	if (codes <= 0) {
		throw std::runtime_error("Encoder codes cant be negative or zero on motor with name " + name);
	}
	encoderCodes = codes;
}

int EctoTalon::getEncoderCodes() const {
	return encoderCodes;
}

bool EctoTalon::isDisabled() const {
	return disabled;
}

void EctoTalon::setMotionMagicTarget(double value) {
	talonBase->Set(ControlMode::MotionMagic, (value / (M_PI * 2.0)) * (double) getEncoderCodes(),
	               DemandType::DemandType_ArbitraryFeedForward, this->currentFeedForward);
}

double EctoTalon::getPotPosition() const {
	if (feedbackMode == EctoMotorFeedback::Potentiometer) {
		return talonBase->GetSelectedSensorPosition();
	}
	
	log->info("Asking for potentiometer position but feedback mode specifies a different mode " + name);
	return 0;
}

double EctoTalon::getPotVelocity() const {
	if (feedbackMode == EctoMotorFeedback::Potentiometer) {
		return talonBase->GetSelectedSensorVelocity();
	}
	
	log->info("Asking for potentiometer velocity but feedback mode specifies a different mode " + name);
	return 0;
}

double EctoTalon::getQuadPosition() const {
	if (feedbackMode == EctoMotorFeedback::QuadEncoder) {
		return talonBase->GetSelectedSensorPosition();
	}
	
	log->info("Asking for quadrature position but feedback mode specifies a different mode " + name);
	return 0;
}

double EctoTalon::getQuadVelocity() const {
	if (feedbackMode == EctoMotorFeedback::QuadEncoder) {
		return talonBase->GetSelectedSensorVelocity();
	}
	
	log->info("Asking for quadrature velocity but feedback mode specifies a different mode " + name);
	return 0;
}

void EctoTalon::setPotAsClosedLoopSource() {
	talonBase->ConfigSelectedFeedbackSensor(TalonSRXFeedbackDevice::Analog);
}

void EctoTalon::setQuadAsClosedLoopSource() {
	talonBase->ConfigSelectedFeedbackSensor(TalonSRXFeedbackDevice::QuadEncoder);
}

void EctoTalon::setVelocityTarget(double value) {
	talonBase->Set(ControlMode::Velocity,
	               ((value / (M_PI * 2.0) * (double) getEncoderCodes())) / 10.0,
	               DemandType::DemandType_ArbitraryFeedForward, this->currentFeedForward);
}

void EctoTalon::factoryReset() {
//	/talonBase->ConfigFactoryDefault(100);
}

std::string EctoTalon::getFirmwareVersion() const {
	//Returns firmware value as one int 4.22 would be 0x0422
	int firmwareVer = talonBase->GetFirmwareVersion();
	
	//Get first 2 bytes and bitshift 2 bytes, get last 2 bytes
	return fmt::format("{}.{}", std::to_string((firmwareVer & 0xFF00) >> 8), std::to_string((firmwareVer & 0x00FF)));
}

void EctoTalon::setSwitchPolarity(bool normallyClosed) {
	throw std::runtime_error("A");
}

bool EctoTalon::getForwardLimitSwitch() const {
	throw std::runtime_error("A");
}

bool EctoTalon::getReverseLimitSwitch() const {
	throw std::runtime_error("A");
}

void EctoTalon::setAnalogOffset(double analogOffset) {
	throw std::runtime_error("A");
}