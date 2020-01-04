//
// Created by abiel on 10/9/19.
//

#include "EctoControl/SwervePIDController/SwervePIDController.h"

SwervePIDController::SwervePIDController(SwerveControllerSources &inSources, SwerveControllerOutput &inOutputs,
                                         const PIDConfig &config, std::chrono::milliseconds updateTime,
                                         std::chrono::milliseconds timeout) : sources(inSources), output(inOutputs),
                                                                              pids(sources, output, config) {
    this->updateTime = updateTime;
    this->timeout = timeout;
}

void SwervePIDController::start() {
    mainThread = std::make_unique<EctoWatchdog>("SwervePIDController", timeout, updateTime,
                                                std::bind(&SwervePIDController::update, this));
    mainThread->start();
}

void SwervePIDController::update() {
    pids.frontLeftWheel.update();
    pids.frontRightWheel.update();
    pids.backLeftWheel.update();
    pids.backRightWheel.update();
}

void SwervePIDController::set(double frontLeftWheelAngle, double frontRightWheelAngle, double backLeftWheelAngle,
                              double backRightWheelAngle) {
    pids.frontLeftWheel.setSetpoint(frontLeftWheelAngle);
    pids.frontRightWheel.setSetpoint(frontRightWheelAngle);

    pids.backLeftWheel.setSetpoint(backLeftWheelAngle);
    pids.backRightWheel.setSetpoint(backRightWheelAngle);
}

void SwervePIDController::setConfig(const PIDConfig &config) {
    pids.frontLeftWheel.setConfig(config);
    pids.frontRightWheel.setConfig(config);
    pids.backLeftWheel.setConfig(config);
    pids.backRightWheel.setConfig(config);
}