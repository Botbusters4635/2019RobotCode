//
// Created by abiel on 4/2/18.
//

#include "EctoCSV/EctoCSV.h"

EctoCSV::EctoCSV(string fileName, FileMode fileMode, bool overwrite) {
	this->fileName = fileName;
	this->currentFileMode = fileMode;

	//Reads FileHeader from file
	if (fileMode == FileMode::Read) {
		//Checks if file exists
		if (!checkIfFileExists(fileName))
			throw runtime_error("File name does not exist: " + fileName);

		inFile.open(fileName);

		this->currentFileHeader = readFileHeader();

	} else if (fileMode == FileMode::Write) {
		if (overwrite && checkIfFileExists(fileName))
			if (remove(fileName.c_str()) != 0)
				throw runtime_error("Failed to delete file " + fileName);

		//Checks if file exists
		if (checkIfFileExists(fileName))
			throw runtime_error("File name already exists: " + fileName);

		outFile.open(fileName);

	} else if (fileMode == FileMode::Append) {
		if (!checkIfFileExists(fileName))
			throw runtime_error("File name does not exist: " + fileName);

		inFile.open(fileName);
		this->currentFileHeader = readFileHeader();

		readData();

		inFile.close();

		if (remove(fileName.c_str()) != 0)
			throw runtime_error("Failed to delete file " + fileName);

		this->currentFileMode = FileMode::Write;

		outFile.open(fileName);
	} else {
		throw runtime_error("No valid FileMode selected");
	}
}

/**
 * Checks if file exists in directory
 * @param fileName
 * @return
 */
bool EctoCSV::checkIfFileExists(string fileName) const {
	ifstream inFile(fileName);

	return inFile.good();
}

/**
 * Creates a string file header given a FileHeader
 * @param in
 * @return
 */
string EctoCSV::createFileHeader(const FileHeader &in) const {
	ostringstream os;

	os << FileHeader::startMessage;
	os << FileHeader::separator << in.numberOfTables << endl;

	return os.str();
}

/**
 * Finds and reads FileHeader from current file
 * @return
 */
FileHeader EctoCSV::readFileHeader() {
	string rawHeader;

	//Goes to first line in file
	inFile.clear();
	inFile.seekg(0, inFile.beg);

	getline(inFile, rawHeader);

	return parseFileHeader(rawHeader);
}

/**
 * Reads all table headers in file and returns their position and the TableHeader
 * @param currentFile
 * @return
 */
pair<vector<size_t>, vector<TableHeader>> EctoCSV::readTableHeader(const FileHeader &currentFile) {
	//Go to beginning of file
	inFile.clear();
	inFile.seekg(0, inFile.beg);

	//Lines in which headers are found
	vector<string> rawHeaders;
	vector<size_t> headerLinePos;

	//Current line and line buffer
	size_t currentLine = 0;
	string line;

	//Finds all TableHeaders, stores the rawString to a vector and stores the linePosition to a vector
	while (getline(inFile, line)) {
		currentLine++;

		if (line.find(TableHeader::startMessage, 0) != string::npos) {
			rawHeaders.emplace_back(line);
			headerLinePos.emplace_back(currentLine);
		}
	}

	vector<TableHeader> headers;

	//Parses all headers and adds them to the vector
	for (const string &rawHeader : rawHeaders) {
		headers.emplace_back(parseTableHeader(rawHeader));
	}

	return make_pair(headerLinePos, headers);
}

/**
 * Splits string into a vector
 * @param s
 * @param delim
 * @return
 */
vector<string> EctoCSV::splitString(const string &s, char delim) const {
	stringstream ss(s);

	string item;
	vector<string> tokens;

	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}

	return tokens;
}

/**
 * Converts a string to size_t
 * @param in
 * @return
 */
size_t EctoCSV::readSizeTFromString(const string &in) const {
	stringstream stream(in);
	size_t result;

	stream >> result;

	return result;
}

string EctoCSV::readUntilSeparator(string in, size_t startPos) {
	auto firstSeparator = in.find(FileHeader::separator, startPos) + 1;

	if (firstSeparator == string::npos)
		throw runtime_error("Did not find first separator");

	auto secondSeparator = in.find(FileHeader::separator, firstSeparator);

	if (secondSeparator == string::npos)
		throw runtime_error("Did not find second separator");

	return in.substr(firstSeparator, secondSeparator - firstSeparator);
}

/**
 * Moves to the selected line (starts at 1)
 * @param file
 * @param line
 */
void EctoCSV::goToLine(istream &file, size_t line) {
	//Goes to begging of file
	inFile.clear();
	inFile.seekg(0, file.beg);

	//Temporary buffer (not used)
	string buf;

	for (size_t i = 1; i <= line; ++i) {
		getline(file, buf);
	}
}

/**
 * Adds a table
 * @param tableName
 */
void EctoCSV::addTable(const string &tableName) {
	tables.emplace(make_pair(tableName, Table()));

	//Updates current table size
	currentFileHeader.numberOfTables = tables.size();
}

bool EctoCSV::checkIfTableExists(const string &tableName) const {
	return !(tables.find(tableName) == tables.end());
}

bool EctoCSV::checkIfColumnExists(const string &tableName, const string &columnName) const {
	if (tables.find(tableName) == tables.end())
		throw runtime_error("Tried to use a non-existing table " + tableName);

	return !(tables.at(tableName).find(columnName) == tables.at(tableName).end());
}

bool EctoCSV::checkIfColumnExists(const string &columnName) const {
	return checkIfColumnExists(selectedTable, columnName);
}

/**
 * Returns currently set table
 * @return
 */
string EctoCSV::getSetTable() const {
	return selectedTable;
}

/**
 * Get table names
 * @return
 */
vector<string> EctoCSV::getTableNames() const {
	vector<string> output;

	for (auto table : tables)
		output.emplace_back(table.first);

	return output;
}

/**
 * Sets the table to use when no table arguments are given
 * @param tableName
 */
void EctoCSV::setTable(const string &tableName) {
	if (tables.find(tableName) == tables.end())
		throw runtime_error("Tried to set a non-existing table " + tableName);

	selectedTable = tableName;
}

/**
 * Adds a column to a table
 * @param tableName
 * @param columnName
 */
void EctoCSV::addColumn(const string &tableName, const string &columnName) {
	if (tables.find(tableName) == tables.end())
		throw runtime_error("Tried to use a non-existing table " + tableName);

	tables.at(tableName).emplace(make_pair(columnName, vector<double>()));
}

/**
 * Adds a column to the previously selected table
 * @param columnName
 */
void EctoCSV::addColumn(const string &columnName) {
	addColumn(selectedTable, columnName);
}

/**
 * Gets the column names in table
 * @param tableName
 * @return
 */
vector<string> EctoCSV::getColumnNames(const string &tableName) const {
	if (tables.find(tableName) == tables.end())
		throw runtime_error("Tried to use a non-existing table " + tableName);

	vector<string> names;
	auto table = tables.at(tableName);

	for (auto column : table)
		names.emplace_back(column.first);

	return names;
}

/**
 * Gets the column names from the previously selected table
 * @return
 */
vector<string> EctoCSV::getColumnNames() const {
	return getColumnNames(selectedTable);
}

/**
 * Adds an element to the selected table and column
 * @param tableName
 * @param columnName
 * @param value
 */
void EctoCSV::addElement(const string &tableName, const string &columnName, double value) {
	if (tables.find(tableName) == tables.end())
		throw runtime_error("Tried to use a non-existing table " + tableName);

	Table &table = tables.at(tableName);

	if (table.find(columnName) == table.end())
		throw runtime_error("Tried to use a non-existing column " + tableName);

	table.at(columnName).emplace_back(value);
}

/**
 * Adds an element to the previously selected table and column
 * @param columnName
 * @param value
 */
void EctoCSV::addElement(const string &columnName, double value) {
	addElement(selectedTable, columnName, value);
}

/**
 * Gets all elements from column
 * @param tableName
 * @param columnName
 * @return
 */
vector<double> EctoCSV::getElements(const string &tableName, const string &columnName) const {
	if (tables.find(tableName) == tables.end())
		throw runtime_error("Tried to use a non-existing table " + tableName);

	auto &table = tables.at(tableName);

	if (table.find(columnName) == table.end())
		throw runtime_error("Tried to use a non-existing column " + tableName);

	auto &column = table.at(columnName);

	return column;
}

/**
 * Gets all elements from column in previously selected table
 * @param columnName
 * @return
 */
vector<double> EctoCSV::getElements(const string &columnName) const {
	return getElements(selectedTable, columnName);
}

/**
 * Gets an individual element
 * @param tableName
 * @param columnName
 * @param pos
 * @return
 */
double EctoCSV::getElement(const string &tableName, const string &columnName, size_t pos) const {
	if (tables.find(tableName) == tables.end())
		throw runtime_error("Tried to use a non-existing table " + tableName);

	auto &table = tables.at(tableName);

	if (table.find(columnName) == table.end())
		throw runtime_error("Tried to use a non-existing column " + tableName);

	auto &column = table.at(columnName);

	if (pos > column.size())
		throw runtime_error("Tried to get an invalid row: " + pos);

	return column.at(pos);
}

/**
 * Gets an individual element from previously selected column
 * @param columnName
 * @param pos
 * @return
 */
double EctoCSV::getElement(const string &columnName, size_t pos) const {
	return getElement(selectedTable, columnName, pos);
}

/**
 * Clears all elements in a column
 * @param tableName
 * @param columnName
 */
void EctoCSV::clearElements(const string &tableName, const string &columnName) {
	if (tables.find(tableName) == tables.end())
		throw runtime_error("Tried to use a non-existing table " + tableName);

	tables.at(tableName).at(columnName).clear();
}

void EctoCSV::clearElements(const string &columnName) {
	clearElements(selectedTable, columnName);
}

/**
 * Generates TableHeaders for all tables in object
 * @param tableName
 * @return
 */
TableHeader EctoCSV::generateTableHeader(const string &tableName) const {
	if (tables.find(tableName) == tables.end())
		throw runtime_error("Tried to use a non-existing table " + tableName);

	auto table = tables.at(tableName);

	TableHeader header;

	header.nameOfTable = tableName;
	header.numberOfColumns = table.size();
	header.labels = getColumnNames(tableName);

	return header;
}

/**
 * Converts a FileHeader to a string
 * @param fileHeader
 * @return
 */
string EctoCSV::convertFileHeader(const FileHeader &fileHeader) const {
	ostringstream stream;

	stream << FileHeader::startMessage;

	stream << FileHeader::separator << fileHeader.numberOfTables;

	return stream.str();
}

/**
 * Converts a TableHeader to a string
 * @param tableHeader
 * @return
 */
string EctoCSV::convertTableHeader(const TableHeader &tableHeader) const {
	ostringstream stream;

	//Appends startMessage
	stream << TableHeader::startMessage;

	//Adds the name of table and number of columns
	stream << TableHeader::separator << tableHeader.nameOfTable;
	stream << TableHeader::separator << tableHeader.numberOfColumns;

	//Adds all labels
	for (const auto &column : tableHeader.labels) {
		stream << TableHeader::separator << column;
	}

	return stream.str();
}

/**
 * Gets the max column length in a table
 * @param tableName
 * @return
 */
size_t EctoCSV::getMaxColumnLengthInTable(const string &tableName) const {
	if (tables.find(tableName) == tables.end())
		throw runtime_error("Tried to use a non-existing table " + tableName);

	const Table table = tables.at(tableName);

	double currentMax = 0;

	for (pair<string, vector<double>> column : table) {
		currentMax = max(currentMax, (double) column.second.size());
	}

	return (size_t) currentMax;
}

/**
 * Generates a CSV output for the selected table
 * @param tableName
 * @return
 */
string EctoCSV::generateCSVOutput(const string &tableName) const {
	if (tables.find(tableName) == tables.end())
		throw runtime_error("Tried to use a non-existing table " + tableName);

	ostringstream stream;

	const Table &table = tables.at(tableName);
	double maxLength = getMaxColumnLengthInTable(tableName);

	//Iterates over all rows of table
	for (size_t i = 0; i < maxLength; ++i) {
		//Iterates over all columns of table
		for (auto column : table) {
			double num;
			bool isLast = false;

			if (table.rbegin()->first == column.first)
				isLast = true;

			//If no element is in row, return 0
			if (column.second.size() - 1 < i || column.second.empty()) {
				num = 0.0;
			} else {
				num = column.second.at(i);
			}

			stream << num;

			//Only append a comma if element is not last
			if (!isLast)
				stream << ',';
		}

		stream << endl;
	}

	return stream.str();
}

/**
 * Parses a FileHeader from a string
 * @param rawHeader
 * @return
 */
FileHeader EctoCSV::parseFileHeader(const string &rawHeader) const {
	FileHeader header;

	if (rawHeader.find(FileHeader::startMessage) == string::npos)
		throw runtime_error("No header found in " + rawHeader);

	auto headerVector = splitString(rawHeader, FileHeader::separator);

	header.numberOfTables = readSizeTFromString(*headerVector.begin());

	return header;
}

/**
 * Parses a TableHeader from a string
 * @param rawHeader
 * @return
 */
TableHeader EctoCSV::parseTableHeader(const string &rawHeader) const {
	if (rawHeader.find(TableHeader::startMessage) == string::npos)
		throw runtime_error("No header found in " + fileName);

	auto headerVector = splitString(rawHeader, FileHeader::separator);

	if (headerVector.size() <= 2)
		throw runtime_error("Tried to parse invalid header " + rawHeader);

	TableHeader header;

	header.nameOfTable = headerVector.at(1);
	header.numberOfColumns = readSizeTFromString(headerVector.at(2));

	if (header.numberOfColumns > 0) {
		vector<string> labels;

		//Iterates through all column labels
		for (auto i = headerVector.begin() + 3; i != headerVector.end(); ++i) {
			labels.emplace_back(*i);
		}

		header.labels = labels;
	}

	return header;
}

/**
 * Formats all data in object to a string
 * @return
 */
string EctoCSV::formatData() const {
	ostringstream stream;

	stream << convertFileHeader(currentFileHeader) << endl << endl;

	for (auto table : tables) {
		stream << convertTableHeader(generateTableHeader(table.first)) << endl;
		stream << generateCSVOutput(table.first) << endl;
	}

	return stream.str();
}

/**
 * Reads a table from a file
 * @param headerPos
 * @param tableHeader
 */
void EctoCSV::readTable(size_t headerPos, const TableHeader &tableHeader) {
	size_t numberOfColumns = tableHeader.numberOfColumns;

	addTable(tableHeader.nameOfTable);

	//Adds all columns from labels
	for (const string &label : tableHeader.labels)
		addColumn(tableHeader.nameOfTable, label);

	//First line of table and last line of the table
	size_t firstTableLine = headerPos + 1;
	size_t lastTableLine;

	goToLine(inFile, firstTableLine);

	size_t currentLine = firstTableLine;
	string line;

	//Finds the last line
	while (getline(inFile, line) && !line.empty()) {
		++currentLine;
	}

	lastTableLine = currentLine - 1;

	//Returns to the first line
	goToLine(inFile, firstTableLine);

	for (size_t tableLine = firstTableLine; tableLine <= lastTableLine; ++tableLine) {
		string line;

		getline(inFile, line);

		vector<string> valuesString = splitString(line, ',');

		for (size_t column = 0; column < numberOfColumns; ++column) {
			addElement(tableHeader.nameOfTable, tableHeader.labels.at(column), stod(valuesString.at(column)));
		}
	}
}

/**
 * Returns the current file header
 * @return
 */
FileHeader EctoCSV::getFileHeader() const {
	return this->currentFileHeader;
}

vector<string> EctoCSV::getTableLabels(const string &tableName) const {
	if (tables.find(tableName) == tables.end())
		throw runtime_error("Tried to set a non-existing table " + tableName);

	vector<string> labels;

	auto const &table = tables.at(tableName);

	for (auto const &column : table)
		labels.emplace_back(column.first);

	return labels;
}

void EctoCSV::updateTableHeaders() {
	tableHeaders.clear();

	for (auto table : tables) {
		tableHeaders.emplace_back(generateTableHeader(table.first));
	}
}

/**
 * Reads data from file
 */
void EctoCSV::readData() {
	auto tableFileHeaders = readTableHeader(this->currentFileHeader);

	for (size_t i = 0; i < tableFileHeaders.first.size(); ++i) {
		readTable(tableFileHeaders.first.at(i), tableFileHeaders.second.at(i));
	}

	for (const TableHeader &header : tableFileHeaders.second) {
		tableHeaders.emplace_back(header);
	}
}

/**
 * Writes data to file
 */
void EctoCSV::writeData() {
	if (currentFileMode != FileMode::Write)
		throw runtime_error("Tried to write to a file which is not set in write mode");

	string data = formatData();

	outFile << data;

	outFile.close();
}

/**
 * Regenerates and gets all table headers
 * @return
 */
vector<TableHeader> EctoCSV::getTableHeaders() {
	updateTableHeaders();

	return tableHeaders;
}
