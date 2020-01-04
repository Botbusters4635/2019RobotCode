#ifndef BOTBUSTERSREBIRTH_ECTOSETTINGS_H
#define BOTBUSTERSREBIRTH_ECTOSETTINGS_H

#include "EctoSettings/mini/ini.h"
#include <mutex>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <map>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


/* Used to read config files defined in the project.
 * This is a thread safe class, it can be used among several threads without issue.
 */

class EctoSettings {
public:
    explicit EctoSettings(const std::string &filePath);

    /* getString() is used to get a property from the module's file.
     * It retrieves the text of the property. */
    std::string getString(const std::string &group, const std::string &property);

    /* getBool() is used to obbtain a boolean value from the module's file.
     * If the property has an invalid value, it stops execution and shows a warning. */
    bool getBool(const std::string &group, const std::string &property);

    /* getDouble() obtains the numerical value from the module's file, if it
     * is not a number it stops execution and shows a warning. */
    double getNumber(const std::string &group, const std::string &property);

    std::map<std::string, std::string> getAllOfGroup(const std::string &group);

    void refreshFile();
    ~EctoSettings();
private:

    bool propertyExists(const std::string &group, const std::string &property);

    std::shared_ptr<spdlog::logger> log;

    mINI::INIFile iniFile;
    mINI::INIStructure iniData;


    std::mutex mtx;
};

#endif
