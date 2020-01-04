#include "EctoUtilities/EctoUtils.h"


//Limits value from lower limit to upper limit
double EctoUtils::limit(double value, double lowerLimit, double upperLimit) {
	if (lowerLimit > upperLimit)
		throw logic_error("Lower limit is larger than upper limit!");

	return max(lowerLimit, min(value, upperLimit));
}

//Limits value from -1 to 1
double EctoUtils::limit(double value) {
	return EctoUtils::limit(value, -1.0, 1.0);
}

//Implementation of deadband
double EctoUtils::applyDeadband(double value, double deadband) {
	if (abs(value) > deadband) {
		if (value > 0.0) {
			return (value - deadband) / (1.0 - deadband);

		} else {
			return (value + deadband) / (1.0 - deadband);
		}
	} else {
		return 0.0;
	}
}

//Applies treshold to value
double EctoUtils::applyTreshold(double previousValue, double value, double treshold) {
	if (std::abs(abs(value) - std::abs(previousValue)) > treshold) {
		return value;
	} else {
		return previousValue;
	}
}

double EctoUtils::shortestAngleTurn(double currentAngle, double target) {
	double angleToTurn = target - currentAngle;

	if (abs(angleToTurn) > 180) {
		if (currentAngle > 0) {
			if (angleToTurn > 0) {
				angleToTurn = angleToTurn - 180;
			} else {
				angleToTurn = angleToTurn + 360;
			}
		} else {
			if (angleToTurn > 0) {
				angleToTurn = angleToTurn - 360;
			} else {
				angleToTurn = angleToTurn + 180;
			}
		}
	}
	return angleToTurn;
}