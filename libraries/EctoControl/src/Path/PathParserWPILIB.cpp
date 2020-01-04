//
// Created by abiel on 1/2/20.
//

//Parses wpilib paths from PathParser (2020)

#include "EctoControl/Path/PathParserWPILIB.h"
#include <json/json.hpp>
#include <iostream>
#include <fstream>

Path PathParserWPILIB::loadPath(const std::string &filePath){
    std::ifstream file(filePath);

    if(!file.good()){
        throw std::runtime_error("Invalid file!");
    }

    std::vector<RobotPose2D> poses;

    json j;
    file >> j;
    file.close();

    for(const auto& element : j){
        const double x = element["pose"]["translation"]["x"];
        const double y = element["pose"]["translation"]["y"];
        const double radians = element["pose"]["rotation"]["radians"];
        const Rotation2D rot(radians);

        poses.emplace_back(RobotPose2D{x, y, rot});
    }

    return Path(poses);
}