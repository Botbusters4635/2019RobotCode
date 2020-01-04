//
// Created by abiel on 8/22/19.
//

#ifndef BOTBUSTERSREBIRTH_ECTOPCM_H
#define BOTBUSTERSREBIRTH_ECTOPCM_H

#include <frc/Solenoid.h>
#include <EctoModule/Manager.h>

#include <string>

struct EctoPiston {
	bool isSingleSolenoid = false;
	
	std::shared_ptr<frc::Solenoid> aSolenoid;
	std::shared_ptr<frc::Solenoid> bSolenoid;
	
	bool currentState = false;
};

class EctoPCM : public Manager<EctoPCM> {
	friend class Manager<EctoPCM>;

public:
	EctoPiston &getPiston(const std::string &pistonName);
	
	static void setPiston(EctoPiston &piston, bool state);
	
	void setPiston(const std::string &pistonName, bool state);
	
	void togglePiston(const std::string &pistonName);

protected:
	void update() override;

private:
	EctoPCM();
	
	EctoPCM &operator=(const EctoPCM &);
	
	void initializePistons();
	
	std::map<std::string, std::string> pistonsConfig;
	std::map<std::string, EctoPiston> pistons;
	
	const std::string baseNamePison = "Piston";
};

namespace EctoPCMPropertyDict {
	const std::string name = "name";
	const std::string id = "id";
}

#endif //BOTBUSTERSREBIRTH_ECTOPCM_H
