//
// Created by abiel on 9/10/19.
//

#ifndef BOTBUSTERSREBIRTH_MOTORCHARACTERIZATIONHELPER_H
#define BOTBUSTERSREBIRTH_MOTORCHARACTERIZATIONHELPER_H

#include "Core/MotorHandler/EctoMotor/EctoMotor.h"
#include "EctoModule/System.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/RobotController.h>
#include <frc/Timer.h>
#include <fmt/format.h>

class MotorCharacterizationHelper : public System {
public:
	MotorCharacterizationHelper(const std::string &name, const std::shared_ptr<EctoMotor> &motor);
	
	void initRobot() override;
	void updateRobot() override;

private:
	std::shared_ptr<EctoMotor> motor;
	
	nt::NetworkTableEntry autoSpeedEntry =
			nt::NetworkTableInstance::GetDefault().GetEntry("/robot/autospeed");
	
	double priorAutoSpeed;
	
	nt::NetworkTableEntry telemetryEntry =
			nt::NetworkTableInstance::GetDefault().GetEntry("/robot/telemetry");
};


#endif //BOTBUSTERSREBIRTH_MOTORCHARACTERIZATIONHELPER_H
