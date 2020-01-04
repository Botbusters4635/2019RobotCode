/*
* Settings
* Group: EctoLog
* Enabled: Enabled state
* UpdateRateMs: Update Rate
 */
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <fstream>
#include <ctime>
#include <mutex>
#include "EctoUtilities/EctoUtils.h"

#ifdef __linux__

#include <sys/types.h>
#include <sys/stat.h>

#elif _WIN32

#include <Windows.h>

#endif

/*
Singleton EctoLog class
Made by Alberto

This class manages the logging to a .csv file from the RoboRio for debugging
purposes

Usage:
You need to declare a reference to this singleton, this is done as follows
EctoLog& log = EctoLog::getInstance();

Then, you start defining which variables you want to keep track of.
addValue needs first the key that will identify that value on the csv and the variable itself.
log.addValue("key", double);
log.addValue("key", boolean);

Afterwards, when you are done adding values to be logged, you tell EctoLog to start working,
keep in mind that once this is done you cannot add any more variables to record.

Logging is started as follows.
log.startLogging();

IN-CLASS Usage:
The process is very similar to the one already described, the only difference being
how the reference to the singleton is declared and defined.
Header File (.h)
Here we declare a member Reference to the class where it will be used.
Remember to include EctoLog's Header File (Example)
class Test () {
Test();
EctoLog& log;
};
Source File (.cpp)
Here we initialize the reference on the "Initialization List", notice this is done on the constructor
Test::Test() : log(EctoLog::getInstance()){

}
*/

enum severity_level {
	normal,
	trace,
	debug,
	info,
	warning,
	error,
	fatal
};

using namespace std;
typedef chrono::steady_clock Time;
typedef chrono::milliseconds ms;
typedef chrono::duration<float> fsec;

class EctoLog {
public:
	void addValue(string key, double &value);

	void addValue(string key, bool &value);

	void startLogging();

	static EctoLog &getInstance(double updateRateMs = 50, bool enabled = true) {
		static EctoLog singletonInstance(updateRateMs, enabled);
		return singletonInstance;
	}

private:
	const string FILE_ERROR = "Could not open file for logging";
	const string LOGRUN_ERROR = "Logging already running, check code, this may crash. :c";
	const string LOG_DISABLED = "Logging is disabled.";

	const string timestampKey = "timestamp";

	void fileErrorPrompt();

	void logAlreadyRunErrorPrompt();

	void logDisabledError();

	template<typename T, typename T2>
	void printVectors(const vector<T> &v, const vector<T2> &v2);

	EctoLog(double updateRateMs, bool enabled);

	EctoLog(const EctoLog &);

	EctoLog &operator=(const EctoLog &);

	void setHeaders();

	bool isWriteAvailable();

	vector<string> headers;
	vector<double *> values;

	vector<string> headersBool;
	vector<bool *> valuesBool;

	thread m_thread;
	mutex mtx;           // mutex for critical section

	ofstream file;
	time_t t = time(nullptr);
	struct tm *now = localtime(&t);

	chrono::steady_clock::time_point start = Time::now();
	chrono::steady_clock::time_point next = Time::now();
	double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(
			next - start).count();

	void update();

	bool logState = false;
	bool fileOpen = false;
	double updateRateMs;
	bool logEnabled;

};
