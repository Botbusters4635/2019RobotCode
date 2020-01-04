//
// Created by Abiel on 8/13/18.
//

#ifndef BOTBUSTERSREBIRTH_INPUTHANDLER_H
#define BOTBUSTERSREBIRTH_INPUTHANDLER_H

#include "InputHandlers/InputHandler.h"
#include "InputValue.h"

class InputHandler {
public:
	virtual void init() = 0;

	//Prints inputs every time calculateInputs is called until state is set to false
	virtual void printInputs(bool state) {
		this->printInputsState = state;
	}

	//Prints outputs every time calculateInputs is called until state is set to false
	virtual void printOutputs(bool state) {
		this->printOutputsState = state;
	}

	virtual InputValue calculateInputs(const InputValue &joystickInputs) const = 0;

private:
	bool printInputsState = false;
	bool printOutputsState = false;
};

#endif //BOTBUSTERSREBIRTH_NONHOLONOMICINPUTHANDLER_H
