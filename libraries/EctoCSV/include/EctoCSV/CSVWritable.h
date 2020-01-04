//
// Created by Abiel on 8/24/18.
//

#ifndef BOTBUSTERSREBIRTH_CSVWRITABLE_H
#define BOTBUSTERSREBIRTH_CSVWRITABLE_H

#include <string>
#include <sstream>

class CSVWritable {
public:
	//Name of each column of data
	//Note: does not add a new line at the end
	virtual std::string getCSVColumnNames() const = 0;

	//Write data to CSV, adds a new line at the end
	virtual std::string toCSV() const = 0;
};

#endif //BOTBUSTERSREBIRTH_CSVWRITABLE_H
