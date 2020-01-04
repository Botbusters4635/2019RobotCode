//
// Created by abiel on 10/23/19.
//

#include "EctoControl/Odometry/LinearOdometry.h"
#include <iostream>

LinearOdometry::LinearOdometry(const RobotPose2D &startingPosition){
    currentPose = startingPosition;
}

LinearOdometry::LinearOdometry() : LinearOdometry(RobotPose2D(0,0,0)) {
    ;
}

void LinearOdometry::updateOdometry_distance(const Twist2D &distance) {
    Twist2D deltaDistance = distance - lastDistance;
    //Use given yaw (not delta)
    deltaDistance.setDtheta(distance.getDtheta());

    updateOdometry_velocity(deltaDistance, 1);

    lastDistance = distance;
}

void LinearOdometry::updateOdometry_velocity(const Twist2D &velocity, double dt) {
    const Twist2D distance = velocity * dt;

    Eigen::Vector2d positionVector(distance.getDx(), distance.getDy());
    const Eigen::Rotation2Dd rotation(velocity.getDtheta());

    positionVector = rotation.toRotationMatrix() * positionVector;

    currentPose.setX(currentPose.getX() + positionVector(0, 0));
    currentPose.setY(currentPose.getY() + positionVector(1, 0));
    currentPose.setHeading(Rotation2D(velocity.getDtheta()));
}

RobotPose2D LinearOdometry::getPose() const {
    return currentPose;
}