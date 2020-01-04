//
// Created by hiram on 3/07/19.
//
#include "EctoModule/Module.h"

std::string Module::configRootDir = "";


Module::Module(const std::string& name) : name(name){
    settings = std::make_unique<EctoSettings>(configRootDir + name + ".ini");
    log = spdlog::stdout_color_mt(name);
    log->info("Starting...");
}

std::string Module::getName() {
    return name;
}

void Module::setConfigFileRootDir(const std::string &configRootDir){
    Module::configRootDir = configRootDir;
}