//
// Created by hiram on 9/19/19.
//

#include "EctoPot.h"

EctoPot::EctoPot(int port, double range, double lowerVoltageLimit, double upperVoltageLimit, double offset) {
	input = std::make_unique<frc::AnalogInput>(port);
	this->upperVoltageLimit = upperVoltageLimit;
	this->offset = offset;
	this->lowerVoltageLimit = lowerVoltageLimit;
	this->range = range;
	
	input->SetOversampleBits(6);
	input->SetAverageBits(4);
	
	lastPosition = getPosition();
	lastPositionTime = frc::Timer::GetFPGATimestamp();
}

double EctoPot::PIDGet() {
	return getPosition();
}

double EctoPot::getVoltage() {
	return input->GetVoltage();
}

double EctoPot::getPosition() const {
	lastPosition = (input->GetAverageVoltage() * range / (upperVoltageLimit - lowerVoltageLimit)) - offset;
	lastPositionTime = frc::Timer::GetFPGATimestamp();
	return lastPosition;
}

double EctoPot::getVelocity() const {
	return (getPosition() - lastPosition) / (frc::Timer::GetFPGATimestamp() - lastPositionTime);
}
