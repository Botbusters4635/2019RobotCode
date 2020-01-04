#include "EctoUtilities/EctoLog.h"
#include <iostream>

EctoLog::EctoLog(double updateRateMs, bool enabled) {
	stringstream fileName;
	fileName << (now->tm_year + 1900) << '-'
	         << (now->tm_mon + 1) << '-'
	         << now->tm_mday << '_'
	         << now->tm_hour << "hrs"
	         << now->tm_min << "mins"
	         << now->tm_sec << 's' << ".csv";
	string filePath("/home/lvuser/logs/");

	this->updateRateMs = updateRateMs;
	this->logEnabled = logEnabled;

	if (logEnabled) {
#ifdef __linux__
		const int dir_err = mkdir(filePath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if (-1 == dir_err)
			//BOOST_LOG_TRIVIAL(fatal) << "Error creating directory!";

#elif _WIN32
			if (CreateDirectoryA(filePath.c_str(), NULL) ||
				ERROR_ALREADY_EXISTS == GetLastError()) {
			} else {
				std::cout << "Error creating directory!" << std::endl;
			}

#endif
			file.open(filePath + fileName.str());
		if (file.is_open()) {
			fileOpen = true;
			headers.emplace_back(timestampKey);
			values.emplace_back(&elapsed_seconds);
		} else
			fileErrorPrompt();
	}
}

void EctoLog::fileErrorPrompt() {
	// BOOST_LOG_TRIVIAL(error) << FILE_ERROR << endl;
}

void EctoLog::logAlreadyRunErrorPrompt() {
	// BOOST_LOG_TRIVIAL(error) << LOGRUN_ERROR;
}

void EctoLog::logDisabledError() {
	// BOOST_LOG_TRIVIAL(error) << LOG_DISABLED;
}

template<typename T, typename T2>
void EctoLog::printVectors(const vector<T> &v, const vector<T2> &v2) {

	for (int i = 0; i < v.size(); ++i) {
		file << *EctoUtils::ptr(v[i]);
		if (i + 1 < v.size())
			file << ",";
	}
	if (!v2.empty())
		file << ",";
	for (int i = 0; i < v2.size(); ++i) {
		file << *EctoUtils::ptr(v2[i]);
		if (i + 1 < v2.size())
			file << ",";
	}
	file << endl;
}

void EctoLog::setHeaders() {
	printVectors(headers, headersBool);
}

bool EctoLog::isWriteAvailable() {
	if (!logEnabled) {
		logDisabledError();
		return false;
	}
	if (!fileOpen) {
		fileErrorPrompt();
		return false;
	}
	if (logState) {
		logAlreadyRunErrorPrompt();
		return false;
	}
	return true;
}

void EctoLog::addValue(const string key, double &value) {
	if (!isWriteAvailable())
		return;
	headers.emplace_back(key);
	values.emplace_back(&value);
}

void EctoLog::addValue(const string key, bool &value) {
	if (!isWriteAvailable())
		return;
	headersBool.emplace_back(key);
	valuesBool.emplace_back(&value);
}

void EctoLog::startLogging() {
	if (!isWriteAvailable())
		return;

	logState = true;
	std::unique_lock<std::mutex> lck(mtx);

	setHeaders();
	m_thread = std::thread(&EctoLog::update, this);
}

void EctoLog::update() {
	std::unique_lock<std::mutex> lck(mtx);

	if (logEnabled) {
		while (logState && fileOpen) {
			next = Time::now();
			elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double >>(next - start).count();

			printVectors(values, valuesBool);

			this_thread::sleep_for(std::chrono::duration<double>(updateRateMs / 1000.0));
		}
		file.close();
		m_thread.join();
	}
}
