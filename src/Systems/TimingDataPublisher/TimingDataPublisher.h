//
// Created by abiel on 10/13/19.
//

#ifndef BOTBUSTERSREBIRTH_TIMINGDATAPUBLISHER_H
#define BOTBUSTERSREBIRTH_TIMINGDATAPUBLISHER_H

#include <EctoModule/System.h>
#include <EctoModule/SystemHandler.h>

//TODO Publish init times
class TimingDataPublisher : public System {
public:
	TimingDataPublisher(std::shared_ptr<SystemHandler> handler, const std::string &dataPublisherName = "TimingDataPublisher");
	
	void updateRobot() override;
private:
	std::shared_ptr<SystemHandler> handler;
};


#endif //BOTBUSTERSREBIRTH_TIMINGDATAPUBLISHER_H
