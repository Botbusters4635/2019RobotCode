//
// Created by abiel on 12/25/19.
//

#include "EctoControl/PathFollowers/Holonomic/SimpleHolonomicFollower.h"

SimpleHolonomicFollower::SimpleHolonomicFollower(const Path &path, double lookaheadDistance, double finishThreshold)  {
    this->currentPath = path;
    this->currentWaypointIndex = 0;
    this->pathSize = path.getPoses().size();

    this->lookaheadDistance = lookaheadDistance;
    this->finishTreshold = finishThreshold;
}

void SimpleHolonomicFollower::setNewPath(const Path &newPath) {
    currentPath = newPath;
    currentWaypointIndex = 0;
    this->pathSize = newPath.getPoses().size();
}

double SimpleHolonomicFollower::getDistanceToPathCompletion() const {
    return RobotPose2D::getDistanceBetweenPoints(lastPose, currentPath.getPoses().back());
}

bool SimpleHolonomicFollower::hasFinished() const {
    const double distance = getDistanceToPathCompletion();

    return std::abs(distance) <= lookaheadDistance;
}

RobotPose2D SimpleHolonomicFollower::update(const RobotPose2D &currentPose) {
    RobotPose2D outputPose;

    if(hasFinished()){
        outputPose = currentPose;
    } else if(currentWaypointIndex < pathSize){
        RobotPose2D currentTarget = currentPath[currentWaypointIndex];

        double distanceToTarget = RobotPose2D::getDistanceBetweenPoints(currentPose, currentTarget);

        while(distanceToTarget < lookaheadDistance){
            if(currentWaypointIndex < pathSize){
                currentTarget = currentPath[currentWaypointIndex];
                distanceToTarget = RobotPose2D::getDistanceBetweenPoints(currentPose, currentTarget);
                if(distanceToTarget < lookaheadDistance) currentWaypointIndex++;
            } else break;
        }

        outputPose = currentTarget;
    } else {
        outputPose = currentPath[currentWaypointIndex];
    }

    lastPose = currentPose;
    return outputPose;
}