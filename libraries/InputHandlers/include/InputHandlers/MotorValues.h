#ifndef BOTBUSTERSREBIRTH_MOTORVALUES_H
#define BOTBUSTERSREBIRTH_MOTORVALUES_H

#include <cmath>
#include <string>

enum class MotorMode : unsigned short {
	VOLTAGE = 0,
	POSITION = 1,
	VELOCITY = 2,
	CURRENT = 3,
	FOLLOWER = 5,
	MOTION_PROFILE = 6,
	MOTION_MAGIC = 7,
	MOTION_PROFILE_ARC = 10,
	DEFAULT = 15
};

class MotorValues {
public:
	MotorValues(double leftValue, double rightValue, MotorMode type = MotorMode::DEFAULT);

	MotorValues();

	double calculateMax() const;

	double getLeft() const;

	double getRight() const;

	void setLeft(double left);

	void setRight(double right);

	MotorMode getValueType() const;

	void setValueType(MotorMode valueType);

	double left, right;

	static std::string getMotorModeName(MotorMode mode);

	friend std::ostream &operator<<(std::ostream &os, const MotorValues &values);

	friend std::istream &operator>>(std::istream &in, MotorValues &values);

private:
	static std::string getValueTypeName(MotorMode valueType);

	MotorMode valueType;
};

#endif
