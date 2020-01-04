//
// Created by Abiel on 8/20/18.
//

#ifndef BOTBUSTERSREBIRTH_ROBOTPOSE2DCURVATURE_H
#define BOTBUSTERSREBIRTH_ROBOTPOSE2DCURVATURE_H

#include "Point2D.h"
#include "RobotPose2D.h"
#include "Rotation2D.h"
#include <EctoCSV/CSVWritable.h>
#include <json/json.hpp>

using nlohmann::json;

class RobotPose2DCurvature : public RobotPose2D {
public:
	RobotPose2DCurvature(const RobotPose2D &pose, double curvature, double dcurvature_ds);

	RobotPose2DCurvature(const RobotPose2D &pose, double curvature);

	RobotPose2DCurvature(const Point2D &point, const Rotation2D &rotation, double curvature, double dcurvature_ds);

	RobotPose2DCurvature(const Point2D &point, const Rotation2D &rotation, double curvature);

	RobotPose2DCurvature();

	void setCurvature(double curvature);

	void setDCurvature(double dcurvature);

	double getCurvature() const;

	double getDCurvature() const;

	std::string getCSVColumnNames() const override;

	std::string toCSV() const override;

private:
	double curvature;
	double dcurvature_ds;
};

void to_json(json &j, const RobotPose2DCurvature &pose);

void from_json(const json &j, RobotPose2DCurvature &pose);

#endif //BOTBUSTERSREBIRTH_ROBOTPOSE2DCURVATURE_H
