//
// Created by hiram on 9/19/19.
// Thank alberto for the name
//

#ifndef BOTBUSTERS_REBIRTH_ECTOPOT_H
#define BOTBUSTERS_REBIRTH_ECTOPOT_H


#include <frc/PIDSource.h>
#include <frc/AnalogInput.h>
#include <EctoControl/EctoControllerSource.h>
#include <frc/Timer.h>

class EctoPot : public frc::PIDSource, public EctoControllerSource {
public:
	explicit EctoPot(int port, double range, double lowerVoltageLimit, double upperVoltageLimit, double offset);
	
	double getPosition() const override;
	
	double getVelocity() const override;
	
	double getVoltage();
	
	double PIDGet() override;

private:
	std::unique_ptr<frc::AnalogInput> input;
	double range;
	double upperVoltageLimit;
	double offset;
	double lowerVoltageLimit;
	
	mutable double lastPosition = 0;
	mutable double lastPositionTime = 0;
};


#endif //BOTBUSTERS_REBIRTH_ECTOPOT_H
