//
// Created by abiel on 10/9/19.
//

#ifndef ECTOCONTROL_SWERVEPIDCONTROLLER_H
#define ECTOCONTROL_SWERVEPIDCONTROLLER_H

#include <memory>
#include "EctoControl/EctoPID/EctoPID.h"
#include "EctoControl/EctoControllerSource.h"
#include "EctoControl/EctoControllerOutput.h"
#include "EctoUtilities/EctoWatchdog.h"

struct SwerveControllerSources {
    std::shared_ptr<EctoControllerSource> frontLeftSteer;
    std::shared_ptr<EctoControllerSource> frontRightSteer;

    std::shared_ptr<EctoControllerSource> backLeftSteer;
    std::shared_ptr<EctoControllerSource> backRightSteer;
};

struct SwerveControllerOutput {
    std::shared_ptr<EctoControllerOutput> frontLeftSteer;
    std::shared_ptr<EctoControllerOutput> frontRightSteer;

    std::shared_ptr<EctoControllerOutput> backLeftSteer;
    std::shared_ptr<EctoControllerOutput> backRightSteer;
};

//Used to hold all the EctoPID objects
class SwerveEctoPIDs {
public:
    SwerveEctoPIDs(SwerveControllerSources &sources, SwerveControllerOutput &output, const PIDConfig &config) :
            frontLeftWheel(*sources.frontLeftSteer, *output.frontLeftSteer, config),
            frontRightWheel(*sources.frontRightSteer, *output.frontRightSteer, config),
            backLeftWheel(*sources.backLeftSteer, *output.backLeftSteer, config),
            backRightWheel(*sources.backRightSteer, *output.backRightSteer, config) {
        ;
    }

    EctoPID frontLeftWheel, frontRightWheel;
    EctoPID backLeftWheel, backRightWheel;
};

//All the pid loops for swerve, under one roof™
class SwervePIDController {
public:
    SwervePIDController(SwerveControllerSources &inSources, SwerveControllerOutput &inOutputs, const PIDConfig &config,
                        std::chrono::milliseconds updateTime = std::chrono::milliseconds(20),
                        std::chrono::milliseconds timeout = std::chrono::milliseconds(1000));

    void
    set(double frontLeftWheelAngle, double frontRightWheelAngle, double backLeftWheelAngle, double backRightWheelAngle);

    void start();

    void setConfig(const PIDConfig &config);

private:
    void update();

    std::unique_ptr<EctoWatchdog> mainThread;

    PIDConfig config;
    SwerveControllerSources &sources;
    SwerveControllerOutput &output;

    SwerveEctoPIDs pids;

    std::chrono::milliseconds updateTime, timeout;
};

#endif //ECTOCONTROL_SWERVEPIDCONTROLLER_H
