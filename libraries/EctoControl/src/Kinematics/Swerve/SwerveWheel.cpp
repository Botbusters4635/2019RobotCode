//
// Created by Abiel on 8/26/19.
//

#include "EctoControl/Kinematics/Swerve/SwerveWheel.h"
#include <cmath>

void SwerveWheel::invertValue() {
    wheelVelocity *= -1.0;
    wheelAngle += std::copysign(M_PI, wheelAngle);
    wheelAngle = (wheelAngle > M_PI ? wheelAngle - 2 * M_PI : wheelAngle);
    wheelAngle = (wheelAngle < -M_PI ? wheelAngle + 2 * M_PI : wheelAngle);
}

SwerveWheel SwerveWheel::invertValue_copy(const SwerveWheel &value) {
    SwerveWheel output(value);
    output.invertValue();
    return output;
}

double SwerveWheel::getAngleBetween(const SwerveWheel &current, const SwerveWheel &target) {
    return std::remainder(target.wheelAngle - current.wheelAngle, M_PI * 2.0);
}

bool SwerveWheel::operator==(const SwerveWheel &rhs) {
    return wheelVelocity == rhs.wheelVelocity and
        wheelAngle == rhs.wheelAngle and
        wheelAngularVelocity == rhs.wheelAngularVelocity;
}

SwerveWheel& SwerveWheel::operator=(const SwerveWheel &rhs) {
    this->wheelVelocity = rhs.wheelVelocity;
    this->wheelAngle = rhs.wheelAngle;
    this->wheelAngularVelocity = rhs.wheelAngularVelocity;

    return *this;
}

void SwerveWheel::roundToEpsilon() {
    if(std::abs(wheelVelocity) < epsilon){
        wheelVelocity = 0.0;
    }

    if(std::abs(wheelAngle) < epsilon){
        wheelAngle = 0.0;
    }

    if(std::abs(wheelAngularVelocity) < epsilon){
        wheelAngularVelocity = 0.0;
    }
}

SwerveWheel SwerveWheel::roundToEpsilon_copy(const SwerveWheel &wheel) {
    SwerveWheel output(wheel);
    output.roundToEpsilon();
    return output;
}

std::ostream& operator<<(std::ostream &os, const SwerveWheel &wheel) {
    os << "Wheel Velocity: " << wheel.wheelVelocity << " Wheel Angle: " << wheel.wheelAngle <<  " Wheel Angular Velocity: " << wheel.wheelAngularVelocity;
    return os;
}