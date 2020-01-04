//
// Created by Abiel on 8/27/18.
//
#include "InputHandlers/InputUtils.h"
#include "InputHandlers/InputValue.h"

double InputUtils::applyDeadzone(double input, double deadzone) {
	return std::abs(input) >= deadzone ? input : 0.0;
}

double InputUtils::applyExponentialCurve(double input, double expoValue) {
	return (expoValue * std::pow(input, 3.0) + (1 - expoValue) * input);
}

MotorValues InputUtils::convertInputValueToMotorValue(const InputValue &value, MotorMode valueType) {
	return {value.getLeftVel(), value.getRightVel(), valueType};
}

#include <iostream>
InputUtils::JoystickQuadrant InputUtils::joystickDPad(double inputX, double inputY, double activationTreshold){
    double inputAngle = std::atan2(inputX, inputY);
    double inputMagnitude = std::hypot(inputY, inputX);

    if(inputMagnitude < activationTreshold)
        return JoystickQuadrant::None;

    if((inputAngle >= 0.0 and inputAngle < M_PI_4) or (inputAngle < 0.0 and inputAngle > -M_PI_4))
        return JoystickQuadrant::Left;

    if(inputAngle > M_PI_4 and inputAngle < 3.0 * M_PI_4)
        return JoystickQuadrant::Up;

    if((inputAngle > 3.0 * M_PI_4 and inputAngle <= M_PI) or (inputAngle > -M_PI and inputAngle < -3.0 * M_PI_4))
        return JoystickQuadrant::Right;

    return JoystickQuadrant::Down;
}

