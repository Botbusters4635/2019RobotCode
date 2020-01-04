/*
A set of various utilities, mostly used for robot code
 */
#ifndef BOTBUSTERSREBIRTH_ECTOUTILS_H
#define BOTBUSTERSREBIRTH_ECTOUTILS_H

#include <memory>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

namespace EctoUtils {
	struct MotorIdsTank {
		unsigned int left;
		unsigned int right;
	};

//Arduino map
	template<class T>
	T map(T x, T in_min, T in_max, T out_min, T out_max) {
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

	double limit(double value, double lowerLimit, double upperLimit);

	double limit(double value);

	double applyDeadband(double value, double deadband);

	double applyTreshold(double previousValue, double value, double treshold);

	double shortestAngleTurn(double currentAngle, double target);

	template<typename T>
	T *ptr(T &obj) { return &obj; } //turn reference into pointer!

	template<typename T>
	T *ptr(T *obj) { return obj; } //obj is already pointer, return it!

}

#endif
