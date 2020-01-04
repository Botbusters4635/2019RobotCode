//
// Created by Abiel on 8/26/18.
//

#ifndef BOTBUSTERSREBIRTH_MULTIPLECSVWRITER_H
#define BOTBUSTERSREBIRTH_MULTIPLECSVWRITER_H

#include <string>
#include <fstream>
#include <cstdio>
#include <typeinfo>
#include <sys/stat.h>
#include "CSVWritable.h"

/**
 * Writes multiple objects of the same type to a file
 */
class MultipleCSVWriter {
public:
	explicit MultipleCSVWriter(const std::string &fileName, bool overwrite = true, bool useDefaultFileLocation = true);

	void openFile();

	void writeObject(const CSVWritable &objectToWrite);

	void closeFile();

	~MultipleCSVWriter();

private:
	static constexpr auto defaultFileLocation = "/home/lvuser";

	static inline bool checkIfFileExists(const std::string &fileName);

	std::string fileName;

	bool overwrite = false;

	bool firstTimeFileOpened = true;

	std::ofstream file;

	bool firstObject = true;
	std::size_t typeOfObjectsStored_hash;
	std::string typeOfObjectStored_name;
};


#endif //BOTBUSTERSREBIRTH_MULTIPLECSVWRITER_H
