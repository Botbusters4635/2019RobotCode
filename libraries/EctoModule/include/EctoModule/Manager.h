//
// Created by hiram on 28/06/19.
//

#ifndef BOTBUSTERS_REBIRTH_MANAGER_H
#define BOTBUSTERS_REBIRTH_MANAGER_H


#include "Module.h"
#include <EctoUtilities/EctoWatchdog.h>

// Manager is a singleton superclass inheriting from Module.
// In order to inherit from it the subclass must declare itself as inheriting from
// Manager<subclass>, mark Manager<subclass> as a friend class, and finally make constructor private.
// Example:
// class EctoInput: public Manager<EctoInput>{
//      friend class Manager<EctoInput>;
// private:
//      EctoInput(){};
// public::
//      getAxis();
// }

template<typename T>
class Manager : public Module {
public:
    static T &getInstance() {
        static T instance;
        if(!instance.startedWatchdog){
            instance.watchdog->start();
            instance.startedWatchdog = true;
        }
        return instance;
    }

    Manager(Manager const &) = delete;

    Manager &operator=(Manager const &) = delete;

protected:
    explicit Manager(const std::string &name) : Module(name) {
            watchdog = new EctoWatchdog(name, std::chrono::milliseconds(2000), std::chrono::milliseconds(20),
                                std::bind(&Manager::update, this));
    };
    virtual void update() = 0;

    ~Manager() {};

    EctoWatchdog *watchdog;
    bool startedWatchdog = false;

};


#endif //BOTBUSTERS_REBIRTH_MANAGER_H
