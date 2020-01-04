//
// Created by hiram on 8/08/19.
//

#ifndef BOTBUSTERS_REBIRTH_ECTOMOTOR_H
#define BOTBUSTERS_REBIRTH_ECTOMOTOR_H

#include <EctoControl/EctoControllerOutput.h>
#include <EctoControl/EctoControllerSource.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <rev/CANSparkMax.h>
#include "DataTypes/EctoMotorHealth.h"
#include "DataTypes/EctoMotorMode.h"
#include "DataTypes/EctoMotorConfig.h"
#include "DataTypes/EctoMotorFeedback.h"
#include <frc/PIDOutput.h>
#include <frc/PIDSource.h>
#include "EctoSendable/EctoSendable.h"

/**
 * Base structure for a motor controller
 */
//TODO Add get PID error
class EctoMotor
		: public EctoControllerOutput, public EctoControllerSource, public frc::PIDOutput, public frc::PIDSource, public EctoSendable  {
public:
	explicit EctoMotor(int id, const std::string &name);
	
	std::string getName() const;
	
	virtual void factoryReset() = 0;
	
	void setControlMode(EctoControlMode controlMode);
	
	EctoControlMode getControlMode() const;
	
	void setFeedbackMode(EctoMotorFeedback feedbackMode);
	
	virtual void setSwitchPolarity(bool normallyClosed) = 0;
	
	EctoMotorFeedback getFeedbackMode() const;
	
	/**
	 * Get the current state depending on the current control mode
	 */
	double get() const;
	
	/**
	 * EctoPIDSource implementation
	 * @return
	 */
	
	/**
	 * Get position in radians
	 */
	double getPosition() const override;
	
	/**
	 * Get velocity in radians per second
	 */
	double getVelocity() const override;
	
	int getId();
	
	void set(double value);
	
	void set(double value, EctoControlMode controlMode);
	
	virtual std::string getFirmwareVersion() const = 0;
	
	//Inverts both motor and sensor phase
	virtual void invert(bool state) = 0;
	
	virtual bool isInverted() const = 0;
	
	virtual void invertSensor(bool state) = 0;
	
	virtual bool isSensorInverted() const = 0;
	
	virtual void setPIDConfig(const PIDConfig &pidConfig, int profileSlot) = 0;
	
	virtual void setBrakeOnIdle(bool state) = 0;
	
	virtual void enableMotorCurrentLimit(bool state) = 0;
	
	virtual void setMotorCurrentLimit(double current) = 0;
	
	virtual void setMotorCurrentTarget(double value) = 0;
	
	virtual void setClosedLoopOutputRange(double minimum, double maximum) = 0;
	
	virtual void setClosedLoopRampRate(double rampRate) = 0;
	
	virtual void setOpenLoopRampRate(double rampRate) = 0;
	
	virtual void setPercentOutput(double value) = 0;
	
	virtual double getPercentOutput() const = 0;
	
	/**
	 * Set the current position in radians
	 * @param position
	 */
	virtual void setPosition(double position) = 0;
	
	virtual void setPositionTarget(double position) = 0;
	
	virtual void setVelocityTarget(double velocity) = 0;
	
	virtual double getMotorTemperature() const = 0;
	
	virtual double getMotorCurrent() const = 0;
	
	virtual double getMotorVoltage() const = 0;
	
	virtual void setEncoderCodes(int codes) = 0;
	
	virtual int getEncoderCodes() const = 0;
	
	/**
	 * (In volts)
	 * Feedforward is not set until the next set command is sent
	 */
	virtual void setArbitraryFeedForward(double feedForward) = 0;
	
	/**
	 * EctoPIDOutput implementation
	 * @param set
	 */
	void outputSet(double set) final;
	
	virtual void disable() = 0;
	
	virtual bool isDisabled() const = 0;
	
	virtual void enableLimitSwitches(bool state) = 0;
	
	virtual void setForwardSoftLimit(double radians) = 0;
	
	virtual void enableForwardSoftLimit(bool state) = 0;
	
	virtual void setReverseSoftLimit(double radians) = 0;
	
	virtual void enableReverseSoftLimit(bool state) = 0;
	
	virtual bool getReverseLimitSwitch() const = 0;
	
	virtual bool getForwardLimitSwitch() const = 0;
	
	virtual void disableLimits() = 0;
	
	virtual void configureMotionMagicVelocity(double velocity) = 0;
	
	virtual void configureMotionMagicAcceleration(double acceleration) = 0;
	
	virtual void configureMotionMagicSCurve(double sCurve) = 0;
	
	virtual void setMotionMagicTarget(double value) = 0;
	
	virtual void setAnalogPositionConversionFactor(double conversionFactor) = 0;
	
	virtual void setAnalogVelocityConversionFactor(double conversionFactor) = 0;
	
	virtual double getPotPosition() const = 0;
	
	virtual double getPotVelocity() const = 0;
	
	virtual double getQuadPosition() const = 0;
	
	virtual double getQuadVelocity() const = 0;
	
	virtual void setPotAsClosedLoopSource() = 0;
	
	virtual void setQuadAsClosedLoopSource() = 0;
	
	void setControllerSourceMode(EctoControlMode mode);
	
	void PIDWrite(double output) override;
	
	double PIDGet() override;
	
	virtual void setAnalogOffset(double analogOffset) = 0;
	
	EctoSendableData serializeData() const override;

protected:
	int id;
	std::string name;
	EctoControlMode controlMode = EctoControlMode::Percent;
	EctoMotorFeedback feedbackMode = EctoMotorFeedback::QuadEncoder;
	
	EctoControlMode controllerSourceMode = EctoControlMode::Percent;
	
	static std::shared_ptr<spdlog::logger> log;
	bool disabled = false;
private:
	std::chrono::system_clock::time_point lastEncoderDetection = std::chrono::system_clock::now();
};

#endif //BOTBUSTERS_REBIRTH_ECTOMOTOR_H
