//
// Created by hiram on 28/06/19.
//

#include "EctoRobot.h"
#include <frc2/command/CommandScheduler.h>

EctoRobot::EctoRobot(const std::string &robotName) : TimedRobot(units::second_t (0.025)), System(robotName) {
	systemManager = std::make_shared<SystemHandler>("SystemManager");
	inputHandlers = std::make_shared<SystemHandler>("InputHandlers");
}

void EctoRobot::RobotInit() {
	log->info("RobotInit...");

	systemManager->initRobot();
	inputHandlers->initRobot();
}


void EctoRobot::RobotPeriodic() {
	frc2::CommandScheduler::GetInstance().Run();
	systemManager->updateRobot();
	motorHandler.update();
}

//TODO Run command handler here
void EctoRobot::AutonomousInit() {
	frc2::CommandScheduler::GetInstance().Enable();
	log->info("AutonomousInit... ");
}

void EctoRobot::AutonomousPeriodic() {
	if(updateInputsInAuto){
		inputHandlers->updateRobot();
	}
}

void EctoRobot::TeleopInit() {
	frc2::CommandScheduler::GetInstance().Disable();
	log->info("TeleopInit...");
}

void EctoRobot::TeleopPeriodic() {
	inputHandlers->updateRobot();
}

void EctoRobot::DisabledInit() {
	log->info("DisabledInit...");
	systemManager->initDisabled();
}

void EctoRobot::DisabledPeriodic() {
	this->updateDisabled();
	systemManager->updateDisabled();
}

//TODO Add test runner
void EctoRobot::TestInit() {
	log->info("TestInit...");
}

void EctoRobot::TestPeriodic() {
	;
}

