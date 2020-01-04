//
// Created by Abiel on 8/25/18.
//

#ifndef BOTBUSTERSREBIRTH_CSVWRITER_H
#define BOTBUSTERSREBIRTH_CSVWRITER_H

#include <string>
#include <fstream>
#include <cstdio>
#include <stdexcept>
#include <sys/stat.h>
#include <typeinfo>
#include "CSVWritable.h"

class CSVWriter {
public:
	CSVWriter(const std::string &fileName, const CSVWritable &objectToWriteInput, bool overwrite = true,
	          bool useDefaultFileLocation = true);

	/**
	 * Returns true if it opened the file without errors
	 * @return
	 */
	bool writeToFile();

private:
	static constexpr auto defaultFileLocation = "/home/lvuser";

	static inline bool checkIfFileExists(const std::string &fileName);

	const CSVWritable &objectToWrite;

	std::string fileName;
	bool overwrite;
};


#endif //BOTBUSTERSREBIRTH_CSVWRITER_H
