//
// Created by abiel on 12/25/19.
//

#ifndef ECTOCONTROL_ODOMETRY_H
#define ECTOCONTROL_ODOMETRY_H

#include <chrono>
#include <EctoMath/DataTypes/RobotPose2D.h>
#include <EctoMath/DataTypes/Twist2D.h>

/**
 * Odometry base class
 */

class Odometry {
public:
    /**
     * Using change in accumulated distance
     * Gets current yaw from dTheta (Twist2D)
     * @param distance
     */
    virtual void updateOdometry_distance(const Twist2D &distance) = 0;

    virtual void updateOdometry_velocity(const Twist2D &velocity, double dt) = 0;
    void updateOdometry_velocity_dt(const Twist2D &velocity);

    virtual RobotPose2D getPose() const = 0;

private:
    bool lastRanTimeSet = false;

    std::chrono::high_resolution_clock::time_point lastRanTime;
};

#endif //ECTOCONTROL_ODOMETRY_H
