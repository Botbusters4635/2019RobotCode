//
// Created by hiram on 28/06/19.
//

#ifndef  BOTBUSTERS_REBIRTH_ECTOROBOT_H
#define BOTBUSTERS_REBIRTH_ECTOROBOT_H

#include <frc/TimedRobot.h>
#include <map>
#include <EctoModule/System.h>
#include <EctoModule/SystemHandler.h>
#include <spdlog/spdlog.h>
#include "Core/MotorHandler/MotorHandler.h"

class EctoRobot : public frc::TimedRobot, public System {
public:
	explicit EctoRobot(const std::string &robotName);
	
	std::shared_ptr<SystemHandler> systemManager;
	std::shared_ptr<SystemHandler> inputHandlers;
	
	static constexpr bool updateInputsInAuto = true;
	
	MotorHandler &motorHandler = MotorHandler::getInstance();

private:
	void RobotInit() final;
	
	void RobotPeriodic() final;
	
	void TestInit() final;
	
	void TestPeriodic() final;
	
	void DisabledInit() final;
	
	void DisabledPeriodic() final;
	
	void TeleopInit() final;
	
	void TeleopPeriodic() final;
	
	void AutonomousInit() final;
	
	void AutonomousPeriodic() final;
	
};


#endif //BOTBUSTERS_REBIRTH_ECTOROBOT_H
