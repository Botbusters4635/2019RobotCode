//
// Created by abiel on 1/2/20.
//

#include "EctoSwerve.h"

EctoSwerve::EctoSwerve(const EctoSwerveConfig &config) : System("EctoSwerve") {
	/*
	 * Kinematics init
	 */
	const double length = settings->getNumber("Swerve", "Length");
	const double width = settings->getNumber("Swerve", "Width");
	kinematics = std::make_unique<SwerveKinematics>(length, width);
	
	/*
	 * Heading PID Controller Config
	 */
	headingPIDConfig.continous = true;
	headingPIDConfig.maxInput = M_PI;
	headingPIDConfig.minInput = -M_PI;
	headingPIDConfig.clamped = true;
	headingPIDConfig.maxOutput = 4.0 * M_PI;
	headingPIDConfig.minOutput = -4.0 * M_PI;
	headingPIDConfig.deadband = 0.002;
	headingPIDConfig.p = 0.9;
	headingPIDConfig.i = 0.0;
	headingPIDConfig.d = 0.003;
	
	targetHeadingController = std::make_unique<EctoPID>(headingSource, headingOutput, headingPIDConfig);
	
	/*
	 * Spark init
	 */
	frontLeftWheel = motorHandler.getMotor("frontLeftWheel");
	frontRightWheel = motorHandler.getMotor("frontRightWheel");
	backLeftWheel = motorHandler.getMotor("backLeftWheel");
	backRightWheel = motorHandler.getMotor("backRightWheel");
	
	frontLeftSteer = motorHandler.getMotor("frontLeftSteer");
	frontRightSteer = motorHandler.getMotor("frontRightSteer");
	backLeftSteer = motorHandler.getMotor("backLeftSteer");
	backRightSteer = motorHandler.getMotor("backRightSteer");
	
	/**
	 * Feedback and source mode
	 */
	frontRightSteer->setFeedbackMode(EctoMotorFeedback::Potentiometer);
	frontLeftSteer->setFeedbackMode(EctoMotorFeedback::Potentiometer);
	backRightSteer->setFeedbackMode(EctoMotorFeedback::Potentiometer);
	backLeftSteer->setFeedbackMode(EctoMotorFeedback::Potentiometer);
	
	frontRightSteer->setControllerSourceMode(EctoControlMode::Position);
	frontLeftSteer->setControllerSourceMode(EctoControlMode::Position);
	backRightSteer->setControllerSourceMode(EctoControlMode::Position);
	backLeftSteer->setControllerSourceMode(EctoControlMode::Position);
	
	frontRightWheel->setFeedbackMode(EctoMotorFeedback::QuadEncoder);
	frontLeftWheel->setFeedbackMode(EctoMotorFeedback::QuadEncoder);
	backRightWheel->setFeedbackMode(EctoMotorFeedback::QuadEncoder);
	backLeftWheel->setFeedbackMode(EctoMotorFeedback::QuadEncoder);
	
	/**
	 * Inverts
	 */
	frontRightSteer->invert(true);
	frontLeftSteer->invert(true);
	backRightSteer->invert(true);
	backLeftSteer->invert(true);
	
	frontRightWheel->invert(false);
	backRightWheel->invert(true);
	
	/**
	 * Ramp Rates
	 */
	const double wheelRampRate = 0.17;
	frontRightWheel->setOpenLoopRampRate(wheelRampRate);
	frontLeftWheel->setOpenLoopRampRate(wheelRampRate);
	backRightWheel->setOpenLoopRampRate(wheelRampRate);
	backLeftWheel->setOpenLoopRampRate(wheelRampRate);
	
	const double steerRampRate = .05;
	frontRightSteer->setOpenLoopRampRate(steerRampRate);
	frontLeftSteer->setOpenLoopRampRate(steerRampRate);
	backRightSteer->setOpenLoopRampRate(steerRampRate);
	backLeftSteer->setOpenLoopRampRate(steerRampRate);
	
	/**
	 * Brakes
	 */
	const bool wheelBrake = false;
	frontRightWheel->setBrakeOnIdle(wheelBrake);
	frontLeftWheel->setBrakeOnIdle(wheelBrake);
	backRightWheel->setBrakeOnIdle(wheelBrake);
	backLeftWheel->setBrakeOnIdle(wheelBrake);
	
	const bool steerBrake = true;
	frontRightSteer->setBrakeOnIdle(steerBrake);
	frontLeftSteer->setBrakeOnIdle(steerBrake);
	backLeftSteer->setBrakeOnIdle(steerBrake);
	backRightSteer->setBrakeOnIdle(steerBrake);
	
	/**
	 * Current limits
	 */
	const double wheelCurrentLimit = 35;
	frontRightWheel->setMotorCurrentLimit(wheelCurrentLimit);
	frontRightWheel->enableMotorCurrentLimit(true);
	
	frontLeftWheel->setMotorCurrentLimit(wheelCurrentLimit);
	frontLeftWheel->enableMotorCurrentLimit(true);
	
	backRightWheel->setMotorCurrentLimit(wheelCurrentLimit);
	backRightWheel->enableMotorCurrentLimit(true);
	
	backLeftWheel->setMotorCurrentLimit(wheelCurrentLimit);
	backLeftWheel->enableMotorCurrentLimit(true);
	
	const double steerCurrentLimit = 35;
	frontRightSteer->setMotorCurrentLimit(steerCurrentLimit);
	frontRightSteer->enableMotorCurrentLimit(true);
	
	frontLeftSteer->setMotorCurrentLimit(steerCurrentLimit);
	frontLeftSteer->enableMotorCurrentLimit(true);
	
	backRightSteer->setMotorCurrentLimit(steerCurrentLimit);
	backRightSteer->enableMotorCurrentLimit(true);
	
	backLeftSteer->setMotorCurrentLimit(steerCurrentLimit);
	backLeftSteer->enableMotorCurrentLimit(true);
	
	/**
	 * Analog position conversion factor
	 */
	frontRightSteer->setAnalogPositionConversionFactor(2 * M_PI / 3.335);
	frontLeftSteer->setAnalogPositionConversionFactor(2 * M_PI / 3.335);
	backRightSteer->setAnalogPositionConversionFactor(2 * M_PI / 3.335);
	backLeftSteer->setAnalogPositionConversionFactor(2 * M_PI / 3.335);
	
	/**
	 * Analog offsets
	 */
	frontLeftAnalogOffset = 3.623;
	frontRightAnalogOffset = 5.201;
	
	backLeftAnalogOffset = 2.885;
	backRightAnalogOffset = 0.923;
	
	frontLeftSteer->setAnalogOffset(frontLeftAnalogOffset);
	frontRightSteer->setAnalogOffset(frontRightAnalogOffset);
	
	backLeftSteer->setAnalogOffset(backLeftAnalogOffset);
	backRightSteer->setAnalogOffset(backRightAnalogOffset);
	
	/**
	 * Steer PID init
	 */
	steerPIDConfig.p = 0.16;
	steerPIDConfig.d = 0.000001;
	steerPIDConfig.minInput = -M_PI;
	steerPIDConfig.maxInput = M_PI;
	steerPIDConfig.continous = true;
	steerPIDConfig.deadband = 0.0;
	
	swervePIDSources.frontLeftSteer = frontLeftSteer;
	swervePIDSources.frontRightSteer = frontRightSteer;
	swervePIDSources.backLeftSteer = backLeftSteer;
	swervePIDSources.backRightSteer = backRightSteer;
	
	swervePIDOutputs.frontLeftSteer = frontLeftSteer;
	swervePIDOutputs.frontRightSteer = frontRightSteer;
	swervePIDOutputs.backLeftSteer = backLeftSteer;
	swervePIDOutputs.backRightSteer = backRightSteer;
	
	swervePidController = std::make_unique<SwervePIDController>(swervePIDSources, swervePIDOutputs, steerPIDConfig);
	swervePidController->start();
	
	zeroYaw();
	lastTimeUpdate = frc::Timer::GetFPGATimestamp();
}

void EctoSwerve::initNetworkTables() {
	frc::SmartDashboard::PutNumber("EctoSwerve/Heading/P", headingPIDConfig.p);
	frc::SmartDashboard::PutNumber("EctoSwerve/Heading/I", headingPIDConfig.i);
	frc::SmartDashboard::PutNumber("EctoSwerve/Heading/D", headingPIDConfig.d);
	
	frc::SmartDashboard::PutNumber("EctoSwerve/Steer/P", steerPIDConfig.p);
	frc::SmartDashboard::PutNumber("EctoSwerve/Steer/I", steerPIDConfig.i);
	frc::SmartDashboard::PutNumber("EctoSwerve/Steer/D", steerPIDConfig.d);
}

void EctoSwerve::updateNetworkTables() {
	frc::SmartDashboard::PutNumber("EctoSwerve/CurrentHeading", getYaw());

	PIDConfig newSteerConfig = steerPIDConfig;
	newSteerConfig.p = frc::SmartDashboard::GetNumber("EctoSwerve/Steer/P", steerPIDConfig.p);
	newSteerConfig.i = frc::SmartDashboard::GetNumber("EctoSwerve/Steer/I", steerPIDConfig.i);
	newSteerConfig.d = frc::SmartDashboard::GetNumber("EctoSwerve/Steer/D", steerPIDConfig.d);
	
	if (newSteerConfig != steerPIDConfig) {
		swervePidController->setConfig(newSteerConfig);
		steerPIDConfig = newSteerConfig;
	}
	
	PIDConfig newHeadingConfig = headingPIDConfig;
	newHeadingConfig.p = frc::SmartDashboard::GetNumber("EctoSwerve/Heading/P", headingPIDConfig.p);
	newHeadingConfig.i = frc::SmartDashboard::GetNumber("EctoSwerve/Heading/I", headingPIDConfig.i);
	newHeadingConfig.d = frc::SmartDashboard::GetNumber("EctoSwerve/Heading/D", headingPIDConfig.d);
	
	if (newHeadingConfig != headingPIDConfig) {
		targetHeadingController->setConfig(newHeadingConfig);
		headingPIDConfig = newHeadingConfig;
	}
}

void EctoSwerve::setTargetVelocity(const Twist2D &target, const Point2D &centerOfRotation,
                                   bool overrideControllers, bool transformToFieldOriented) {
	this->targetCenterOfRotation = centerOfRotation;
	
	if(transformToFieldOriented){
		this->setVelocityTarget = transformToFieldReference(target);
	} else {
		this->setVelocityTarget = target;
	}
	
	if(overrideControllers){
		movingToPosition = false;
		rotatingToAngle = false;
	}
}

void EctoSwerve::rotateToHeading(double target) {
	//TODO
}

void EctoSwerve::setTargetPosition(const RobotPose2D &targetPose) {
	//TODO
}

Twist2D EctoSwerve::transformToFieldReference(const Twist2D &target) const {
	const double yaw = getYaw();
	const double yawCos = std::cos(yaw);
	const double yawSin = std::sin(yaw);
	
	Twist2D output;
	
	const double temp = target.getDx() * yawCos + target.getDy() * yawSin;
	output.setDy(target.getDy() * yawCos - target.getDx() * yawSin);
	output.setDx(temp);
	
	return output;
}

SwerveMotorValues EctoSwerve::getCurrentMotorState() const {
	SwerveMotorValues values;
	
	values.topLeft.wheelVelocity = frontLeftWheel->getQuadVelocity();
	values.topLeft.wheelAngle = -frontLeftSteer->getPotPosition();
	values.topLeft.wheelAngularVelocity = -frontLeftSteer->getPotVelocity();
	
	values.topRight.wheelVelocity = frontRightWheel->getQuadVelocity();
	values.topRight.wheelAngle = -frontRightSteer->getPotPosition();
	values.topRight.wheelAngularVelocity = -frontRightSteer->getPotVelocity();
	
	values.backLeft.wheelVelocity = backLeftWheel->getQuadVelocity();
	values.backLeft.wheelAngle = -backLeftSteer->getPotPosition();
	values.backLeft.wheelAngularVelocity = -backLeftSteer->getPotVelocity();
	
	values.backRight.wheelVelocity = backRightWheel->getQuadVelocity();
	values.backRight.wheelAngle = -backRightSteer->getPotPosition();
	values.backRight.wheelAngularVelocity = -backRightSteer->getPotVelocity();
	return values;
}

bool EctoSwerve::checkIfTargetHeadingReached() const {
	//TODO
	return false;
}

bool EctoSwerve::checkIfTargetPositionReached() const {
	//TODO
	return false;
}

void EctoSwerve::writeMotors(const SwerveMotorValues &values) {
	frontLeftWheel->set(values.topLeft.wheelVelocity, EctoControlMode::Percent);
	frontRightWheel->set(values.topRight.wheelVelocity, EctoControlMode::Percent);
	backLeftWheel->set(values.backLeft.wheelVelocity, EctoControlMode::Percent);
	backRightWheel->set(values.backRight.wheelVelocity, EctoControlMode::Percent);

	swervePidController->set(values.topLeft.wheelAngle, values.topRight.wheelAngle, values.backLeft.wheelAngle,
	                         values.backRight.wheelAngle);
}

void EctoSwerve::initRobot() {
	initNetworkTables();
	inverseKinematicsThread = std::make_unique<std::thread>(std::bind(&EctoSwerve::updateInverseKinematics, this));
}

void EctoSwerve::updateRobot() {
	updateNetworkTables();
	
	/**
	 * Update controllers
	 */
	 
	if(movingToPosition){
		if(checkIfTargetPositionReached()){
			movingToPosition = false;
		} else {
			/**
			 * Move to position
			 */
			 //TODO (this)
		}
	} else if(rotatingToAngle){
		if(checkIfTargetHeadingReached()){
			rotatingToAngle = false;
		} else {
			/**
			 * Rotate to angle
			 */
			 //TODO (this)
		}
	} else {
		/**
		 * Use velocities
		 */
		inverseKinematicsTarget.lock();
		actualVelocityTarget = setVelocityTarget;
		centerOfRotation = targetCenterOfRotation;
		inverseKinematicsTarget.unlock();
	}
}

void EctoSwerve::zeroYaw() {
	/**
	 * NavX Reset
	 */
	headingZero = getYaw(false);
	targetHeading = 0;
}


float EctoSwerve::getYaw(bool useZero) const {
	float yaw = -ahrs.GetYaw();
	
	yaw *= M_PI / 180.0;
	
	if (useZero) {
		yaw -= headingZero;
	}
	
	yaw = EctoMath::wrapAngle(yaw);
	
	return yaw;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void EctoSwerve::updateInverseKinematics() {
	for (;;) {
		auto currentMotorStates = getCurrentMotorState();
		
		inverseKinematicsTarget.lock();
		
		Twist2D targetVelocity = actualVelocityTarget;
		Point2D setCenterOfRotation = centerOfRotation;
		
		inverseKinematicsTarget.unlock();
		
		SwerveMotorValues motorValues = kinematics->calculateInverseKinematics(targetVelocity, currentMotorStates, setCenterOfRotation);
		writeMotors(motorValues);
		
		frc::SmartDashboard::PutNumber("EctoSwerve/CenterOfRotation/X", setCenterOfRotation.getX());
		frc::SmartDashboard::PutNumber("EctoSwerve/CenterOfRotation/Y", setCenterOfRotation.getY());
		
		frc::SmartDashboard::PutNumber("EctoSwerve/CurrentTarget/Dx", targetVelocity.getDx());
		frc::SmartDashboard::PutNumber("EctoSwerve/CurrentTarget/Dy", targetVelocity.getDy());
		frc::SmartDashboard::PutNumber("EctoSwerve/CurrentTarget/Dtheta", targetVelocity.getDtheta());
		
		frc::SmartDashboard::PutNumber("EctoSwerve/WheelState/TopLeft/Angle", currentMotorStates.topLeft.wheelAngle);
		frc::SmartDashboard::PutNumber("EctoSwerve/WheelState/TopRight/Angle", currentMotorStates.topRight.wheelAngle);
		frc::SmartDashboard::PutNumber("EctoSwerve/WheelState/BackLeft/Angle", currentMotorStates.backLeft.wheelAngle);
		frc::SmartDashboard::PutNumber("EctoSwerve/WheelState/BackRight/Angle",
		                               currentMotorStates.backRight.wheelAngle);
		
		frc::SmartDashboard::PutNumber("EctoSwerve/SetValue/TopLeft/Angle", motorValues.topLeft.wheelAngle);
		frc::SmartDashboard::PutNumber("EctoSwerve/SetValue/TopRight/Angle", motorValues.topRight.wheelAngle);
		frc::SmartDashboard::PutNumber("EctoSwerve/SetValue/BackLeft/Angle", motorValues.backLeft.wheelAngle);
		frc::SmartDashboard::PutNumber("EctoSwerve/SetValue/BackRight/Angle", motorValues.backRight.wheelAngle);
		
		frc::SmartDashboard::PutNumber("EctoSwerve/SetValue/TopLeft/Velocity", motorValues.topLeft.wheelVelocity);
		frc::SmartDashboard::PutNumber("EctoSwerve/SetValue/TopRight/Velocity", motorValues.topRight.wheelVelocity);
		frc::SmartDashboard::PutNumber("EctoSwerve/SetValue/BackLeft/Velocity", motorValues.backLeft.wheelVelocity);
		frc::SmartDashboard::PutNumber("EctoSwerve/SetValue/BackRight/Velocity",
		                               motorValues.backRight.wheelVelocity);
		
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}
#pragma clang diagnostic pop