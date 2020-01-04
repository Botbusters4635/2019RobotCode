//
// Created by abiel on 12/25/19.
//

#ifndef ECTOCONTROL_PATHPARSERWPILIB_H
#define ECTOCONTROL_PATHPARSERWPILIB_H

#include "EctoControl/Path/Path.h"

class PathParserWPILIB {
public:
    static Path loadPath(const std::string &filePath);
};


#endif //ECTOCONTROL_PATHPARSERWPILIB_H
