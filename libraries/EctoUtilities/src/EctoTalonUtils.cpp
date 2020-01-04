//
// Created by Abiel on 1/17/19.
//

#include "EctoUtilities/EctoTalonUtils.h"

//Converts RPM to NativeUnits as defined in p. 88 of Talon Software Manual
double EctoTalonUtils::RPMToNativeUnits(double rpm, uint16_t nativeUnitsPerRev) {
	return rpm / (600.0 / nativeUnitsPerRev);
}

//Converts NativeUnits to RPM as defined in p. 88 of Talon Software Manual
double EctoTalonUtils::nativeUnitsToRPM(int nativeUnits, uint16_t nativeUnitsPerRev) {
	return nativeUnits * (600.0 / nativeUnitsPerRev);
}

double EctoTalonUtils::MSToNativeUnits(double MS, double wheelDiameter, uint16_t nativeUnitsPerRev) {
	return MS / (wheelDiameter * M_PI) * nativeUnitsPerRev;
}

double EctoTalonUtils::nativeUnitsToMS(int nativeUnits, double wheelDiameter, uint16_t nativeUnitsPerRev) {
	return (nativeUnits / nativeUnitsPerRev) * (wheelDiameter * M_PI);
}

double EctoTalonUtils::MToNativeUnits(double M, double wheelDiameter, uint16_t nativeUnitsPerRev) {
	return (M / (wheelDiameter * M_PI)) * nativeUnitsPerRev;
}