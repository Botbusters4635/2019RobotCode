/*
* Settings
* Group: Input
* StickPort: Stick Port (probably 0)
* Deadzone: Deadzone for Joystick
* ButtonName# - ButtonName#: Button Name
* AxisName# - AxisName#: Axis Name
*/

#ifndef BOTBUSTERSREBIRTH_ECTOINPUT_H
#define BOTBUSTERSREBIRTH_ECTOINPUT_H

#include <InputHandlers/EctoButton.h>
#include <InputHandlers/JoystickAxis.h>
#include <EctoModule/Manager.h>
#include <frc/DriverStation.h>
#include <frc/Joystick.h>
#include <map>
#include <utility>
#include <string>
#include <mutex>
#include <thread>
#include <chrono>

/**
 * Class responsible for handling all inputs.
 * @return
 */
class EctoInput : public Manager<EctoInput> {
	friend class Manager<EctoInput>;

public:
	void addButton(EctoButton *button, const std::string &buttonName, int joystickId = 1);
	
	void addAxis(JoystickAxis *axis, const std::string &axisName, int joystickId = 1);
	
	void setRumbleMotor(double leftSetpoint, double rightSetpoint, int joystickId = 1);
	
	int getPOV(int joystickId = 1) const;

protected:
	void update() override;

private:
	struct JoystickData {
		std::shared_ptr<frc::Joystick> joystick;
		
		int joystickId;
		int wpiJoystickId;
		
		int axisCount;
		int buttonCount;
		
		//Stores names to ids
		std::map<std::string, int> buttonNames;
		std::map<std::string, int> axesNames;
		
		std::map<int, std::vector<std::shared_ptr<EctoButton>>> buttonsToUpdate;
		std::map<int, std::vector<std::shared_ptr<JoystickAxis>>> axesToUpdate;
	};
	
	bool getButtonState(int id, int joyId = 1) const;
	
	double getJoystickRaw(int joystickId, int joyId = 1) const;
	
	EctoInput();
	
	EctoInput &operator=(const EctoInput &);
	
	void initializeJoysticks();
	
	void initializeButtons();
	
	void initializeAxis();
	
	const std::string baseNameStick = "StickPort";
	const std::string baseNameStickSelector = "Stick";
	const std::string baseNameAxis = "AxisName";
	const std::string baseNameButton = "ButtonName";
	
	int joystickCount;
	
	std::map<int, JoystickData> joysticks;
	
	mutable std::mutex ectoInputMutex;
	frc::DriverStation &driverStation = frc::DriverStation::GetInstance();
};

#endif
