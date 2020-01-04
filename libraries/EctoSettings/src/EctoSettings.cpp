#include "EctoSettings/EctoSettings.h"

EctoSettings::EctoSettings(const std::string &filePath) : 
    iniFile(filePath) {

    // Initialize a logger for this instance.
    log = spdlog::stdout_color_mt("EctoSettings/" + filePath);
    int res = iniFile.read(iniData);
    if(res == 0){
        log->error("The configuration file " + filePath + " was not found.");
        throw std::runtime_error("The configuration file " + filePath + " was not found.");
    }
    log->trace("{} initialized...", filePath);
}

// Refresh the data from the ini file, in case of any changes.
void EctoSettings::refreshFile() {
    log->trace("Refreshing...");  
    iniFile.read(iniData);
    log->trace("Done");  
}

std::string EctoSettings::getString(const std::string &group, const std::string &property) {
    std::unique_lock<std::mutex> lck(mtx);
    log->trace("Getting {} from {}...", property, group);

    std::string valueStr;
    if (propertyExists(group, property)) {
        valueStr = iniData[group][property];
    } else {
        log->critical("Property " + property + " of group " + group + " not found.");
        throw std::runtime_error("Property " + property + " of group " + group + " not found.");
    }
    log->trace("Read {}", valueStr);
    return valueStr;
}

// Get a bool valuue from the ini data map.
bool EctoSettings::getBool(const std::string &group, const std::string &property) {
    std::unique_lock<std::mutex> lck(mtx);
    log->trace("Getting {} from {}...", property, group);

    bool valueBool;
    // Check if group and property exist, if not stop execution.
    if (propertyExists(group, property)) {
        std::string boolString = iniData[group][property];
        if (boolString == "true") {
            valueBool = true;
        } else if (boolString == "false") {
            valueBool = false;
        } else {
            log->critical(
                    "Property " + property + " of group " + group + " is invalid, it must be either true or false");
            throw std::runtime_error("Property " + property + " of group " + group + " is invalid, it must be either true or false");
        }
    } else {
        log->critical("Property " + property + " of group " + group + " not found.");
        throw std::runtime_error("Property " + property + " of group " + group + " not found.");
    }
    log->trace("Read {}", valueBool);
    return valueBool;
}

double EctoSettings::getNumber(const std::string &group, const std::string &property) {
    std::unique_lock<std::mutex> lck(mtx);
    log->trace("Getting {} from {}...", property, group);
    double number;
    if (propertyExists(group, property)) {
        try {
            number = stod(iniData[group][property]);
        } catch (const std::invalid_argument &ia) {
            log->critical("Property " + property + " of group " + group + " is not a number");
            throw std::runtime_error("Property " + property + " of group " + group + " is not a number");
        }

    } else {
        log->critical("Property " + property + " of group " + group + " not found.");
        throw std::runtime_error("Property " + property + " of group " + group + " not found.");
    }
    log->trace("Read {}", number);
    return number;
}

std::map<std::string, std::string> EctoSettings::getAllOfGroup(const std::string &group){
    std::map<std::string, std::string> result;
    bool foundSection = false;

    for (auto const& it : iniData){
        auto const& section = it.first;
        log->trace("{}", section);
        if(std::equal(section.begin(), section.end(), group.begin(), group.end(),
                [] (const char& a, const char& b){
            return (std::tolower(a) == std::tolower(b));
        })){
            foundSection = true;
            for (auto const& variable : it.second){
                auto const& key = variable.first;
                auto const& value = variable.second;
                log->trace("Key: {}", key);
                log->trace("Value: {}", value);
                result.emplace(std::make_pair(key, value));
            }
            break;
        }
    }

    if(!foundSection){
        throw std::runtime_error("Could not find group " + group + " failed to retrieve all of its elements.");
    }
    return result;
}

bool EctoSettings::propertyExists(const std::string &group, const std::string &property) {
    return iniData.has(group) && iniData[group].has(property);
}

EctoSettings::~EctoSettings() {
    if(log){
    	log->trace("Deletting {}", log->name());
	    spdlog::drop(log->name());
    }
}

