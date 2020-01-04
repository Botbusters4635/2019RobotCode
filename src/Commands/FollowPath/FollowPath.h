//
// Created by alberto on 03/01/20.
//

#ifndef BOTBUSTERS_REBIRTH_FOLLOWPATH_H
#define BOTBUSTERS_REBIRTH_FOLLOWPATH_H

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>
#include <EctoControl/Path/Path.h>
#include "Systems/EctoSwerve/EctoSwerve.h"

class FollowPath : public frc2::CommandHelper<frc2::CommandBase, FollowPath>{
public:
	FollowPath(std::shared_ptr<EctoSwerve>& swerve, Path path);
	
	void Initialize() override;
	
	void Execute() override;
	
	void End(bool interrupted) override;
	
	bool IsFinished() override;
	
private:
	std::shared_ptr<EctoSwerve> & swerve;
	Path path;
};


#endif //BOTBUSTERS_REBIRTH_FOLLOWPATH_H
