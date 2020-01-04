//
// Created by hiram on 9/08/19.
//

#include <stdexcept>
#include <cmath>
#include <chrono>
#include "EctoMotor.h"

std::shared_ptr<spdlog::logger> EctoMotor::log = spdlog::stdout_color_mt("EctoMotor");

EctoMotor::EctoMotor(int id, const std::string &name) {
	this->id = id;
	this->name = name;
	
	log->trace("Creating motor with name {} and id {}...", name, id);
}

void EctoMotor::set(double value) {
	this->set(value, this->controlMode);
}

void EctoMotor::set(double value, EctoControlMode controlMode) {
	this->controlMode = controlMode;
	switch (this->controlMode) {
		case EctoControlMode::Percent:
			this->setPercentOutput(value);
			break;
		case EctoControlMode::Velocity:
			this->setVelocityTarget(value);
			break;
		case EctoControlMode::Position:
			this->setPositionTarget(value);
			break;
		case EctoControlMode::MotionMagic:
			this->setMotionMagicTarget(value);
			break;
		case EctoControlMode::Current:
			this->setMotorCurrentTarget(value);
			break;
	}
}

std::string EctoMotor::getName() const {
	return name;
}

void EctoMotor::setControlMode(EctoControlMode controlMode) {
	this->controlMode = controlMode;
}

EctoControlMode EctoMotor::getControlMode() const {
	return this->controlMode;
}

void EctoMotor::setFeedbackMode(EctoMotorFeedback feedbackMode) {
	this->feedbackMode = feedbackMode;
	switch (this->feedbackMode) {
		case EctoMotorFeedback::None:
			throw std::runtime_error("Cant set feedbackmode to None in motor with name: " + name);
		case EctoMotorFeedback::QuadEncoder:
			this->setQuadAsClosedLoopSource();
			break;
		case EctoMotorFeedback::Potentiometer:
			this->setPotAsClosedLoopSource();
			break;
	}
}

EctoMotorFeedback EctoMotor::getFeedbackMode() const {
	return this->feedbackMode;
}

int EctoMotor::getId() {
	return id;
}

double EctoMotor::get() const {
	switch (feedbackMode) {
		case EctoMotorFeedback::None:
			return getPercentOutput();
		case EctoMotorFeedback::QuadEncoder:
			return getVelocity();
		case EctoMotorFeedback::Potentiometer:
			return getPosition();
		default:
			return 0;
	}
}

void EctoMotor::outputSet(double set) {
	this->set(set, EctoControlMode::Percent);
}

bool EctoMotor::isDisabled() const {
	return disabled;
}

double EctoMotor::getPosition() const {
	if (getEncoderCodes() == 0) {
		log->warn("Trying to get position but no encoder codes defined! on motor: {}", name);
		return 0;
	}
	
	switch (feedbackMode) {
		case EctoMotorFeedback::None:
			log->warn("Cannot get a position when no feedback mode is defined in motor with name: {} ", name);
			return 0;
		case EctoMotorFeedback::QuadEncoder:
			return getQuadPosition();
		case EctoMotorFeedback::Potentiometer:
			return getPotPosition();
		default:
			return 0;
	}
}

double EctoMotor::getVelocity() const {
	if (getEncoderCodes() == 0) {
		log->warn("Trying to get position but no encoder codes defined! on motor: {}", name);
		return 0;
	}
	
	switch (feedbackMode) {
		case EctoMotorFeedback::None:
			log->warn("Cannot get a velocity when no feedback mode is defined in motor with name: {} ", name);
			return 0;
		case EctoMotorFeedback::QuadEncoder:
			return getQuadVelocity();
		case EctoMotorFeedback::Potentiometer:
			return getPotVelocity();
		default:
			return 0;
	}
}

void EctoMotor::setControllerSourceMode(EctoControlMode mode) {
	this->controllerSourceMode = mode;
}

void EctoMotor::PIDWrite(double output) {
	outputSet(output);
}

double EctoMotor::PIDGet() {
	return getPosition();
}

EctoSendableData EctoMotor::serializeData() const {
	
	EctoSendableData data;
	data.addData("IsInverted", isInverted());
	data.addData("IsSensorInverted", isSensorInverted());

	data.addData("SetPoint", this->get());
	
	return data;
}
