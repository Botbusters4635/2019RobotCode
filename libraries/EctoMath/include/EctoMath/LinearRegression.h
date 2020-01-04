//
// Created by Abiel on 8/25/18.
//

#ifndef BOTBUSTERSREBIRTH_LINEARREGRESSION_H
#define BOTBUSTERSREBIRTH_LINEARREGRESSION_H

#include <vector>
#include <stdexcept>
#include <cmath>

//From https://algs4.cs.princeton.edu/14analysis/LinearRegression.java.html

using std::vector;
using std::pair;

class LinearRegression {
public:
	//First is x, second is y
	explicit LinearRegression(const vector<pair<double, double>> &input);

	LinearRegression(double svar0, double svar1, double intercept, double slope, double R2);

	double getIntercept() const;

	double getSlope() const;

	double getR2() const;

	double predict(double x) const;

private:
	double intercept, slope;
	double r2;
	double svar0, svar1;
};


#endif //BOTBUSTERSREBIRTH_LINEARREGRESSION_H
