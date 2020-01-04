#ifndef ECTOCONTROL_ECTOMOTORTYPE_H
#define ECTOCONTROL_ECTOMOTORTYPE_H

#include <algorithm>
#include <string>

enum class EctoMotorType {
	PWM,
	TalonSRX,
	SparkMax,
	Empty
};

bool compareIgnoringCase(const std::string &s, const std::string &s1);

std::string getStringFromMotorType(EctoMotorType type);

EctoMotorType getMotorTypeFromString(const std::string &type);

#endif