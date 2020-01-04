//
// Created by abiel on 9/20/19.
//

#ifndef ECTOCONTROL_ECTOMAGIC_H
#define ECTOCONTROL_ECTOMAGIC_H

#include "EctoControl/EctoController.h"
#include "EctoControl/MotionProfiles/TrapezoidalMotionProfile.h"
#include <chrono>

/**
 * Magic motion equivalent
 */

class EctoMagic : public EctoController {
public:
    EctoMagic(EctoController &controller, const MotionProfileConfig &motionProfileConfig);

    void setMotionProfileConfig(const MotionProfileConfig &motionProfileConfig);

    void setSetpoint(double setpoint) override;
    double getSetpoint() const override;

    double getError() const override;

    void update() override;

    const EctoControllerOutput& getControllerOutput() const override;
    const EctoControllerSource& getControllerSource() const override;

private:
    std::chrono::high_resolution_clock::time_point startTime;

    TrapezoidalMotionProfile motionProfile;
    MotionProfileConfig motionProfileConfig;

    EctoController &baseController;
};

#endif //ECTOCONTROL_ECTOMAGIC_H
