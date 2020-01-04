//
// Created by Abiel on 9/11/18.
//

#include "InputHandlers/ToggleButton.h"

ToggleButton::ToggleButton(bool defaultState) {
    this->outValue = defaultState;
}

void ToggleButton::calculateOutput() {
	if (inValue && inValue != previousStatus) {
		this->outValue = !outValue;
	}

	this->previousStatus = inValue;
}