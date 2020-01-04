//
// Created by Abiel on 1/17/19.
//

#ifndef BOTBUSTERSREBIRTH_ECTOTALONUTILS_H
#define BOTBUSTERSREBIRTH_ECTOTALONUTILS_H

#include <cstdint>
#include <cmath>

namespace EctoTalonUtils {
	double RPMToNativeUnits(double rpm, uint16_t nativeUnitsPerRev);

	double nativeUnitsToRPM(int nativeUnits, uint16_t nativeUnitsPerRev);

	double MSToNativeUnits(double MS, double wheelDiameter, uint16_t nativeUnitsPerRev);

	double nativeUnitsToMS(int nativeUnits, double wheelDiameter, uint16_t nativeUnitsPerRev);

	double MToNativeUnits(double M, double wheelDiameter, uint16_t nativeUnitsPerRev);
}

#endif //BOTBUSTERSREBIRTH_ECTOTALONUTILS_H
