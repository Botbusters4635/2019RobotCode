//
// Created by Abiel on 8/12/18.
//

#ifndef BOTBUSTERSREBIRTH_INPUTVALUE_H
#define BOTBUSTERSREBIRTH_INPUTVALUE_H

/**
 * Stores values from -1 to 1 to be interpreted by the non-holonomic drivetrain
 */
class InputValue {
public:
	InputValue(double left_vel, double right_vel);

	InputValue();

	double getLeftVel() const;

	double getRightVel() const;

	void setLeftVel(double left_vel);

	void setRightVel(double right_vel);

	InputValue &operator*=(double rhs);

	const InputValue operator*(double rhs) const;

protected:
	double left_vel, right_vel;
};


#endif //BOTBUSTERSREBIRTH_INPUTVALUE_H
