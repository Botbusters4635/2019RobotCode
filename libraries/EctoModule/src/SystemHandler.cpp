//
// Created by alberto on 7/07/19.
//

#include "EctoModule/SystemHandler.h"

SystemHandler::SystemHandler(const std::string &name) : System(name){

}

bool SystemHandler::addSubsystem(System &newSystem) {
    return addSubsystem(std::shared_ptr<System>(&newSystem));
}

bool SystemHandler::addSubsystem(const std::shared_ptr<System> &newSystem) {

    if(!newSystem){
        throw std::runtime_error("Null pointer given");
    }

    //Find subsystem in vector
    auto it = find_if(systems.begin(), systems.end(), [&newSystem](const SystemData& obj) {return obj.subsystem == newSystem;});
    if(it != systems.end()){
        log ->error("Error while adding subcomponent {} to {}, already a subcomponent", newSystem->getName(), getName());
        return false;
    }

    SystemData data;
    data.subsystem = newSystem;

    systems.emplace_back(data);
    return true;
}

void SystemHandler::initRobot() {
    for (auto &systemData : systems) {
        auto startTime = std::chrono::high_resolution_clock::now();
        systemData.subsystem->initRobot();
        double elapsedTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();

        systemData.timingData.initRobotTime = elapsedTime;
    }
}

void SystemHandler::updateRobot() {
    for (auto &systemData : systems) {
        auto startTime = std::chrono::high_resolution_clock::now();

        systemData.subsystem->updateRobot();
        double elapsedTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();

        systemData.timingData.updateRobotTime(elapsedTime);
    }
}

void SystemHandler::initDisabled() {
    for (auto &systemData : systems) {
        auto startTime = std::chrono::high_resolution_clock::now();

        systemData.subsystem->initDisabled();
        double elapsedTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();

        systemData.timingData.initDisabledTime = elapsedTime;
    }
}

void SystemHandler::updateDisabled() {
    for (auto &systemData : systems) {
        auto startTime = std::chrono::high_resolution_clock::now();

        systemData.subsystem->updateDisabled();
        double elapsedTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();

        systemData.timingData.updateDisabledTime(elapsedTime);
    }
}

void SystemHandler::initTeleop() {
    for (auto &systemData : systems) {
        auto startTime = std::chrono::high_resolution_clock::now();

        systemData.subsystem->initTeleop();
        double elapsedTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();

        systemData.timingData.initTeleopTime = elapsedTime;
    }
}

void SystemHandler::updateTeleop() {
    for (auto &systemData : systems) {
        auto startTime = std::chrono::high_resolution_clock::now();

        systemData.subsystem->updateTeleop();
        double elapsedTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();

        systemData.timingData.updateTeleopTime(elapsedTime);
    }
}

void SystemHandler::initAuto() {
    for (auto &systemData : systems) {
        auto startTime = std::chrono::high_resolution_clock::now();

        systemData.subsystem->initAuto();
        double elapsedTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();

        systemData.timingData.initAutoTime = elapsedTime;
    }
}

void SystemHandler::updateAuto() {
    for (auto &systemData : systems) {
        auto startTime = std::chrono::high_resolution_clock::now();

        systemData.subsystem->updateAuto();
        double elapsedTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();

        systemData.timingData.updateAutoTime(elapsedTime);
    }
}

void SystemHandler::initTest() {
    for (auto &systemData : systems) {
        auto startTime = std::chrono::high_resolution_clock::now();

        systemData.subsystem->initTest();
        double elapsedTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();

        systemData.timingData.initTestTime = elapsedTime;
    }
}

void SystemHandler::updateTest() {
    for (auto &systemData : systems) {
        auto startTime = std::chrono::high_resolution_clock::now();

        systemData.subsystem->updateTest();
        double elapsedTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();

        systemData.timingData.updateTestTime(elapsedTime);
    }
}

std::vector<std::pair<std::string, TimingData>> SystemHandler::getTimingData() const {
    std::vector<std::pair<std::string, TimingData>> output;

    for(auto &systemData : systems){
        output.emplace_back(std::make_pair(systemData.subsystem->getName(), systemData.timingData));
    }

    return output;
}