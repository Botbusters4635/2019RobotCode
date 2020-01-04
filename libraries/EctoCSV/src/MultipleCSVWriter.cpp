//
// Created by Abiel on 8/26/18.
//

#include "EctoCSV/MultipleCSVWriter.h"

MultipleCSVWriter::MultipleCSVWriter(const std::string &fileName, bool overwrite, bool useDefaultFileLocation) {
	if (useDefaultFileLocation)
		this->fileName = defaultFileLocation + fileName;
	else
		this->fileName = fileName;

	if (!overwrite && checkIfFileExists(fileName))
		throw std::runtime_error("Tried to write a csv to a file that already exists " + this->fileName);

	this->overwrite = overwrite;
}

bool MultipleCSVWriter::checkIfFileExists(const std::string &fileName) {
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}

void MultipleCSVWriter::openFile() {
	if (firstTimeFileOpened && overwrite)
		file.open(fileName, std::ios::trunc);

	file.open(fileName);

	firstTimeFileOpened = false;
}

void MultipleCSVWriter::writeObject(const CSVWritable &objectToWrite) {
	const std::type_info &typeInfo(typeid(objectToWrite));

	if (firstObject) {
		typeOfObjectsStored_hash = typeInfo.hash_code();
		typeOfObjectStored_name = typeInfo.name();

		firstObject = false;
	} else {
		if (typeOfObjectsStored_hash != typeInfo.hash_code())
			throw std::runtime_error("Attempted to write an object of type: " + std::string(typeInfo.name()) +
			                         " to a CSV containing objects of type: " + typeOfObjectStored_name);
	}

	if (!file.is_open())
		throw std::runtime_error("Tried to write to a file that is not open: " + fileName);

	file << objectToWrite.getCSVColumnNames() << ',' << typeInfo.name() << '\n';
	file << objectToWrite.toCSV();
}

void MultipleCSVWriter::closeFile() {
	file.close();
}

MultipleCSVWriter::~MultipleCSVWriter() {
	this->closeFile();
}