//
// Created by hiram on 29/06/19.
//

#ifndef BOTBUSTERS_REBIRTH_SLIMERINSPACE_H
#define BOTBUSTERS_REBIRTH_SLIMERINSPACE_H

#include "Core/EctoRobot.h"
#include "Systems/EctoSwerve/EctoSwerve.h"
#include "Systems/EctoSwerve/EctoSwerveInputHandler.h"
#include "Systems/PuppetMeister/PuppetMeister.h"
#include "Systems/TimingDataPublisher/TimingDataPublisher.h"

class SlimerInSpace : public EctoRobot {
public:
	SlimerInSpace();

private:
	std::shared_ptr<PuppetMeister> meister;
	std::shared_ptr<EctoSwerve> swerve;
	std::shared_ptr<EctoSwerveInputHandler> swerveInputHandler;
	
	std::shared_ptr<TimingDataPublisher> timingDataPublisher;
};


#endif //BOTBUSTERS_REBIRTH_SLIMERINSPACE_H
