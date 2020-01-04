//
// Created by abiel on 10/23/19.
//

#include "EctoControl/Odometry/ExponentialOdometry.h"
#include "EctoMath/EctoMath.h"

ExponentialOdometry::ExponentialOdometry(const RobotPose2D &startingPosition) {
    currentPose = startingPosition;
}

ExponentialOdometry::ExponentialOdometry() : ExponentialOdometry(RobotPose2D(0,0,0)){
    ;
}

#include <iostream>

void ExponentialOdometry::updateOdometry_distance(const Twist2D &distance) {
    Twist2D deltaDistance = distance - lastDistances;
    //Use given yaw (not delta)
    deltaDistance.setDtheta(distance.getDtheta());

    updateOdometry_velocity(deltaDistance, 1);

    lastDistances = distance;
}

void ExponentialOdometry::updateOdometry_velocity(const Twist2D &velocity, double dt) {
    const double yaw = velocity.getDtheta();

    const double angularVelocity = (yaw - lastYaw) / dt;
    const double angleDelta = angularVelocity * dt;

    Eigen::Matrix<double, 3, 1> twistMatrix;
    twistMatrix << velocity.getDx(), velocity.getDy(), angleDelta;

    const double angleDeltaSin = std::sin(angleDelta);
    const double angleDeltaCos = std::cos(angleDelta);

    const double yawSin = std::sin(yaw);
    const double yawCos = std::cos(yaw);

    Eigen::Matrix<double, 3, 3> rotationMatrix;
    rotationMatrix <<
                   yawCos, -yawSin, 0,
            yawSin, yawCos, 0,
            0, 0, 1;

    Eigen::Matrix<double, 3, 3> deltaMatrix;
    deltaMatrix <<
                angleDeltaSin / angularVelocity, (angleDeltaCos - 1.0) / angularVelocity, 0,
            (1.0 - angleDeltaCos) / angularVelocity, angleDeltaSin / angularVelocity, 0,
            0, 0, dt;

    Eigen::Matrix<double, 3, 1> outputMatrix;

    if(angleDelta != 0){
        outputMatrix = rotationMatrix * deltaMatrix * twistMatrix;
    } else {
        //std::cout << "NAN" << std::endl;
        outputMatrix = rotationMatrix * twistMatrix;
    }

//    std::cout << "Rotation: " << std::endl << rotationMatrix << std::endl << std::endl;
//    std::cout << "Delta: " << std::endl << deltaMatrix << std::endl << std::endl;
//    std::cout << "Twist: " << std::endl << twistMatrix << std::endl << std::endl;
//    std::cout << "Output: " << std::endl << outputMatrix << std::endl << std::endl;

    currentPose.setX(currentPose.getX() + outputMatrix(0, 0));
    currentPose.setY(currentPose.getY() + outputMatrix(1, 0));
    currentPose.setHeading(Rotation2D(yaw));

    lastYaw = yaw;

    //std::cout << "END" << std::endl;
}

RobotPose2D ExponentialOdometry::getPose() const {
    return currentPose;
}