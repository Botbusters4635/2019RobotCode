//
// Created by Abiel on 8/26/18.
//

#ifndef BOTBUSTERSREBIRTH_INPUTUTILS_H
#define BOTBUSTERSREBIRTH_INPUTUTILS_H

#include <cmath>
#include "InputHandlers/MotorValues.h"

class InputValue;

namespace InputUtils {
    enum class JoystickQuadrant{
        None,
        Up,
        Right,
        Down,
        Left
    };

	/**
	 * Applies a deadzone to an input
	 * @param input
	 * @param deadzone
	 * @return
	 */
	double applyDeadzone(double input, double deadzone);

	/**
	 * Applies an exponential curve to an input
	 * @param input
	 * @param expoValue
	 * @return
	 */
	double applyExponentialCurve(double input, double expoValue);

	/**
	 * Maps a joystick into 4 quadrants
	 * @param input
	 * @param activationTreshold
	 * @return
	 */
    InputUtils::JoystickQuadrant joystickDPad(double inputX, double inputY, double activationTreshold);

	MotorValues convertInputValueToMotorValue(const InputValue &value, MotorMode valueType);
}

#endif //BOTBUSTERSREBIRTH_INPUTUTILS_H
