//
// Created by Abiel on 8/20/18.
//

#include "EctoMath/DataTypes/RobotPose2DCurvature.h"

RobotPose2DCurvature::RobotPose2DCurvature(const RobotPose2D &pose, double curvature, double dcurvature_ds)
		: RobotPose2D(pose) {
	this->curvature = curvature;
	this->dcurvature_ds = dcurvature_ds;
}

RobotPose2DCurvature::RobotPose2DCurvature(const RobotPose2D &pose, double curvature) : RobotPose2D(pose) {
	this->curvature = curvature;
	this->dcurvature_ds = 0.0;
}

RobotPose2DCurvature::RobotPose2DCurvature(const Point2D &point, const Rotation2D &rotation, double curvature,
                                           double dcurvature_ds) : RobotPose2D(point, rotation) {
	this->curvature = curvature;
	this->dcurvature_ds = dcurvature_ds;
}

RobotPose2DCurvature::RobotPose2DCurvature(const Point2D &point, const Rotation2D &rotation, double curvature)
		: RobotPose2D(point, rotation) {
	this->curvature = curvature;
	this->dcurvature_ds = 0.0;
}

RobotPose2DCurvature::RobotPose2DCurvature() : RobotPose2D() {
	this->curvature = 0.0;
	this->dcurvature_ds = 0.0;
}

void RobotPose2DCurvature::setCurvature(double curvature) {
	this->curvature = curvature;
}

void RobotPose2DCurvature::setDCurvature(double dcurvature) {
	this->dcurvature_ds = dcurvature;
}

double RobotPose2DCurvature::getCurvature() const {
	return curvature;
}

double RobotPose2DCurvature::getDCurvature() const {
	return dcurvature_ds;
}

std::string RobotPose2DCurvature::getCSVColumnNames() const {
	std::stringstream stream;

	stream << RobotPose2D::getCSVColumnNames() << ",Curvature,dCurvature_ds";

	return stream.str();
}

std::string RobotPose2DCurvature::toCSV() const {
	std::stringstream stream;

	stream << getX() << ',' << getY() << ',' << getCurvature() << ',' << getDCurvature() << '\n';

	return stream.str();
}

void to_json(json &j, const RobotPose2DCurvature &pose) {
	j = json{{"pose",       (RobotPose2D) pose},
	         {"curvature",  pose.getCurvature()},
	         {"dcurvature", pose.getDCurvature()}};
}

void from_json(const json &j, RobotPose2DCurvature &pose) {
	j.at("pose").get_to<RobotPose2D>((RobotPose2D &) pose);

	pose.setCurvature(j.at("curvature").get<double>());
	pose.setDCurvature(j.at("dcurvature").get<double>());
}