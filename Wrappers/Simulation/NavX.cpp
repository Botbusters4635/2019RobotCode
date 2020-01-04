//
// Created by Abiel on 1/6/19.
//

#include "NavX.h"

NavX::NavX() {
	;
}

float NavX::GetPitch() const {
	return pitch;
}

void NavX::SetPitch(float pitch) {
	NavX::pitch = pitch;
}

float NavX::GetRoll() const {
	return roll;
}

void NavX::SetRoll(float roll) {
	NavX::roll = roll;
}

float NavX::GetYaw() const {
	return yaw;
}

void NavX::SetYaw(float yaw) {
	NavX::yaw = yaw;
}

float NavX::GetCompassHeading() const {
	return compassHeading;
}

void NavX::SetCompassHeading(float compassHeading) {
	NavX::compassHeading = compassHeading;
}

float NavX::GetLinearAccelX() const {
	return linearAccelX;
}

void NavX::SetLinearAccelX(float linearAccelX) {
	NavX::linearAccelX = linearAccelX;
}

float NavX::GetLinearAccelY() const {
	return linearAccelY;
}

void NavX::SetLinearAccelY(float linearAccelY) {
	NavX::linearAccelY = linearAccelY;
}

float NavX::GetLinearAccelZ() const {
	return linearAccelZ;
}

void NavX::SetLinearAccelZ(float linearAccelZ) {
	NavX::linearAccelZ = linearAccelZ;
}

bool NavX::isIsMoving() const {
	return isMoving;
}

void NavX::SetIsMoving(bool isMoving) {
	NavX::isMoving = isMoving;
}

bool NavX::isIsRotating() const {
	return isRotating;
}

void NavX::SetIsRotating(bool isRotating) {
	NavX::isRotating = isRotating;
}

float NavX::GetFusedHeading() const {
	return fusedHeading;
}

void NavX::SetFusedHeading(float fusedHeading) {
	NavX::fusedHeading = fusedHeading;
}

bool NavX::IsMagneticDisturbance() const {
	return isMagneticDisturbance;
}

void NavX::SetIsMagneticDisturbance(bool isMagneticDisturbance) {
	NavX::isMagneticDisturbance = isMagneticDisturbance;
}

bool NavX::isIsMagnetometerCalibrated() const {
	return isMagnetometerCalibrated;
}

void NavX::SetIsMagnetometerCalibrated(bool isMagnetometerCalibrated) {
	NavX::isMagnetometerCalibrated = isMagnetometerCalibrated;
}

float NavX::GetVelocityX() const {
	return velocityX;
}

void NavX::SetVelocityX(float velocityX) {
	NavX::velocityX = velocityX;
}

float NavX::GetVelocityY() const {
	return velocityY;
}

void NavX::SetVelocityY(float velocityY) {
	NavX::velocityY = velocityY;
}

float NavX::GetVelocityZ() const {
	return velocityZ;
}

void NavX::SetVelocityZ(float velocityZ) {
	NavX::velocityZ = velocityZ;
}

float NavX::GetDisplacementX() const {
	return displacementX;
}

void NavX::SetDisplacementX(float displacementX) {
	NavX::displacementX = displacementX;
}

float NavX::GetDisplacementY() const {
	return displacementY;
}

void NavX::SetDisplacementY(float displacementY) {
	NavX::displacementY = displacementY;
}

float NavX::GetDisplacementZ() const {
	return displacementZ;
}

void NavX::SetDisplacementZ(float displacementZ) {
	NavX::displacementZ = displacementZ;
}

double NavX::GetAngle() const {
	return angle;
}

void NavX::SetAngle(double angle) {
	NavX::angle = angle;
}

double NavX::GetRate() const {
	return rate;
}

void NavX::SetRate(double rate) {
	NavX::rate = rate;
}

float NavX::GetRawGyroX() const {
	return rawGyroX;
}

void NavX::SetRawGyroX(float rawGyroX) {
	NavX::rawGyroX = rawGyroX;
}

float NavX::GetRawGyroY() const {
	return rawGyroY;
}

void NavX::SetRawGyroY(float rawGyroY) {
	NavX::rawGyroY = rawGyroY;
}

float NavX::GetRawGyroZ() const {
	return rawGyroZ;
}

void NavX::SetRawGyroZ(float rawGyroZ) {
	NavX::rawGyroZ = rawGyroZ;
}

float NavX::GetRawAccelX() const {
	return rawAccelX;
}

void NavX::SetRawAccelX(float rawAccelX) {
	NavX::rawAccelX = rawAccelX;
}

float NavX::GetRawAccelY() const {
	return rawAccelY;
}

void NavX::SetRawAccelY(float rawAccelY) {
	NavX::rawAccelY = rawAccelY;
}

float NavX::GetRawAccelZ() const {
	return rawAccelZ;
}

void NavX::SetRawAccelZ(float rawAccelZ) {
	NavX::rawAccelZ = rawAccelZ;
}

float NavX::GetRawMagX() const {
	return rawMagX;
}

void NavX::SetRawMagX(float rawMagX) {
	NavX::rawMagX = rawMagX;
}

float NavX::GetRawMagY() const {
	return rawMagY;
}

void NavX::SetRawMagY(float rawMagY) {
	NavX::rawMagY = rawMagY;
}

float NavX::GetRawMagZ() const {
	return rawMagZ;
}

void NavX::SetRawMagZ(float rawMagZ) {
	NavX::rawMagZ = rawMagZ;
}

std::string NavX::GetFirmwareVersion() {
	return std::string("SIM");
}

void NavX::ResetDisplacement() {
	;
}

void NavX::ClearError() {
	;
}

void NavX::ZeroYaw() {
	;
}

void NavX::Reset() {
	;
}

double NavX::PIDGet() {
	return 0.0;
}