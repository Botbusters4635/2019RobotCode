//
// Created by alberto on 16/09/19.
//

#include "BallIntake.h"
#include <frc/smartdashboard/SmartDashboard.h>

BallIntake::BallIntake(const std::shared_ptr<EctoMotor> &intakeMotor) : System("BallIntake") {
	ballIntakeMotor = intakeMotor;
	ballIntakeMotor->setOpenLoopRampRate(0.1);
}

void BallIntake::initRobot() {
	leftPiston = pcm.getPiston(ballIntakePistonBase + "1");
	rightPiston = pcm.getPiston(ballIntakePistonBase + "2");
}

void BallIntake::updateRobot() {
	frc::SmartDashboard::PutBoolean("BallIntake/lifted", isIntakeLifted);
	frc::SmartDashboard::PutNumber("BallIntake/IntakeMotorSetPoint", lastSetpoint);
}

void BallIntake::setIntakeMotor(double set) {
	if(lastSetpoint == set){
		//return;
	}
	
	if (!isIntakeLifted) {
		ballIntakeMotor->set(set, EctoControlMode::Percent);
	} else {
		ballIntakeMotor->set(0, EctoControlMode::Percent);
	}
}

void BallIntake::setIntakePistonState(bool state) {
	if(lastPistonState == state){
		return;
	}
	
	pcm.setPiston(leftPiston, state);
	pcm.setPiston(rightPiston, state);
	lastPistonState = state;
	isIntakeLifted = state;
}