//
// Created by alberto on 31/07/19.
//
#ifndef ECTOCONTROL_MOTORHANDLER_H
#define ECTOCONTROL_MOTORHANDLER_H

#include "Core/MotorHandler/EctoMotor/EctoMotor.h"
#include "EctoMotor/DataTypes/EctoMotorType.h"
#include <EctoModule/Manager.h>

class MotorHandler : public Manager<MotorHandler> {
	friend class Manager<MotorHandler>;

public:
	std::shared_ptr<EctoMotor> &getMotor(const std::string &name);
	void update() override;

private:
	const std::string talonVersion = "4.22";
	const std::string sparkMaxVersion = "v1.4.0";
	
	void initializeMotors();
	void initializeSimulatedMotors();
	
	std::map<std::string, std::string> rawMotorConfig;
	std::vector<std::shared_ptr<EctoMotor>> motorControllers;
	
	MotorHandler();
};

#endif //ECTOCONTROL_MOTORHANDLER_H
