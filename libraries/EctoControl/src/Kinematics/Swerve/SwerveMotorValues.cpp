//
// Created by alberto on 15/08/19.
//

#include "EctoControl/Kinematics/Swerve/SwerveMotorValues.h"
#include <iostream>

SwerveMotorValues::SwerveMotorValues(const SwerveWheel &topLeft, const SwerveWheel &topRight, const SwerveWheel &backLeft, const SwerveWheel &backRight){
    this->topLeft = topLeft;
    this->topRight = topRight;

    this->backLeft = backLeft;
    this->backRight = backRight;
}

SwerveMotorValues::SwerveMotorValues(){
    ;
}

double SwerveMotorValues::getHighestVelocity() const {
    return std::max(std::max(topLeft.wheelVelocity, topRight.wheelVelocity), std::max(backLeft.wheelVelocity, backRight.wheelVelocity));
}

void SwerveMotorValues::clampVelocities(double maxVel) {
    double highestVelocity = getHighestVelocity();

    if(highestVelocity == 0 || highestVelocity <= maxVel){
        return;
    }
    topLeft.wheelVelocity = (topLeft.wheelVelocity / highestVelocity) * maxVel;
    topRight.wheelVelocity =  (topRight.wheelVelocity / highestVelocity) * maxVel;

    backLeft.wheelVelocity = (backLeft.wheelVelocity / highestVelocity) * maxVel;
    backRight.wheelVelocity = (backRight.wheelVelocity / highestVelocity) * maxVel;
}

void SwerveMotorValues::normalizeVelocities() {
    this->clampVelocities(1.0);
}

double SwerveMotorValues::getAngleWeight(const SwerveWheel &currentState,
                                         const SwerveWheel &targetState) {
    return std::abs(SwerveWheel::getAngleBetween(currentState, targetState) / M_PI);
}

double SwerveMotorValues::getVelocityWeight(const SwerveWheel &currentState,
                                            const SwerveWheel &targetState) {
    return std::abs(targetState.wheelVelocity - currentState.wheelVelocity) / 2.0;
}

double SwerveMotorValues::getAngleAccelerationWeight(const SwerveWheel &currentState,
                                                     const SwerveWheel &targetState, const SwerveWheel &lastState, double dt) {
    double acceleration = (lastState.wheelAngularVelocity - currentState.wheelAngularVelocity) / dt;
    double angleDifference = SwerveWheel::getAngleBetween(currentState, targetState);

    if(angleDifference > 0){
        return acceleration < 0 ? 1 : 0;
    } else if(angleDifference < 0){
        return acceleration > 0 ? 1 : 0;
    } else{
        //0
        return 0;
    }
}

double SwerveMotorValues::calculateWeight(const SwerveWheel &currentState, const SwerveWheel &targetState, const SwerveWheel &lastState, double dt) {
    return getAngleWeight(currentState, targetState) * angleWeightValue + getVelocityWeight(currentState, targetState) * velocityWeightValue + getAngleAccelerationWeight(currentState, targetState, lastState, dt) * 0.666;
}

SwerveWheel SwerveMotorValues::optimizeWheelValue(const SwerveWheel &currentState, const SwerveWheel &targetState, const SwerveWheel &lastState, const SwerveWheel &lastSet, double dt) {
    SwerveWheel invertedState = SwerveWheel::invertValue_copy(targetState);
    double targetWeight = calculateWeight(currentState, targetState, lastState, dt) + getAngleWeight(lastSet, targetState) * 1.6665 + .55;
    double invertedWeight = calculateWeight(currentState, invertedState, lastState, dt) + getAngleWeight(lastSet, invertedState) * 1.25;

    if(targetWeight > invertedWeight)
        return invertedState;
    else
        return targetState;
}

SwerveMotorValues SwerveMotorValues::optimizeValues_copy(const SwerveMotorValues &currentState, const SwerveMotorValues &targetState, const SwerveMotorValues &lastState, const SwerveMotorValues &lastSet, double dt) {
    SwerveMotorValues output;
    output.topLeft = optimizeWheelValue(currentState.topLeft, targetState.topLeft, lastState.topLeft, lastSet.topLeft, dt);
    output.topRight = optimizeWheelValue(currentState.topRight, targetState.topRight, lastState.topRight, lastSet.topRight, dt);

    output.backLeft = optimizeWheelValue(currentState.backLeft, targetState.backLeft, lastState.backLeft, lastSet.backLeft, dt);
    output.backRight = optimizeWheelValue(currentState.backRight, targetState.backRight, lastState.backRight, lastSet.backRight, dt);
    return output;
}

SwerveMotorValues SwerveMotorValues::optimizeValues(const SwerveMotorValues &currentState, const SwerveMotorValues &targetState, const SwerveMotorValues &lastState, const SwerveMotorValues &lastSet, double dt) {
    return SwerveMotorValues::optimizeValues_copy(currentState, targetState, lastState, lastSet, dt);
}

bool SwerveMotorValues::operator==(const SwerveMotorValues &rhs) {
    return topLeft == rhs.topLeft and
        topRight == rhs.topRight and
        backLeft == rhs.backLeft and
        backRight == rhs.backRight;
}

SwerveMotorValues& SwerveMotorValues::operator=(const SwerveMotorValues &rhs) {
    topLeft = rhs.topLeft;
    topRight = rhs.topRight;

    backLeft = rhs.backLeft;
    backRight = rhs.backRight;

    return *this;
}

void SwerveMotorValues::roundToEpsilon() {
    topLeft.roundToEpsilon();
    topRight.roundToEpsilon();

    backLeft.roundToEpsilon();
    backRight.roundToEpsilon();
}

std::ostream& operator<<(std::ostream &os, const SwerveMotorValues &value){
    os << "Top Left: " << value.topLeft << std::endl;
    os << "Top Right: " << value.topRight << std::endl;
    os << "Back Left: " << value.backLeft << std::endl;
    os << "Back Right: " << value.backRight;
    return os;
}