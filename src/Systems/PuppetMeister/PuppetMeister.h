//
// Created by abiel on 9/17/19.
//

#ifndef BOTBUSTERSREBIRTH_PUPPETMEISTER_H
#define BOTBUSTERSREBIRTH_PUPPETMEISTER_H

#include "Systems/Claw/Claw.h"
#include "Systems/Elevator/Elevator.h"
#include "Systems/BallIntake/BallIntake.h"
#include "Core/MotorHandler/MotorHandler.h"
#include <InputHandlers/InputUtils.h>
#include <EctoModule/SystemHandler.h>
#include "Systems/TimingDataPublisher/TimingDataPublisher.h"
#include <frc/DigitalOutput.h>

enum class PuppetMeisterPreset {
	Stored,
	HatchIntake,
	BallIntake,
	
	Ball_CargoShip,
	Ball_Low,
	Ball_Mid,
	Ball_High,
	
	Hatch_CargoShip, //Probably the same as hatch intake
	Hatch_Low,
	Hatch_Mid,
	Hatch_High
};

struct PuppetMeisterConfig {
	std::string leftClawMotorName = "leftClaw";
	std::string rightClawMotorName = "rightClaw";
	
	std::string wristMotorName = "wristMotor";
	
	std::string elevatorMotorName = "elevatorMotor";
	
	std::string externalIntakeMotorName = "externalIntakeMotor";
	
	ElevatorConfig elevatorConfig;
};

class PuppetMeisterInputHandler;

class PuppetMeister : public SystemHandler {
public:
	explicit PuppetMeister(const PuppetMeisterConfig &config);

private:
	MotorHandler &handler = MotorHandler::getInstance();
	
	PuppetMeisterConfig config;
	
	std::shared_ptr<Claw> claw;
	std::shared_ptr<BallIntake> intake;
	std::shared_ptr<Elevator> elevator;
	std::shared_ptr<PuppetMeisterInputHandler> inputHandler;
	std::shared_ptr<TimingDataPublisher> timingDataPublisher;
};

class PuppetMeisterInputHandler : public System {
public:
	PuppetMeisterInputHandler(const std::shared_ptr<Claw> &claw, const std::shared_ptr<Elevator> &elevator,
	                          const std::shared_ptr<BallIntake> &intake);
	
	void updateRobot() override;

private:
	void updateInputs();
	
	void setTargetPreset(PuppetMeisterPreset preset);
	
	void checkCollisions();
	
	std::shared_ptr<Claw> claw;
	std::shared_ptr<BallIntake> intake;
	std::shared_ptr<Elevator> elevator;
	
	EctoInput &stick = EctoInput::getInstance();
	
	std::unique_ptr<JoystickAxisExpo> clawStick;
	std::unique_ptr<JoystickAxisExpo> leftTrigger, rightTrigger;
	
	std::unique_ptr<JoystickAxisExpo> driverLeftTrigger, driverRightTrigger;
	
	PuppetMeisterPreset targetPreset = PuppetMeisterPreset::Stored;
	EctoButton hatchMode, ballMode;
	EctoButton autoHatchMode, autoBallMode;
	EctoButton driverAutoHome, operatorAutoHome;
	EctoButton topPreset, midPreset, lowPreset, altMid;
	EctoButton enablePiston, disablePiston;
	
	bool isInHatchMode = true;
	
	bool lastHatchMode = false;
	bool lastBallMode = false;
	
	bool lastAutoHatch = false;
	bool lastAutoBall = false;
	
	bool manualPistonEnable = false;
	bool lastManualPistonValue = false;
	
	bool lastMode = false;
	
	const double externalIntakeAutoPercent = .666;
	
	const double garraTresh = 0.9;
	const double maxHeightParaGirarGarra = 0.1;
	const double waitForElevatorPos = 0.9;
	
	double targetElevatorHeight = 0.0;
	double targetClawAngle = 0.0;
	
	double setElevatorHeight = 0.0;
	double setClawAngle = 0.0;
	
	bool targetLiftIntake = true;
	bool setLiftIntake = true;
	
	const double storedTriggerThresh = 0.4;
	
	bool currentPistonState = true;
	
	PuppetMeisterPreset lastPreset;
};


#endif //BOTBUSTERSREBIRTH_PUPPETMEISTER_H
