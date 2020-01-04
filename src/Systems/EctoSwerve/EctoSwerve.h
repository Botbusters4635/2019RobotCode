//
// Created by abiel on 1/2/20.
//

#ifndef BOTBUSTERSREBIRTH_ECTOSWERVE_H
#define BOTBUSTERSREBIRTH_ECTOSWERVE_H

#include <EctoModule/System.h>
#include <InputHandlers/JoystickAxisExpo.h>
#include <InputHandlers/EctoButton.h>

#include <EctoControl/SimpleControllerSource.h>
#include <EctoControl/SimpleControllerOutput.h>

#include <EctoControl/Kinematics/Swerve/SwerveKinematics.h>
#include <EctoControl/Kinematics/Swerve/SwerveMotorValues.h>
#include <EctoControl/SwervePIDController/SwervePIDController.h>

#include "Core/EctoInput/EctoInput.h"
#include <AHRS.h>
#include <Core/MotorHandler/MotorHandler.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalOutput.h>
#include <mutex>
#include <thread>
#include "Sensors/EctoDistanceSensor.h"

#include <EctoMath/EctoMath.h>
#include <EctoMath/DataTypes/RobotPose2D.h>


struct EctoSwerveConfig {
	//Angles to which the robot will snap to
	std::vector<double> snappableAngles {0, 2.69, M_PI / 2.0, 0.58, M_PI, -0.58, -M_PI / 2.0, -2.72};
};

class EctoSwerve : public System{
public:
	explicit EctoSwerve(const EctoSwerveConfig &config);
	
	void initRobot() override;
	void updateRobot() override;
	
	void zeroYaw();
	float getYaw(bool useZero = true) const;
	
	/**
	 * Moves at a target velocity
	 * @param target
	 * @param overrideControllers when set to true pending rotateToHeading and setTargetPositions are interrupted and set back to 0
	 * @param transformToFieldOriented
	 */
	void setTargetVelocity(const Twist2D &target, const Point2D &centerOfRotation = Point2D(0,0), bool overrideControllers = false, bool transformToFieldOriented = true);
	
	/**
	 * Ignores angular velocity given from setVelocityTarget while rotating
	 * @param target
	 */
	void rotateToHeading(double target);
	
	/**
	 * Moves to position has priority over heading rotation
	 * @param targetPose
	 */
	void setTargetPosition(const RobotPose2D &targetPose);
	
	SwerveMotorValues getCurrentMotorState() const;
	
	/**
	 * Transforms a Twist2D into being field oriented
	 * @param target
	 * @return
	 */
	Twist2D transformToFieldReference(const Twist2D &target) const;
	
private:
	void initNetworkTables();
	void updateNetworkTables();
	
	bool checkIfTargetHeadingReached() const;
	bool checkIfTargetPositionReached() const;
	
	void writeMotors(const SwerveMotorValues &values);
	
	EctoSwerveConfig config;
	
	//TODO Implement odometry for setTargetPosition
	/**
	 * Kinematics
	 */
	std::unique_ptr<SwerveKinematics> kinematics;
	
	/**
	 * PIDS
	 */
	PIDConfig steerPIDConfig, headingPIDConfig;
	
	std::unique_ptr<SwervePIDController> swervePidController;
	
	std::unique_ptr<EctoPID> targetHeadingController;
	
	/**
	 * Controller Sources / Outputs
	 */
	SwerveControllerSources swervePIDSources;
	SwerveControllerOutput swervePIDOutputs;
	
	SimpleControllerSource headingSource;
	SimpleControllerOutput headingOutput;
	
	/**
	 * Motors
	 */
	MotorHandler &motorHandler = MotorHandler::getInstance();
	
	std::shared_ptr<EctoMotor> frontRightWheel, frontLeftWheel, backLeftWheel, backRightWheel;
	std::shared_ptr<EctoMotor> frontRightSteer, frontLeftSteer, backLeftSteer, backRightSteer;
	
	double frontRightAnalogOffset, frontLeftAnalogOffset, backLeftAnalogOffset, backRightAnalogOffset;
	
	/**
	 * Heading
	 */
	const double maxHeadingRate = 2 * M_PI; //Max heading change per second
	double headingZero = 0.0;
	
	mutable AHRS ahrs = AHRS(SPI::Port::kMXP); //Has to be mutable because some functions (getYaw) are not const
	
	/**
	 * Time
	 */
	double timeStep = 0.0;
	double lastTimeUpdate;
	
	 /**
	  * Targets / Status
	  */
	 Twist2D actualVelocityTarget; //Velocity target given to the motors
	 Twist2D setVelocityTarget; //Velocity target from setTargetVelocity
	 
	 Point2D centerOfRotation;
	 Point2D targetCenterOfRotation; //Target center of rotation from setTargetVelocity
	 
	 double targetHeading = 0;
	 RobotPose2D targetPosition;
	 
	 /**
	  * Controller statuses
	  */
	 bool rotatingToAngle = false;
	 bool movingToPosition = false;
	 
	const double angleCompletionThreshold = 0.04666;
	const double positionDistanceThreshold = 0.1;
	
	/**
	 * Threads / mutexes
	 */
	void updateInverseKinematics();
	std::unique_ptr<std::thread> inverseKinematicsThread;
	std::mutex inverseKinematicsTarget;
	
	//TODO Add Odometry Thread
};



#endif //BOTBUSTERSREBIRTH_ECTOSWERVE_H
