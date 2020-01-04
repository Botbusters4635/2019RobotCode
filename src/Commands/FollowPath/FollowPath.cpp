//
// Created by alberto on 03/01/20.
//

#include "FollowPath.h"
#include <utility>

FollowPath::FollowPath(std::shared_ptr<EctoSwerve> &swerve, Path  path) : swerve(swerve), path(std::move(path)){

}

void FollowPath::Initialize() {
}

void FollowPath::Execute() {
}

void FollowPath::End(bool interrupted) {
}

bool FollowPath::IsFinished() {
	return false;
}


