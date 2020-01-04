//
// Created by abiel on 12/30/19.
//

#include "EctoMotorSimulated.h"

EctoMotorSimulated::EctoMotorSimulated(int id, const std::string &name) : EctoMotor(id, name) {
	;
}

void EctoMotorSimulated::factoryReset() {
	log->info("Factory reseted simulated motor with name: {}", name);
}

void EctoMotorSimulated::setSwitchPolarity(bool normallyClosed) {
	this->switchPolarity = normallyClosed;
}

std::string EctoMotorSimulated::getFirmwareVersion() const {
	return "Simulated";
}

void EctoMotorSimulated::invert(bool state) {
	this->inverted = state;
}

bool EctoMotorSimulated::isInverted() const {
	return inverted;
}

void EctoMotorSimulated::invertSensor(bool state) {
	this->sensorInverted = state;
}

bool EctoMotorSimulated::isSensorInverted() const {
	return sensorInverted;
}

void EctoMotorSimulated::setPIDConfig(const PIDConfig &pidConfig, int profileSlot) {
	this->pidConfigs[profileSlot] = pidConfig;
}

void EctoMotorSimulated::setBrakeOnIdle(bool state) {
	this->isBrakeEnabled = state;
}

void EctoMotorSimulated::enableMotorCurrentLimit(bool state) {
	this->isMotorCurrentLimitEnabled = state;
}

void EctoMotorSimulated::setMotorCurrentLimit(double current) {
	this->currentLimit = current;
}

void EctoMotorSimulated::setMotorCurrentTarget(double value) {
	;
}

void EctoMotorSimulated::setClosedLoopOutputRange(double minimum, double maximum) {
	this->minimumOutputRate = minimum;
	this->maximumOutputRate = maximum;
}

void EctoMotorSimulated::setClosedLoopRampRate(double rampRate) {
	this->closedLoopRampRate = rampRate;
}

void EctoMotorSimulated::setOpenLoopRampRate(double rampRate) {
	this->openLoopRampRate = rampRate;
}

void EctoMotor::setPercentOutput(double value) {
	;
}

double EctoMotorSimulated::getPercentOutput() const {
	return 0;
}

void EctoMotorSimulated::setPosition(double position) {
	this->currentPosition = position;
}

void EctoMotorSimulated::setPositionTarget(double position) {
	this->positionTarget = position;
}

void EctoMotorSimulated::setVelocityTarget(double velocity) {
	this->velocityTarget = velocity;
}

double EctoMotorSimulated::getMotorTemperature() const {
	return 0;
}

double EctoMotorSimulated::getMotorCurrent() const {
	return 0;
}

double EctoMotorSimulated::getMotorVoltage() const {
	return 12.0;
}

void EctoMotorSimulated::setEncoderCodes(int codes) {
	this->encoderCodes = codes;
}

int EctoMotorSimulated::getEncoderCodes() const {
	return this->encoderCodes;
}

void EctoMotorSimulated::setArbitraryFeedForward(double feedForward) {
	;
}

void EctoMotorSimulated::disable() {
	;
}

bool EctoMotorSimulated::isDisabled() const {
	return false;
}

void EctoMotorSimulated::enableLimitSwitches(bool state) {
	;
}

void EctoMotorSimulated::setForwardSoftLimit(double radians) {
	;
}

void EctoMotorSimulated::setReverseSoftLimit(double radians) {
	;
}

void EctoMotorSimulated::enableReverseSoftLimit(bool state) {
	;
}

bool EctoMotorSimulated::getReverseLimitSwitch() const {
	return false;
}

bool EctoMotorSimulated::getForwardLimitSwitch() const {
	return false;
}

void EctoMotorSimulated::disableLimits() {
	;
}

void EctoMotorSimulated::configureMotionMagicVelocity(double velocity) {
	;
}

void EctoMotorSimulated::configureMotionMagicAcceleration(double acceleration) {
	;
}

void EctoMotorSimulated::setMotionMagicTarget(double value) {
	;
}

double EctoMotorSimulated::getPotPosition() const {
	return 0;
}

double EctoMotorSimulated::getPotVelocity() const {
	return 0;
}

double EctoMotorSimulated::getQuadPosition() const {
	return 0;
}

double EctoMotorSimulated::getQuadVelocity() const {
	return 0;
}

void EctoMotorSimulated::setPotAsClosedLoopSource() {
	;
}

void EctoMotorSimulated::setQuadAsClosedLoopSource() {
	;
}

void EctoMotorSimulated::setAnalogOffset(double analogOffset) {
	;
}

void EctoMotorSimulated::enableForwardSoftLimit(bool state) {
	;
}

void EctoMotorSimulated::setAnalogPositionConversionFactor(double factor) {
	;
}

void EctoMotorSimulated::setAnalogVelocityConversionFactor(double factor) {
	;
}

void EctoMotorSimulated::configureMotionMagicSCurve(double sCurve) {
	;
}

void EctoMotorSimulated::setPercentOutput(double value) {
	;
}