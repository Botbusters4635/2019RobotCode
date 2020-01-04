//
// Created by abiel on 9/17/19.
//

#include "PuppetMeister.h"
#include "Systems/Claw/Claw.h"

PuppetMeister::PuppetMeister(const PuppetMeisterConfig &config) : SystemHandler("PuppetMeister") {
	this->config = config;
	
	claw = std::make_shared<Claw>(handler.getMotor(config.leftClawMotorName),
	                              handler.getMotor(config.rightClawMotorName), handler.getMotor(config.wristMotorName));
	elevator = std::make_shared<Elevator>("MainElevator", handler.getMotor(config.elevatorMotorName),
	                                      config.elevatorConfig);
	intake = std::make_shared<BallIntake>(handler.getMotor(config.externalIntakeMotorName));
	
	inputHandler = std::make_shared<PuppetMeisterInputHandler>(claw, elevator, intake);
	
	timingDataPublisher = std::make_shared<TimingDataPublisher>(std::shared_ptr<SystemHandler>(this), "PuppetMeisterTimingDataPublisher");
	
	this->addSubsystem(inputHandler);
	this->addSubsystem(claw);
	this->addSubsystem(elevator);
	this->addSubsystem(intake);
	this->addSubsystem(timingDataPublisher);
}


PuppetMeisterInputHandler::PuppetMeisterInputHandler(const std::shared_ptr<Claw> &claw,
                                                     const std::shared_ptr<Elevator> &elevator,
                                                     const std::shared_ptr<BallIntake> &intake) : System(
		"PuppetMeisterInputHandler") {
	this->claw = claw;
	this->elevator = elevator;
	this->intake = intake;
	
	clawStick = std::make_unique<JoystickAxisExpo>(.25, .1);
	
	leftTrigger = std::make_unique<JoystickAxisExpo>(0.1666, .15);
	rightTrigger = std::make_unique<JoystickAxisExpo>(0.1666, .15);
	
	driverLeftTrigger = std::make_unique<JoystickAxisExpo>(0.166, .15);
	driverRightTrigger = std::make_unique<JoystickAxisExpo>(0.166, .15);
	
	stick.addAxis(driverLeftTrigger.get(), "leftTrig");
	stick.addAxis(driverRightTrigger.get(), "rightTrig");
	
	stick.addButton(&hatchMode, "leftPush", 2);
	stick.addButton(&ballMode, "rightPush", 2);
//	stick.addButton(&hatchMode, "leftJoy", 1);
//	stick.addButton(&ballMode, "rightJoy", 1);
	//stick.addButton(&autoHatchMode, "rightJoy", 2);
	//stick.addButton(&autoBallMode, "leftJoy", 2);
//	stick.addButton(&enablePiston, "rightJoy", 2);
//	stick.addButton(&disablePiston, "leftJoy", 2);
	stick.addButton(&enablePiston, "rightJoy", 2);
	stick.addButton(&disablePiston, "leftJoy", 2);
	stick.addButton(&driverAutoHome, "start", 1);
	stick.addButton(&operatorAutoHome, "select", 2);
	stick.addAxis(clawStick.get(), "leftX", 2);
	
	stick.addButton(&topPreset, "Y", 2);
	stick.addButton(&midPreset, "B", 2);
	stick.addButton(&lowPreset, "A", 2);
	stick.addButton(&altMid, "X", 2);
//	stick.addButton(&topPreset, "Y", 1);
//	stick.addButton(&midPreset, "B", 1);
//	stick.addButton(&lowPreset, "A", 1);
//	stick.addButton(&altMid, "X", 1);
	
	stick.addAxis(leftTrigger.get(), "leftTrig", 2);
	stick.addAxis(rightTrigger.get(), "rightTrig", 2);
	
}

void PuppetMeisterInputHandler::setTargetPreset(PuppetMeisterPreset preset) {
	if(preset == lastPreset){
		return;
	}
	
	switch (preset) {
		case PuppetMeisterPreset::Stored:
			targetClawAngle = 1.57;
			targetElevatorHeight = 0.01;
			targetLiftIntake = true;
			break;
		case PuppetMeisterPreset::HatchIntake:
			targetClawAngle = 0.0;
			targetElevatorHeight = 0.1;
			targetLiftIntake = true;
			break;
		case PuppetMeisterPreset::BallIntake:
			targetClawAngle = 3.1;
			targetElevatorHeight = 0.01;
			targetLiftIntake = false;
			break;
		case PuppetMeisterPreset::Ball_CargoShip:
			targetClawAngle = 0;
			targetElevatorHeight = 0.40;
			targetLiftIntake = true;
			break;
		case PuppetMeisterPreset::Ball_Low:
			targetClawAngle = 0.1;
			targetElevatorHeight = 0.22;
			targetLiftIntake = true;
			break;
		case PuppetMeisterPreset::Ball_Mid:
			targetClawAngle = 0;
			targetElevatorHeight = 0.645;
			targetLiftIntake = true;
			break;
		case PuppetMeisterPreset::Ball_High:
			targetClawAngle = 0.61;
			targetElevatorHeight = 0.79;
			targetLiftIntake = true;
			break;
		case PuppetMeisterPreset::Hatch_CargoShip:
			targetClawAngle = 0;
			targetElevatorHeight = 0.1;
			targetLiftIntake = true;
			break;
		case PuppetMeisterPreset::Hatch_Low:
			targetClawAngle = 0.0;
			targetElevatorHeight = 0.1;
			targetLiftIntake = true;
			break;
		case PuppetMeisterPreset::Hatch_Mid:
			targetClawAngle = 0;
			targetElevatorHeight = 0.525;
			targetLiftIntake = true;
			break;
		case PuppetMeisterPreset::Hatch_High:
			targetClawAngle = 0.5;
			targetElevatorHeight = 0.8;
			targetLiftIntake = true;
			break;
	}
	
	lastPreset = preset;
}

void PuppetMeisterInputHandler::checkCollisions() {
	const double elevatorHeight = elevator->getHeight();
	const double clawAngle = claw->getCurrentAngle();
	
	setElevatorHeight = targetElevatorHeight;
	setClawAngle = targetClawAngle;
	setLiftIntake = targetLiftIntake;
	
	
	if (targetElevatorHeight > maxHeightParaGirarGarra && clawAngle > garraTresh) {
		setElevatorHeight = 0.0;
	}
	
	if (targetClawAngle > garraTresh && elevatorHeight > maxHeightParaGirarGarra) {
		setClawAngle = waitForElevatorPos;
	}
	
	if (clawAngle > 1.8) {
		setLiftIntake = false;
	}
	
	if (clawAngle < 0.3 && elevatorHeight < 0.07) {
		setClawAngle = 0.7;
	}
	
}

void PuppetMeisterInputHandler::updateRobot() {
	updateInputs();
}

void PuppetMeisterInputHandler::updateInputs() {
	bool hatch = hatchMode.get();
	bool ball = ballMode.get();
	//bool autoHatchModeVal = autoHatchMode.get();
	//bool autoBallModeVal = autoBallMode.get();
	
	if(driverAutoHome.get() or operatorAutoHome.get()){
		elevator->homeElevator();
	}
	
	if (ball && ball != lastBallMode) {
		isInHatchMode = false;
	} else if (hatch && hatch != lastHatchMode) {
		isInHatchMode = true;
	}
	
	this->lastHatchMode = hatch;
	this->lastBallMode = ball;
	
	if (isInHatchMode) {
		intake->setIntakeMotor(0);
		if (topPreset.get()) {
			targetPreset = PuppetMeisterPreset::Hatch_High;
		} else if (midPreset.get()) {
			targetPreset = PuppetMeisterPreset::Hatch_Mid;
		} else if (lowPreset.get()) {
			targetPreset = PuppetMeisterPreset::Hatch_Low;
		} else if (altMid.get()) {
			targetPreset = PuppetMeisterPreset::HatchIntake;
		}
		
		double clawValue = -clawStick->get();
		
		if(driverLeftTrigger->get() > 0.1 or driverRightTrigger->get() > 0.1){
			clawValue = -driverLeftTrigger->get() + driverRightTrigger->get();
		}
		
		claw->setClawMotors(clawValue);
	} else {
		double clawValue = clawStick->get();
		
		if(driverLeftTrigger->get() > 0.1 or driverRightTrigger->get() > 0.1 ){
			clawValue = driverLeftTrigger->get() - driverRightTrigger->get();
		}
		
		intake->setIntakeMotor(clawValue);
		claw->setClawMotors(clawValue);
		
		if (topPreset.get()) {
			targetPreset = PuppetMeisterPreset::Ball_High;
		} else if (midPreset.get()) {
			targetPreset = PuppetMeisterPreset::Ball_Mid;
		} else if (lowPreset.get()) {
			targetPreset = PuppetMeisterPreset::Ball_Low;
		} else if (altMid.get()) {
			targetPreset = PuppetMeisterPreset::BallIntake;
		}
		
		//claw->setPistonState(true);
	}
	
	if (enablePiston.get()) {
		manualPistonEnable = true;
		lastManualPistonValue = false;
	} else if (disablePiston.get()) {
		manualPistonEnable = true;
		lastManualPistonValue = true;
	} else if (isInHatchMode != lastMode){
		manualPistonEnable = false;
	}
	
	if(targetPreset == PuppetMeisterPreset::Ball_Low or
	   targetPreset == PuppetMeisterPreset::Ball_CargoShip or
	   targetPreset == PuppetMeisterPreset::Ball_Mid or
	   targetPreset == PuppetMeisterPreset::Ball_High){
		claw->setPistonState(false);
	} else if(manualPistonEnable){
		claw->setPistonState(lastManualPistonValue);
	} else {
		claw->setPistonState(!isInHatchMode);
	}
	
	//log->info("{} {}", rightTrigger->get(), leftTrigger->get());
	
	if (rightTrigger->get() >= storedTriggerThresh) {
		targetPreset = PuppetMeisterPreset::Ball_CargoShip;
	}
	
	if (leftTrigger->get() >= storedTriggerThresh) {
		targetPreset = PuppetMeisterPreset::Stored;
	}
	
	lastMode = isInHatchMode;
	
	claw->disableClaw(elevator->isAutoHoming());
	
	setTargetPreset(targetPreset);
	checkCollisions();
	elevator->setHeight(setElevatorHeight);
	claw->setClawAngle(setClawAngle);
	intake->setIntakePistonState(setLiftIntake);
}
