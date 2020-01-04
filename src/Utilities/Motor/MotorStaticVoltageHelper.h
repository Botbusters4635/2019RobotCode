//
// Created by hiram on 9/17/19.
//

#ifndef BOTBUSTERS_REBIRTH_MOTORVOLTAGEHELPER_H
#define BOTBUSTERS_REBIRTH_MOTORVOLTAGEHELPER_H


#include <EctoModule/System.h>
#include <Core/MotorHandler/EctoMotor/EctoMotor.h>

class MotorStaticVoltageHelper : public System {
public:
	MotorStaticVoltageHelper(const std::string &name, const std::shared_ptr<EctoMotor> &motor);
	
	void updateRobot() override;
	
	double getVoltageToMove() const;

private:
	std::shared_ptr<EctoMotor> motor;
	double voltageToMove = 0;
};


#endif //BOTBUSTERS_REBIRTH_MOTORVOLTAGEHELPER_H
