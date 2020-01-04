//
// Created by hiram on 28/06/19.
//

#ifndef BOTBUSTERS_REBIRTH_SYSTEM_H
#define BOTBUSTERS_REBIRTH_SYSTEM_H


#include <vector>
#include <memory>
#include "EctoSettings/EctoSettings.h"
#include "Module.h"


class System : public Module {
public:
    System(const std::string & name);

    virtual void initRobot();

    virtual void updateRobot();

    virtual void initTeleop();

    virtual void updateTeleop();

    virtual void initAuto();

    virtual void updateAuto();

    virtual void initDisabled();

    virtual void updateDisabled();

    virtual void initTest();

    virtual void updateTest();

};


#endif //BOTBUSTERS_REBIRTH_SYSTEM_H
