//
// Created by alberto on 15/08/19.
//

#ifndef ECTOCONTROL_SWERVEMOTORVALUES_H
#define ECTOCONTROL_SWERVEMOTORVALUES_H
#include <EctoMath/DataTypes/Rotation2D.h>
#include "SwerveWheel.h"
#include <iostream>

/**
 * Implemented as a class so helper functions can be added later
 *
 */

class SwerveMotorValues {
public:
    SwerveMotorValues(const SwerveWheel &topLeft, const SwerveWheel &topRight, const SwerveWheel &backLeft, const SwerveWheel &backRight);
    SwerveMotorValues();

    SwerveWheel topLeft;
    SwerveWheel topRight;

    SwerveWheel backLeft;
    SwerveWheel backRight;

    double getHighestVelocity() const;

    void clampVelocities(double maxVel);
    void normalizeVelocities();

    static SwerveMotorValues optimizeValues_copy(const SwerveMotorValues &currentState, const SwerveMotorValues &targetState, const SwerveMotorValues &lastState, const SwerveMotorValues &lastSet, double dt);
    static SwerveMotorValues optimizeValues(const SwerveMotorValues &currentState, const SwerveMotorValues &targetState, const SwerveMotorValues &lastState, const SwerveMotorValues &lastSet, double dt);
    static SwerveWheel optimizeWheelValue(const SwerveWheel &currentState, const SwerveWheel &targetState, const SwerveWheel &lastState, const SwerveWheel &lastSet, double dt);

    SwerveMotorValues& operator=(const SwerveMotorValues &rhs);
    bool operator==(const SwerveMotorValues &rhs);

    void roundToEpsilon();

    friend std::ostream& operator<<(std::ostream &os, const SwerveMotorValues &value);
private:
    static double getAngleWeight(const SwerveWheel &currentState, const SwerveWheel &targetState); //Returns a value from 0 to 1 depending on how far off the angles are
    static double getVelocityWeight(const SwerveWheel &currentState, const SwerveWheel &targetState); //Returns a value from 0 to 1 depending on the velocity delta
    static double getAngleAccelerationWeight(const SwerveWheel &currentState, const SwerveWheel &targetState, const SwerveWheel &lastState, double dt); //Depends on the necessary change in velocity


    static double calculateWeight(const SwerveWheel& currentState, const SwerveWheel &targetState, const SwerveWheel &lastState, double dt);
    static constexpr double angleWeightValue = 1.0;
    static constexpr double velocityWeightValue = 0.0;
};

#endif //ECTOCONTROL_SWERVEMOTORVALUES_H
