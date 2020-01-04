//
// Created by abiel on 1/2/20.
//

#include "EctoSwerveInputHandler.h"

EctoSwerveInputHandler::EctoSwerveInputHandler(EctoSwerve &swerveIn) : System("EctoSwerveRebirthInputHandler"), swerve(swerveIn),  fieldOrientedEnable(true) {
	const double joystickExpo = 0.2;
	const double joystickDeadzone = 0.15;
	
	const double triggerExpo = 0.2;
	const double triggerDeadzone = 0.2;
	
	strafeAxis = std::make_unique<JoystickAxisExpo>(joystickExpo, joystickDeadzone);
	forwardAxis = std::make_unique<JoystickAxisExpo>(joystickExpo, joystickDeadzone);
	rotationAxis = std::make_unique<JoystickAxisExpo>(joystickExpo, joystickDeadzone);
	
	brakeTrigger = std::make_unique<JoystickAxisExpo>(triggerExpo, triggerDeadzone);
	
	input.addAxis(strafeAxis.get(), "rightY");
	input.addAxis(forwardAxis.get(), "rightX");
	input.addAxis(rotationAxis.get(), "leftY");
	
	input.addAxis(brakeTrigger.get(), "rightTrig");
	
	input.addButton(&slowMode, "leftPush");
	input.addButton(&fieldOrientedEnable, "rightJoy");
	input.addButton(&visionEnable, "rightPush");
	input.addButton(&resetYaw, "select");
}

void EctoSwerveInputHandler::initRobot() {
	;
}

void EctoSwerveInputHandler::updateRobot() {
	Twist2D output(forwardAxis->get(), strafeAxis->get(), rotationAxis->get());
	
	if(slowMode.get()){
		output *= slowModeReduction;
	} else if(brakeTrigger->get()){
		const double reductionFactor = std::max((1.0 - brakeTrigger->get()), minimumBrakeValue);
		output *= reductionFactor;
	}
	
	swerve.setTargetVelocity(output, Point2D(0,0), true, fieldOrientedEnable.get());
}