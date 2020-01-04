//
// Created by abiel on 10/13/19.
//

#include "TimingDataPublisher.h"
#include "frc/smartdashboard/SmartDashboard.h"

TimingDataPublisher::TimingDataPublisher(std::shared_ptr<SystemHandler> handler, const std::string &dataPublisherName) : System(dataPublisherName) {
	this->handler = handler;
}

void TimingDataPublisher::updateRobot() {
	for(const auto data : handler->getTimingData()){
		const std::string systemName = data.first;
		frc::SmartDashboard::PutNumber(fmt::format("{}/{}/UpdateRobot", "TimingData", systemName), boost::accumulators::rolling_mean(data.second.updateRobotTime));
		frc::SmartDashboard::PutNumber(fmt::format("{}/{}/UpdateDisabled", "TimingData", systemName), boost::accumulators::rolling_mean(data.second.updateDisabledTime));
	}
}