//
// Created by Abiel on 9/9/19.
//

#ifndef BOTBUSTERSREBIRTH_ELEVATOR_H
#define BOTBUSTERSREBIRTH_ELEVATOR_H

#include "EctoModule/System.h"
#include "Core/MotorHandler/EctoMotor/EctoSpark.h"
#include <networktables/NetworkTableEntry.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Timer.h>
#include <InputHandlers/EctoButton.h>
#include <Core/EctoInput/EctoInput.h>

struct ElevatorConfig {
	//How many motor rotations are needed for one winch rotation
	double gearReduction = 0.0;
	double winchDiameter = 0.0;
	
	double forwardHeightLimit = 0.0;
	double reverseHeightLimit = 0.0;
	
	bool enableForwardSoftLimt = true;
	bool enableReverseSoftLimit = true;
	
	bool useMagicMotion = true;
	double maximumVelocity = 0;
	double maximumAcceleration = 0;
	
	bool voltageTestMode = false;
};

class Elevator : public System {
public:
	Elevator(const std::string &elevatorName, const std::shared_ptr<EctoMotor> &motor, const ElevatorConfig &config);
	
	void setHeight(double height);
	double getHeight() const;
	
	void homeElevator();
	
	void initRobot() override;
	void updateRobot() override;
	
	void initDisabled() override;
	
	bool isAutoHoming() const;

private:
	Elevator() = delete;
	
	ElevatorConfig config;
	PIDConfig pidConfig;
	std::shared_ptr<EctoMotor> motor;
	
	inline double convertHeightToRadians(double height) const;
	inline double convertRadiansToHeight(double radians) const;
	
	double winchCircumference;
	double previousHeight;
	
	double lastLimitSwitchCheck = 0;
	const double limitSwitchCheckTimeout = 2.2;
	
	double autoHomeTimeout = 20; //seconds
	double homeStartTime = 0;
	bool hasAutoHomed = false;
	
	double homeCheckWaitTime = 0.5; //Check every 0.5 seconds
	double lastHomeCheckTime = 0;
};


#endif //BOTBUSTERSREBIRTH_ELEVATOR_H
