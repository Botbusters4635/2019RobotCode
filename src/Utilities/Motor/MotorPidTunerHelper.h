//
// Created by abiel on 9/11/19.
//

#ifndef BOTBUSTERSREBIRTH_MOTORPIDTUNERHELPER_H
#define BOTBUSTERSREBIRTH_MOTORPIDTUNERHELPER_H

#include "Core/MotorHandler/EctoMotor/DataTypes/EctoMotorMode.h"
#include "Core/MotorHandler/EctoMotor/EctoMotor.h"
#include "EctoModule/System.h"
#include <networktables/NetworkTableEntry.h>

struct MotorPIDTunerHelperConfig {
	double maximumPercent;
	
	PIDConfig pidConfig;
	
	double currentLimit;
	
	double closedLoopRampRate;
	
	EctoControlMode motorMode;
};

class MotorPIDTunerHelper : public System {
public:
	MotorPIDTunerHelper(const std::string &name, const MotorPIDTunerHelperConfig &config,
	                    const std::shared_ptr<EctoMotor> &motor);
	
	
	//void initAuto() override;
	//void updateAuto() override;
private:
	MotorPIDTunerHelperConfig config;
	std::shared_ptr<EctoMotor> motor;
	
	nt::NetworkTableEntry pEntry;
	nt::NetworkTableEntry iEntry;
	nt::NetworkTableEntry dEntry;
	
	nt::NetworkTableEntry maximumCurrentEntry;
	nt::NetworkTableEntry closedLoopEntry;
};


#endif //BOTBUSTERSREBIRTH_MOTORPIDTUNERHELPER_H

