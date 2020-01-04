//
// Created by abiel on 1/2/20.
//

#ifndef BOTBUSTERSREBIRTH_ECTOSWERVEINPUTHANDLER_H
#define BOTBUSTERSREBIRTH_ECTOSWERVEINPUTHANDLER_H

#include "EctoSwerve.h"
#include <EctoModule/System.h>
#include <Core/EctoInput/EctoInput.h>
#include <InputHandlers/EctoButton.h>
#include <InputHandlers/ToggleButton.h>
#include <InputHandlers/JoystickAxisExpo.h>

class EctoSwerveInputHandler : public System {
public:
	EctoSwerveInputHandler(EctoSwerve &swerveIn);
	
	void initRobot() override;
	void updateRobot() override;
	
private:
	EctoSwerve &swerve;
	
	EctoInput &input = EctoInput::getInstance();
	
	std::unique_ptr<JoystickAxisExpo> strafeAxis, forwardAxis, rotationAxis;
	std::unique_ptr<JoystickAxisExpo> brakeTrigger;
	
	const double slowModeReduction = 0.4;
	const double minimumBrakeValue = 0.25;
	
	ToggleButton slowMode, fieldOrientedEnable;
	EctoButton visionEnable, resetYaw;
};



#endif //BOTBUSTERSREBIRTH_ECTOSWERVEINPUTHANDLER_H
