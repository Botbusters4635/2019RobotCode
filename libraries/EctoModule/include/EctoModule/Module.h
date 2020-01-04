//
// Created by hiram on 3/07/19.
//

#ifndef BOTBUSTERS_REBIRTH_MODULE_H
#define BOTBUSTERS_REBIRTH_MODULE_H

#include <EctoSettings/EctoSettings.h>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// Base class for all subsystems.

class Module {
public:
    Module(const std::string &name);
    std::string getName();

    static void setConfigFileRootDir(const std::string &configRootDir);
protected:
    std::unique_ptr<EctoSettings> settings;

    std::shared_ptr<spdlog::logger> log;

private:
    std::string name;
    static std::string configRootDir;

};


#endif //BOTBUSTERS_REBIRTH_MODULE_H
