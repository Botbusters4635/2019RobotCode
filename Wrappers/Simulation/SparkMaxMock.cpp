//
// Created by abiel on 11/4/19.
//

#include "rev/CANSparkMax.h"
#include "rev/CANSparkMaxLowLevel.h"
#include "rev/CANPIDController.h"
#include "rev/CANAnalog.h"
#include "rev/CANDigitalInput.h"
#include "rev/CANEncoder.h"
#include "rev/CANError.h"


rev::CANError rev::CANSparkMaxLowLevel::RestoreFactoryDefaults(bool){
	return CANError::kOk;
}

rev::CANEncoder rev::CANSparkMax::GetEncoder(rev::CANEncoder::EncoderType, int){
	;
}

rev::CANError rev::CANEncoder::SetPosition(double){
	return CANError::kOk;
}

rev::CANPIDController rev::CANSparkMax::GetPIDController(){
	;
}

rev::CANAnalog rev::CANSparkMax::GetAnalog(rev::CANAnalog::AnalogMode){
	;
}

rev::CANDigitalInput rev::CANSparkMax::GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity){
	;
}

rev::CANDigitalInput rev::CANSparkMax::GetReverseLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity){
	;
}
rev::CANError rev::CANPIDController::SetReference(double, rev::ControlType, int, double, rev::CANPIDController::ArbFFUnits){
	return CANError::kOk;
}

rev::CANError rev::CANSparkMax::SetClosedLoopRampRate(double){
	return CANError::kOk;
}

rev::CANError rev::CANSparkMax::SetOpenLoopRampRate(double){
	return CANError::kOk;
}

rev::CANError rev::CANSparkMax::SetIdleMode(rev::CANSparkMax::IdleMode){
	return CANError::kOk;
}

double rev::CANSparkMax::GetOutputCurrent(){
	return 0.0;
}

double rev::CANSparkMax::GetBusVoltage() {
	return 0.0;
}

rev::CANError rev::CANDigitalInput::EnableLimitSwitch(bool){
	return CANError ::kOk;
}

rev::CANError rev::CANSparkMax::SetSoftLimit(rev::CANSparkMax::SoftLimitDirection, double){
	return CANError ::kOk;
}

rev::CANError rev::CANPIDController::SetOutputRange(double, double, int){
	return CANError::kOk;
}

rev::CANError rev::CANPIDController::SetP(double, int){
	return CANError::kOk;
}

rev::CANError rev::CANPIDController::SetI(double, int){
	return CANError::kOk;
}

rev::CANError rev::CANPIDController::SetD(double, int){
	return CANError::kOk;
}

rev::CANError rev::CANSparkMax::SetSmartCurrentLimit(unsigned int){
	return CANError::kOk;
}

rev::CANError rev::CANEncoder::SetPositionConversionFactor(double){
	return CANError ::kOk;
}

rev::CANError rev::CANEncoder::SetVelocityConversionFactor(double){
	return CANError ::kOk;
}

double rev::CANEncoder::GetPositionConversionFactor(){
	return 0;
}

double rev::CANSparkMax::GetMotorTemperature() {
	return 0;
}

rev::CANError rev::CANSparkMax::EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection direction, bool enable) {
	return CANError ::kOk;
}

rev::CANError rev::CANPIDController::SetSmartMotionMaxVelocity(double maxVel, int slotID) {
	return CANError::kOk;
}

rev::CANError rev::CANPIDController::SetSmartMotionMaxAccel(double maxAccel, int slotID) {
	return CANError ::kOk;
}

rev::CANError rev::CANAnalog::SetVelocityConversionFactor(double factor) {
	return CANError ::kOk;
}

rev::CANError rev::CANAnalog::SetPositionConversionFactor(double factor) {
	return CANError ::kOk;
}

double rev::CANAnalog::GetVelocity() {
	return 0;
}

double rev::CANAnalog::GetPosition() {
	return 0;
}

double rev::CANEncoder::GetVelocity() {
	return 0;
}

double rev::CANEncoder::GetPosition() {
	return 0;
}

rev::CANError rev::CANPIDController::SetFeedbackDevice(const rev::CANSensor &sensor) {
	return CANError ::kOk;
}

bool rev::CANDigitalInput::Get() const {
	return false;
}

std::string rev::CANSparkMaxLowLevel::GetFirmwareString() {
	return "MockLibrary";
}

rev::CANSparkMaxLowLevel::CANSparkMaxLowLevel(int, rev::CANSparkMaxLowLevel::MotorType) : m_deviceID(0){
	;
}

rev::CANSparkMax::CANSparkMax(int, rev::CANSparkMaxLowLevel::MotorType) : CANSparkMaxLowLevel(0, rev::CANSparkMaxLowLevel::MotorType::kBrushless){
	;
}

rev::CANEncoder::CANEncoder(rev::CANEncoder&& rhs) : CANSensor(*rhs.m_device){
	;
}

rev::CANError rev::CANEncoder::SetInverted(bool inverted) {
	return rev::CANError ::kOk;
}

bool rev::CANEncoder::GetInverted() const {
	return false;
}

void rev::CANSparkMax::Set(double speed) {
	;
}

double rev::CANSparkMax::Get() const {
	return 0.0;
}

void rev::CANSparkMax::SetInverted(bool isInverted) {
	return;
}

bool rev::CANSparkMax::GetInverted() const {
	return false;
}

void rev::CANSparkMax::Disable() {
	;
}

void rev::CANSparkMax::StopMotor() {
	;
}

void rev::CANSparkMax::PIDWrite(double output) {
	;
}

rev::CANSparkMaxLowLevel::~CANSparkMaxLowLevel() {
	;
}

rev::CANError rev::CANAnalog::SetInverted(bool inverted) {
	rev::CANError ::kOk;
}

bool rev::CANAnalog::GetInverted() const {
	return false;
}

int rev::CANAnalog::GetID() const {
	return 0;
}

int rev::CANEncoder::GetID() const {
	return 0;
}