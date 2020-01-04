//
// Created by abiel on 12/25/19.
//

#ifndef ECTOCONTROL_PATHFOLLOWER_H
#define ECTOCONTROL_PATHFOLLOWER_H

#include "EctoMath/DataTypes/RobotPose2D.h"
#include "EctoControl/Path/Path.h"

class PathFollower {
public:
    /**
     * Sets a new target path
     * @param newPath
     */
    virtual void setNewPath(const Path &newPath) = 0;

    virtual RobotPose2D update(const RobotPose2D &currentPose) = 0;

    //How close is the follower to completing the path
    virtual double getDistanceToPathCompletion() const = 0;

    virtual bool hasFinished() const = 0;
};

#endif //ECTOCONTROL_PATHFOLLOWER_H
