//
// Created by hiram on 8/08/19.
//

#ifndef ECTOCONTROL_ECTOSPARK_H
#define ECTOCONTROL_ECTOSPARK_H

#include <rev/CANSparkMax.h>
#include "EctoMotor.h"

class EctoSpark : public EctoMotor {
public:
	explicit EctoSpark(int id, const std::string &name = " ");
	
	void setClosedLoopOutputRange(double minimum, double maximum) override;
	
	void invert(bool state) override;
	
	bool isInverted() const override;
	
	void invertSensor(bool state) override;
	
	bool isSensorInverted() const override;
	
	void setPIDConfig(const PIDConfig &pidConfig, int profileSlot) override;
	
	void enableMotorCurrentLimit(bool state) override;
	
	void setMotorCurrentLimit(double current) override;
	
	void setClosedLoopRampRate(double rampRate) override;
	
	void setOpenLoopRampRate(double rampRate) override;
	
	void setBrakeOnIdle(bool state) override;
	
	double getPercentOutput() const override;
	
	void setPercentOutput(double value) override;
	
	void disable() override;
	
	bool isDisabled() const override;
	
	void setPosition(double position) override;
	
	double getMotorTemperature() const override;
	
	double getMotorCurrent() const override;
	
	void setMotorCurrentTarget(double value) override;
	
	double getMotorVoltage() const override;
	
	void setArbitraryFeedForward(double feedForward) override;
	
	void enableLimitSwitches(bool state) override;
	
	void setForwardSoftLimit(double radians) override;
	
	void enableForwardSoftLimit(bool state) override;
	
	void setReverseSoftLimit(double radians) override;
	
	void enableReverseSoftLimit(bool state) override;
	
	void disableLimits() override;
	
	void configureMotionMagicVelocity(double velocity) override;
	
	void configureMotionMagicAcceleration(double acceleration) override;
	
	void configureMotionMagicSCurve(double sCurve) override;
	
	void setMotionMagicTarget(double value) override;
	
	void setAnalogPositionConversionFactor(double conversionFactor) override;
	
	void setAnalogVelocityConversionFactor(double conversionFactor) override;
	
	void setPositionTarget(double position) override;
	
	void setVelocityTarget(double velocity) override;
	
	void setEncoderCodes(int codes) override;
	
	int getEncoderCodes() const override;
	
	double getPotPosition() const override;
	
	double getPotVelocity() const override;
	
	double getQuadPosition() const override;
	
	double getQuadVelocity() const override;
	
	void setPotAsClosedLoopSource() override;
	
	void setQuadAsClosedLoopSource() override;
	
	void setAnalogOffset(double analogOffset) override;
	
	void factoryReset() override;
	
	std::string getFirmwareVersion() const override;
	
	void setSwitchPolarity(bool normallyClosed) override;
	
	bool getReverseLimitSwitch() const override;
	
	bool getForwardLimitSwitch() const override;

private:
	std::unique_ptr<rev::CANSparkMax> sparkBase;
	std::unique_ptr<rev::CANPIDController> pidControllerBase;
	
	std::unique_ptr<rev::CANDigitalInput> forwardLimitSwitch;
	std::unique_ptr<rev::CANDigitalInput> reverseLimitSwitch;
	
	std::unique_ptr<rev::CANAnalog> analogSensor;
	std::unique_ptr<rev::CANEncoder> encoderSensor;
	bool isUsingBrushlessEncoder = true;
	
	double currentFeedForward = 0.0;
	
	double currentLimit = 40;
	
	//There's no way to disable the current limit so set it to something high
	const double maximumCurrentLimit = 80;
	
	double analogOffset = 0;
	
	mutable double lastPotRunTime = 0;
	mutable double lastPotSensorRead = 0;
	const double sensorReadTimeout = 0.04;
};


#endif //ECTOCONTROL_ECTOSPARK_H
