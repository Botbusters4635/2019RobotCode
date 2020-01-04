#include <iostream>
#include "EctoInput.h"
//TODO Re-implement input checking???

EctoInput::EctoInput() : Manager("EctoInput") {
	log->info("Initializing EctoInput...");
	
	joystickCount = settings->getNumber("Input", "StickCount");
	
	initializeJoysticks();
	initializeAxis();
	initializeButtons();
}

void EctoInput::update() {
	driverStation.WaitForData(0);
	
	for (const auto &joystick : joysticks) {
		const JoystickData &joyData = joystick.second;
		
		for (const auto &buttonData : joyData.buttonsToUpdate) {
			
			bool buttonState = getButtonState(buttonData.first, joystick.first);
			
			for (auto &button : buttonData.second) {
				button->updateStatus(buttonState);
			}
		}
		
		for (const auto &axisData : joyData.axesToUpdate) {
			
			double axisValue = getJoystickRaw((unsigned int) axisData.first, joystick.first);
			
			for (const auto &axis : axisData.second) {
				
				axis->updateValue(axisValue);
				
			}
		}
	}
}

void EctoInput::addButton(EctoButton *button, const std::string &buttonName, int joystickId) {
	std::lock_guard<std::mutex> lock(ectoInputMutex);
	
	if (joysticks.count(joystickId) == 0) {
		throw std::runtime_error("Joystick ID " + std::to_string(joystickId) + " not found in EctoInput config");
	}
	JoystickData &data = joysticks.at(joystickId);
	
	if (data.buttonNames.count(buttonName) == 0) {
		throw std::runtime_error(
				"Joystick ID " + std::to_string(joystickId) + " does not have a button named " + buttonName +
				" in EctoInput config");
	}
	
	int buttonId = data.buttonNames.at(buttonName);
	
	data.buttonsToUpdate[buttonId].emplace_back(button);
}

void EctoInput::addAxis(JoystickAxis *axis, const std::string &axisName, int joystickId) {
	std::lock_guard<std::mutex> lock(ectoInputMutex);
	
	if (joysticks.count(joystickId) == 0) {
		throw std::runtime_error("Joystick ID " + std::to_string(joystickId) + " not found in EctoInput config");
	}
	JoystickData &data = joysticks.at(joystickId);
	
	if (data.axesNames.count(axisName) == 0) {
		throw std::runtime_error(
				"Joystick ID " + std::to_string(joystickId) + " does not have a axis named" + axisName +
				"inEctoInput config");
	}
	
	int axisId = data.axesNames.at(axisName);
	
	data.axesToUpdate[axisId].emplace_back(axis);
}

void EctoInput::setRumbleMotor(double leftSetpoint, double rightSetpoint, int joystickId){
	joysticks.at(joystickId).joystick->SetRumble(frc::GenericHID::kLeftRumble, leftSetpoint);
	joysticks.at(joystickId).joystick->SetRumble(frc::GenericHID::kRightRumble, rightSetpoint);
}

void EctoInput::initializeJoysticks() {
	std::lock_guard<std::mutex> lock(ectoInputMutex);
	
	log->info("Initializing Sticks...");
	for (int i = 1; i <= joystickCount; ++i) {
		auto stickId = settings->getNumber("Input", baseNameStick + std::to_string(i));
		
		JoystickData joystickData;
		
		joystickData.joystickId = i;
		joystickData.wpiJoystickId = (int) stickId;
		
		joystickData.joystick = std::make_unique<frc::Joystick>((int) stickId);

#ifndef SIMULATION
		//ROBORIO
		
		while (joystickData.joystick->GetAxisCount() == 0) {
			log->error("Waiting for joystick {}!", stickId);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		
		joystickData.axisCount = joystickData.joystick->GetAxisCount();
		joystickData.buttonCount = joystickData.joystick->GetButtonCount();
		
#else //PC
		joystickData.axisCount = 6;
		joystickData.buttonCount = 10;
#endif
		
		joysticks.emplace(i, joystickData);
	}
}

void EctoInput::initializeAxis() {
	std::lock_guard<std::mutex> lock(ectoInputMutex);
	
	for (std::pair<const int, JoystickData> &data : joysticks) {
		JoystickData &joyData = data.second;
		
		for (int i = 1; i <= joyData.axisCount; ++i) {
			std::string axisName = settings->getString("Input",
			                                           baseNameStickSelector + std::to_string(data.first) + "." +
			                                           baseNameAxis + std::to_string(i));
			
			joyData.axesNames.emplace(std::make_pair(axisName, i));
		}
	}
}

void EctoInput::initializeButtons() {
	std::lock_guard<std::mutex> lock(ectoInputMutex);
	
	for (std::pair<const int, JoystickData> &data : joysticks) {
		JoystickData &joyData = data.second;
		
		for (int i = 1; i <= joyData.buttonCount; ++i) {
			std::string buttonName = settings->getString("Input",
			                                             baseNameStickSelector + std::to_string(data.first) + "." +
			                                             baseNameButton + std::to_string(i));
			
			joyData.buttonNames.emplace(std::make_pair(buttonName, i));
		}
	}
}

/**
 * Returns button state
 * @param  id Button ID
 * @return
 */
bool EctoInput::getButtonState(int id, int joyId) const {
	return joysticks.at(joyId).joystick->GetRawButton(id);
}


/**
 * Returns joystick raw value
 * @param  joystickId Axis ID
 * @return
 */
double EctoInput::getJoystickRaw(int joystickId, int joyId) const {
	return joysticks.at(joyId).joystick->GetRawAxis(joystickId - 1);
}

int EctoInput::getPOV(int joystickId) const {
	return joysticks.at(joystickId).joystick->GetPOV();
}
