//
// Created by Abiel on 9/11/18.
//

#include "InputHandlers/EctoButton.h"

void EctoButton::updateStatus(bool status) {
	std::lock_guard<std::mutex> lock(buttonMutex);
	this->inValue = status;
	calculateOutput();
}

void EctoButton::calculateOutput() {
	this->outValue = inValue;
}

bool EctoButton::get() const {
	std::lock_guard<std::mutex> lock(buttonMutex);
	return outValue;
}