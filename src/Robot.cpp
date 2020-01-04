#include <frc/WPILib.h>
#include "Robots/SlimerInSpace.h"

/**
 * Botbusters_Rebirth 2019
 *
 * Created by:
 * Abiel Fernandez
 * Hiram Muñoz
 * Alberto Jahuey
 * Karen Rodriguez
 *
 *                     __---__
 *                  _-       _--______
 *             __--( /     \ )XXXXXXXXXXXXX_
 *           --XXX(   O   O  )XXXXXXXXXXXXXXX-
 *          /XXX(       U     )        XXXXXXX\
 *        /XXXXX(              )--_  XXXXXXXXXXX\
 *       /XXXXX/ (      O     )   XXXXXX   \XXXXX\
 *       XXXXX/   /            XXXXXX   \__ \XXXXX----
 *       XXXXXX__/          XXXXXX         \__----  -
-*--___  XXX__/          XXXXXX      \__         ---
 * --  --__/   ___/\  XXXXXX            /  ___---=
 *   -_    ___/    XXXXXX              '--- XXXXXX
 *     --\/XXX\ XXXXXX                      /XXXXX
 *       \XXXXXXXXX                        /XXXXX/
 *        \XXXXXX                        _/XXXXX/
 *          \XXXXX--__/              __-- XXXX/
 *           --XXXXXXX---------------  XXXXX--
 *              \XXXXXXXXXXXXXXXXXXXXXXXX-
 *                --XXXXXXXXXXXXXXXXXX-
 *          * * * * * who ya gonna call? * * * * *
 *
 *    ______       _   _               _
 *    | ___ \     | | | |             | |
 *    | |_/ / ___ | |_| |__  _   _ ___| |_ ___ _ __ ___
 *    | ___ \/ _ \| __| '_ \| | | / __| __/ _ \ '__/ __|
 *    | |_/ / (_) | |_| |_) | |_| \__ \ ||  __/ |  \__ \
 *    \____/ \___/ \__|_.__/ \__,_|___/\__\___|_|  |___/
 *
 */

#ifndef RUNNING_FRC_TESTS

int main() {
#ifndef SIMULATION
	Module::setConfigFileRootDir("/home/lvuser/newConfig/");
#else
	std::cout << PROJECT_DIR << std::endl;
	Module::setConfigFileRootDir(PROJECT_DIR);
#endif
	return frc::StartRobot<SlimerInSpace>();
}

#endif