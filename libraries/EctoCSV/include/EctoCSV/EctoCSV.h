//
// Created by abiel on 4/2/18.
//

#ifndef ECTOCSVTESTS_ECTOCSV_H
#define ECTOCSVTESTS_ECTOCSV_H

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <sstream>
#include <cmath>

using namespace std;

//Note, if write is chosen, read is also assumed
enum FileMode {
	Read,
	Write,
	Append,
	None
};

struct FileHeader {
	static constexpr auto separator = ':';
	static constexpr auto startMessage = "START_OF_ECTOCSV";

	size_t numberOfTables;
};

struct TableHeader {
	static constexpr auto separator = ':';
	static constexpr auto startMessage = "START_OF_TABLE";

	string nameOfTable;
	size_t numberOfColumns;
	vector<string> labels;
};

typedef map<string, vector<double>> Table;

class EctoCSV {
public:
	EctoCSV(string fileName, FileMode fileMode, bool overwrite = false);

	void addTable(const string &tableName);

	bool checkIfTableExists(const string &tableName) const;

	bool checkIfColumnExists(const string &tableName, const string &columnName) const;

	bool checkIfColumnExists(const string &columnName) const;

	vector<string> getTableNames() const;

	void setTable(const string &tableName);

	string getSetTable() const;

	void addColumn(const string &tableName, const string &columnName);

	void addColumn(const string &columnName);

	vector<string> getColumnNames(const string &tableName) const;

	vector<string> getColumnNames() const;

	void addElement(const string &tableName, const string &columnName, double value);

	void addElement(const string &columnName, double value);

	vector<double> getElements(const string &tableName, const string &columnName) const;

	vector<double> getElements(const string &columnName) const;

	double getElement(const string &tableName, const string &columnName, size_t pos) const;

	double getElement(const string &columnName, size_t pos) const;

	void clearElements(const string &tableName, const string &columnName);

	void clearElements(const string &columnName);

	void readData();

	void writeData();

	FileHeader getFileHeader() const;

	string generateCSVOutput(const string &tableName) const;

	vector<TableHeader> getTableHeaders();

	TableHeader generateTableHeader(const string &tableName) const;

	size_t getMaxColumnLengthInTable(const string &tableName) const;

private:
	bool checkIfFileExists(string fileName) const;

	string createFileHeader(const FileHeader &in) const;

	FileHeader readFileHeader();

	vector<string> splitString(const string &s, char delim) const;

	size_t readSizeTFromString(const string &in) const;

	string readUntilSeparator(string in, size_t startPos);

	void goToLine(istream &file, size_t line);

	string convertFileHeader(const FileHeader &fileHeader) const;

	string convertTableHeader(const TableHeader &tableHeader) const;

	string formatData() const;

	FileHeader parseFileHeader(const string &rawHeader) const;

	TableHeader parseTableHeader(const string &rawHeader) const;

	pair<vector<size_t>, vector<TableHeader>> readTableHeader(const FileHeader &currentFile);

	void readTable(size_t headerPos, const TableHeader &tableHeader);

	vector<string> getTableLabels(const string &tableName) const;

	void updateTableHeaders();

	string fileName;
	FileMode currentFileMode = FileMode::None;
	FileHeader currentFileHeader;

	ifstream inFile;
	ofstream outFile;

	map<string, Table> tables;
	vector<TableHeader> tableHeaders;
	string selectedTable;
};


#endif //ECTOCSVTESTS_ECTOCSV_H
