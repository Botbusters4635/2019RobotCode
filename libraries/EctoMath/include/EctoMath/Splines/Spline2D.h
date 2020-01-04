//
// Created by Abiel on 8/18/18.
//

#ifndef BOTBUSTERSREBIRTH_SPLINE2D_H
#define BOTBUSTERSREBIRTH_SPLINE2D_H

#include "../DataTypes/Point2D.h"
#include "../DataTypes/Rotation2D.h"
#include "../DataTypes/RobotPose2D.h"
#include "../DataTypes/RobotPose2DCurvature.h"

class Spline2D {
public:
    virtual RobotPose2D getStartingPose() const = 0;
    virtual RobotPose2D getEndingPose() const = 0;

	virtual Point2D getPoint(double t) const = 0;

	virtual Rotation2D getHeading(double t) const = 0;

	virtual double getCurvature(double t) const = 0;

	virtual double getDCurvature(double t) const = 0;

	virtual double getVelocity(double t) const = 0;

	RobotPose2D getRobotPose2D(double t) const;

	RobotPose2DCurvature getRobotPose2DCurvature(double t) const;
};


#endif //BOTBUSTERSREBIRTH_SPLINE2D_H
