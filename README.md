# Botbusters 2019 Robot Code
## Features
* Modular
	* Most of the code is broken down into libraries which can be utilized in other projects or in other simulations of the robot.
	* This allows us to test our libraries in a simulated, controlled enviorment.
* Unit tests
	* Some of the main robot code is unit tested in order to ensure the code works before it is deployed.
	* Most of the library code is unit tested.
* Simulation Support
	* When ran on a PC, information about the commands sent to the motor controllers are sent over NT.
* `Command-based` autonomous; `TimedRobot` teleoperated
* Systems
	* EctoSwerve
		* Supports field-oriented drive.
	* EctoMotor
		* Implements a common api for both `Talon SRX` and `Spark MAX`, this way, a single api can be used for both motor controllers.
	* EctoSettings
		* Commonly modified parameters are stored in an `.ini` file so they can be modified without re-compiling the robot code.
	* EctoInput
		* Inputs are handled in a separate thread.
	* Generic base mechanism classes for common mechanisms.
		* Base elevator class
		* Base articulated class
* Multi-threaded
	* Some tasks run in separate threads in order to have a _faster_ loop time.
* Libraries
	* EctoControl
		* EctoPID: Custom PID implementation
		* EctoSMC
		* MotionProfiles: Trapezoidal motion profiles
		* Kinematics
			* Swerve Inverse / Forward Kinematics
			* Tank Inverse / Forward Kinematics
		* Odometry
			* Non-linear odometry
			* Linear odometry
		* Paths
			* Pure pursuit path planner for holonomic drivetrains
			* Support for parsing PathWeaver paths
	* EctoMath
		* Data types and other math-related functions.
		* Also defines functions for creating quintic spline paths.
	* EctoModule
		* Defines the `Module` structure used in our robot code.
		* Module: base class, gives each module it's own config file and logger.
			* Manager: defines a singleton module which can be used to manage devices in the robot code.
			* System: defines the base class used for most mechanisims, contains an update loop which is
			ran periodically when the robot is enabled and an init function which runs once.
			* SystemManager: Runs systems. Also times each system in order to identify if a system is running slower than it should be.
	* EctoSettings	
		* Parses `.ini` files
	
