//
// Created by Abiel on 8/13/18.
//

#ifndef BOTBUSTERSREBIRTH_TANKDIFFERENTIALDRIVE_H
#define BOTBUSTERSREBIRTH_TANKDIFFERENTIALDRIVE_H

#include "InputHandlers/InputHandler.h"
#include <cmath>

struct TankDifferentialDriveConfig {
	bool initialInvertedStatus = false;

	bool enableExponential = true;
	bool enableDeadzone = true;

	double leftExponential = 0.15;
	double rightExponential = 0.15;

	double leftDeadzone = 0.1;
	double rightDeadzone = 0.1;

	double upperLimit = 1.0;
	double lowerLimit = -1.0;
};

class TankDifferentialDrive : public InputHandler {
public:
	explicit TankDifferentialDrive(const TankDifferentialDriveConfig &config);

	void init() override;

	InputValue calculateInputs(const InputValue &joystickInputs) const override;

private:
	TankDifferentialDriveConfig config;
};


#endif //BOTBUSTERSREBIRTH_TANKDIFFERENTIALDRIVE_H
