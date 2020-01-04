//
// Created by Abiel on 8/25/18.
//

#include "EctoCSV/CSVWriter.h"

CSVWriter::CSVWriter(const std::string &fileName, const CSVWritable &objectToWriteInput, bool overwrite,
                     bool useDefaultFileLocation) : objectToWrite(objectToWriteInput) {
	if (useDefaultFileLocation)
		this->fileName = defaultFileLocation + fileName;
	else
		this->fileName = fileName;

	if (!overwrite && checkIfFileExists(fileName))
		throw std::runtime_error("Tried to write a csv to a file that already exists " + this->fileName);

	this->overwrite = overwrite;
}

bool CSVWriter::writeToFile() {
	std::ofstream stream;

	if (overwrite)
		stream.open(fileName, std::ios::trunc);
	else
		stream.open(fileName);

	bool status = stream.good();

	stream << objectToWrite.getCSVColumnNames() << ',' << typeid(objectToWrite).name() << '\n';
	stream << objectToWrite.toCSV();

	stream.close();

	return status;
}

bool CSVWriter::checkIfFileExists(const std::string &fileName) {
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}