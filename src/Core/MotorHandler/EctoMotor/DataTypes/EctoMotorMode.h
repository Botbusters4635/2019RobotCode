//
// Created by alberto on 31/07/19.
//

#ifndef ECTOCONTROL_ECTOMOTORMODE_H
#define ECTOCONTROL_ECTOMOTORMODE_H

#include <algorithm>
#include "EctoMotorType.h"

enum class EctoControlMode {
	Percent,
	Velocity,
	Position,
	MotionMagic,
	Current
};

std::string getStringFromControlMode(EctoControlMode mode);

EctoControlMode getControlModeFromString(const std::string &mode);

#endif //ECTOCONTROL_ECTOMOTORMODE_H
