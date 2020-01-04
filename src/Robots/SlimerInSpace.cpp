//
// Created by hiram on 29/06/19.
//


#include "SlimerInSpace.h"
#include <frc2/command/SequentialCommandGroup.h>
#include "Commands/FollowPath/FollowPath.h"

SlimerInSpace::SlimerInSpace() : EctoRobot("SlimerInSpace") {
	PuppetMeisterConfig meisterConfig;
	
	meisterConfig.elevatorConfig.gearReduction = (84.0 / 11.0);
	meisterConfig.elevatorConfig.winchDiameter = (0.047752);
	
	meisterConfig.elevatorConfig.enableForwardSoftLimt = true;
	meisterConfig.elevatorConfig.forwardHeightLimit = 1.0;
	
	meisterConfig.elevatorConfig.reverseHeightLimit = -.02;
	meisterConfig.elevatorConfig.enableReverseSoftLimit = true;
	
	meisterConfig.elevatorConfig.voltageTestMode = false;
	
	meisterConfig.elevatorConfig.maximumVelocity = 1.9;
	meisterConfig.elevatorConfig.maximumAcceleration = 0.10066;
	//meisterConfig.elevatorConfig.maximumVelocity = 0.6668;
	//meisterConfig.elevatorConfig.maximumAcceleration = 0.108;
	meisterConfig.elevatorConfig.useMagicMotion = true;
	
	EctoSwerveConfig swerveConfig;
	
	meister = std::make_shared<PuppetMeister>(meisterConfig);
	swerve = std::make_shared<EctoSwerve>(swerveConfig);
	swerveInputHandler = std::make_shared<EctoSwerveInputHandler>(*(swerve.get()));
	timingDataPublisher = std::make_shared<TimingDataPublisher>(systemManager);
	
	systemManager->addSubsystem(meister);
	
	systemManager->addSubsystem(swerve);
	systemManager->addSubsystem(swerveInputHandler);
	
	systemManager->addSubsystem(timingDataPublisher);
	
	auto visionTable = nt::NetworkTableInstance::GetDefault().GetTable("/CameraPublisher/HatchCamera");
	std::string visionKey = {"mjpeg:http://10.46.35.12:5800/?action=stream"};
	visionTable->PutStringArray("streams", visionKey);
	
	
	frc2::SequentialCommandGroup testAuto{
		FollowPath(swerve, Path ({
			RobotPose2D(0,0,0),
			RobotPose2D(3,0,0),
			RobotPose2D(3,3,0)
		})),
		FollowPath(swerve, Path ({
			RobotPose2D(3,3,0),
            RobotPose2D(3,0,0),
            RobotPose2D(0,0,0)
         }))
	};
	
}
