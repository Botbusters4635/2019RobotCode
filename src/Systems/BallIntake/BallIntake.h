//
// Created by alberto on 16/09/19.
//

#ifndef BOTBUSTERS_REBIRTH_BALLINTAKE_H
#define BOTBUSTERS_REBIRTH_BALLINTAKE_H

#include <EctoModule/System.h>
#include <Core/MotorHandler/EctoMotor/EctoTalon.h>
#include <Core/EctoPCM/EctoPCM.h>
#include <Core/EctoInput/EctoInput.h>
#include <InputHandlers/JoystickAxisExpo.h>

class BallIntake : public System {
public:
	BallIntake(const std::shared_ptr<EctoMotor> &intakeMotor);
	
	void initRobot() override;
	void updateRobot() override;
	
	void setIntakeMotor(double set);
	void setIntakePistonState(bool state);

private:
	EctoPiston leftPiston, rightPiston;
	
	EctoPCM &pcm = EctoPCM::getInstance();
	
	std::string ballIntakePistonBase = "ballIntakePiston";
	std::shared_ptr<EctoMotor> ballIntakeMotor;
	
	bool isIntakeLifted = true;
	
	double lastSetpoint = 0;
	bool lastPistonState;
};


#endif //BOTBUSTERS_REBIRTH_BALLINTAKE_H
