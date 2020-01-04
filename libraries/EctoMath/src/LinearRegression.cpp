//
// Created by Abiel on 8/25/18.
//

#include "EctoMath/LinearRegression.h"

LinearRegression::LinearRegression(const vector<pair<double, double>> &input) {
	if (input.empty())
		throw std::runtime_error("Tried to calculate the linear regression of an empty vector");

	std::size_t n = input.size();

	double sumx = 0.0;
	double sumy = 0.0;
	double sumx2 = 0.0;

	for (const pair<double, double> &point : input) {
		sumx += point.first;
		sumx2 += std::pow(point.first, 2.0);
		sumy += point.second;
	}

	double xbar = sumx / n;
	double ybar = sumy / n;

	double xxbar = 0.0;
	double yybar = 0.0;
	double xybar = 0.0;

	for (const pair<double, double> &point : input) {
		xxbar += (point.first - xbar) * (point.first - xbar);
		yybar += (point.second - ybar) * (point.second - ybar);
		xybar += (point.first - xbar) * (point.second - ybar);
	}

	this->slope = xybar / xxbar;
	this->intercept = ybar - slope * xbar;

	double rss = 0.0;
	double ssr = 0.0;

	for (const pair<double, double> &point : input) {
		double fit = this->slope * point.first + intercept;

		rss += std::pow((fit - point.second), 2.0);
		ssr += std::pow((fit - ybar), 2.0);
	}

	int degreesOfFreedom = n - 2;

	r2 = ssr / yybar;
	double svar = rss / degreesOfFreedom;

	svar1 = svar / xbar;
	svar0 = svar / n + std::pow(xbar, 2.0) * svar1;
}

LinearRegression::LinearRegression(double svar0, double svar1, double intercept, double slope, double R2) {
	this->svar0 = svar0;
	this->svar1 = svar1;

	this->intercept = intercept;
	this->slope = slope;

	this->r2 = R2;
}

double LinearRegression::getIntercept() const {
	return intercept;
}

double LinearRegression::getSlope() const {
	return slope;
}

double LinearRegression::getR2() const {
	return r2;
}

double LinearRegression::predict(double x) const {
	return slope * x + intercept;
}