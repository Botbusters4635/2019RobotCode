//
// Created by abiel on 10/23/19.
//

#ifndef ECTOCONTROL_LINEARODOMETRY_H
#define ECTOCONTROL_LINEARODOMETRY_H

#include <EctoMath/DataTypes/RobotPose2D.h>
#include <EctoMath/DataTypes/Twist2D.h>
#include <Eigen/Geometry>
#include "EctoControl/Odometry/Odometry.h"

/**
 * Calculates odometry with linear interpolation
 */
class LinearOdometry : public Odometry {
public:
    LinearOdometry(const RobotPose2D &startingPosition);
    LinearOdometry();

    void updateOdometry_distance(const Twist2D &distance) override;

    void updateOdometry_velocity(const Twist2D &velocity, double dt) override;

    RobotPose2D getPose() const override;

private:
    Twist2D lastDistance;

    RobotPose2D currentPose;
};


#endif //ECTOCONTROL_LINEARODOMETRY_H
