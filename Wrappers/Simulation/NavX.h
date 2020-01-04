//
// Created by Abiel on 1/6/19.
//

#ifndef BOTBUSTERSREBIRTH_NAVX_H
#define BOTBUSTERSREBIRTH_NAVX_H

#include <string>

class NavX {
public:
	static NavX &getInstance() {
		static NavX singletonInstance;
		return singletonInstance;
	}

	float GetPitch() const;

	void SetPitch(float pitch);

	float GetRoll() const;

	void SetRoll(float roll);

	float GetYaw() const;

	void SetYaw(float yaw);

	float GetCompassHeading() const;

	void SetCompassHeading(float compassHeading);

	float GetLinearAccelX() const;

	void SetLinearAccelX(float linearAccelX);

	float GetLinearAccelY() const;

	void SetLinearAccelY(float linearAccelY);

	float GetLinearAccelZ() const;

	void SetLinearAccelZ(float linearAccelZ);

	bool isIsMoving() const;

	void SetIsMoving(bool isMoving);

	bool isIsRotating() const;

	void SetIsRotating(bool isRotating);

	float GetFusedHeading() const;

	void SetFusedHeading(float fusedHeading);

	bool IsMagneticDisturbance() const;

	void SetIsMagneticDisturbance(bool isMagneticDisturbance);

	bool isIsMagnetometerCalibrated() const;

	void SetIsMagnetometerCalibrated(bool isMagnetometerCalibrated);

	float GetVelocityX() const;

	void SetVelocityX(float velocityX);

	float GetVelocityY() const;

	void SetVelocityY(float velocityY);

	float GetVelocityZ() const;

	void SetVelocityZ(float velocityZ);

	float GetDisplacementX() const;

	void SetDisplacementX(float displacementX);

	float GetDisplacementY() const;

	void SetDisplacementY(float displacementY);

	float GetDisplacementZ() const;

	void SetDisplacementZ(float displacementZ);

	double GetAngle() const;

	void SetAngle(double angle);

	double GetRate() const;

	void SetRate(double rate);

	float GetRawGyroX() const;

	void SetRawGyroX(float rawGyroX);

	float GetRawGyroY() const;

	void SetRawGyroY(float rawGyroY);

	float GetRawGyroZ() const;

	void SetRawGyroZ(float rawGyroZ);

	float GetRawAccelX() const;

	void SetRawAccelX(float rawAccelX);

	float GetRawAccelY() const;

	void SetRawAccelY(float rawAccelY);

	float GetRawAccelZ() const;

	void SetRawAccelZ(float rawAccelZ);

	float GetRawMagX() const;

	void SetRawMagX(float rawMagX);

	float GetRawMagY() const;

	void SetRawMagY(float rawMagY);

	float GetRawMagZ() const;

	void SetRawMagZ(float rawMagZ);

	std::string GetFirmwareVersion();

	void ResetDisplacement();

	void ClearError();

	void ZeroYaw();

	void Reset();

	double PIDGet();

private:
	float pitch, roll, yaw, compassHeading;

	float linearAccelX, linearAccelY, linearAccelZ;

	bool isMoving, isRotating;

	float fusedHeading;

	bool isMagneticDisturbance, isMagnetometerCalibrated;

	float velocityX, velocityY, velocityZ;

	float displacementX, displacementY, displacementZ;

	double angle, rate;

	float rawGyroX, rawGyroY, rawGyroZ;

	float rawAccelX, rawAccelY, rawAccelZ;

	float rawMagX, rawMagY, rawMagZ;

private:

	explicit NavX();

	NavX(const NavX &);

	NavX &operator=(const NavX &);
};


#endif //BOTBUSTERSREBIRTH_NAVX_H
