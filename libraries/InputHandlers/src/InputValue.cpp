//
// Created by Abiel on 8/12/18.
//

#include "InputHandlers/InputValue.h"

InputValue::InputValue(double left_vel, double right_vel) {
	this->left_vel = left_vel;
	this->right_vel = right_vel;
}

InputValue::InputValue() : InputValue(0.0, 0.0) {
	;
}

double InputValue::getLeftVel() const {
	return left_vel;
}

double InputValue::getRightVel() const {
	return right_vel;
}

void InputValue::setLeftVel(double left_vel) {
	this->left_vel = left_vel;
}

void InputValue::setRightVel(double right_vel) {
	this->right_vel = right_vel;
}

InputValue &InputValue::operator*=(double rhs) {
	this->left_vel *= rhs;
	this->right_vel *= rhs;

	return *this;
}

const InputValue InputValue::operator*(double rhs) const {
	return InputValue(*this) *= rhs;
}