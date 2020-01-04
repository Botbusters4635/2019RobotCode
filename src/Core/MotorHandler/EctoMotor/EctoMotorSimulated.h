//
// Created by abiel on 12/30/19.
//

#ifndef BOTBUSTERSREBIRTH_ECTOMOTORSIMULATED_H
#define BOTBUSTERSREBIRTH_ECTOMOTORSIMULATED_H

#include "EctoMotor.h"

//TODO Add rx from NT
class EctoMotorSimulated : public EctoMotor{
public:
	EctoMotorSimulated(int id, const std::string &name);
	
	void factoryReset() override;
	
	void setSwitchPolarity(bool normallyClosed) override;
	
	std::string getFirmwareVersion() const override;
	
	void invert(bool state) override;
	bool isInverted() const override;
	
	void invertSensor(bool state) override;
	bool isSensorInverted() const override;
	
	void setPIDConfig(const PIDConfig &pidConfig, int profileSlot = 0) override;
	
	void setBrakeOnIdle(bool state) override;
	
	void enableMotorCurrentLimit(bool state) override;
	
	void setMotorCurrentLimit(double current) override;
	
	void setMotorCurrentTarget(double value) override;
	
	void setClosedLoopOutputRange(double minimum, double maximum) override;
	
	void setClosedLoopRampRate(double rampRate) override;
	
	void setOpenLoopRampRate(double rampRate) override;
	
	void setPercentOutput(double value) override;
	double getPercentOutput() const override;
	
	void setPosition(double position) override;
	void setPositionTarget(double position) override;
	void setVelocityTarget(double velocity) override;
	
	double getMotorTemperature() const override;
	double getMotorCurrent() const override;
	double getMotorVoltage() const override;
	
	void setEncoderCodes(int codes) override;
	int getEncoderCodes() const override;
	
	void setArbitraryFeedForward(double feedForward) override;
	
	void disable() override;
	bool isDisabled() const override;
	
	void enableLimitSwitches(bool state) override;
	void setForwardSoftLimit(double radians) override;
	void setReverseSoftLimit(double radians) override;
	void enableReverseSoftLimit(bool state) override;
	
	bool getReverseLimitSwitch() const override;
	bool getForwardLimitSwitch() const override;
	
	void disableLimits() override;
	
	void configureMotionMagicVelocity(double velocity) override;
	void configureMotionMagicAcceleration(double acceleration) override;
	
	void configureMotionMagicSCurve(double sCurve) override;
	
	void setMotionMagicTarget(double value) override;
	
	double getPotPosition() const override;
	double getPotVelocity() const override;
	double getQuadPosition() const override;
	double getQuadVelocity() const override;
	
	void setPotAsClosedLoopSource() override;
	void setQuadAsClosedLoopSource() override;
	
	void setAnalogOffset(double analogOffset) override;
	
	void enableForwardSoftLimit(bool state) override;
	
	void setAnalogPositionConversionFactor(double factor) override;
	void setAnalogVelocityConversionFactor(double factor) override;
	
private:
	bool switchPolarity = false;
	bool inverted = false;
	bool sensorInverted = false;
	bool isBrakeEnabled = false;
	
	bool isMotorCurrentLimitEnabled = false;
	double currentLimit = 0;
	
	double maximumOutputRate, minimumOutputRate;
	double closedLoopRampRate, openLoopRampRate;
	
	std::array<PIDConfig, 2> pidConfigs;
	
	double currentPosition, currentVelocity;
	double positionTarget, velocityTarget;
	
	int encoderCodes;
};


#endif //BOTBUSTERSREBIRTH_ECTOMOTORSIMULATED_H
