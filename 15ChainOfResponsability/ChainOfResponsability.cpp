#include<iostream>

//Step 1
struct AbstractLogger {

	static int const INFO = 1;
	static int const DEBUG = 2;
	static int const ERROR = 3;

	void setNextLogger(AbstractLogger *nextLogger){
		this->nextLogger = nextLogger;
	}

	void logMessage(int level, std::string message){
		if(this->level <= level){
			write(message);
		}

		if(nextLogger != nullptr){
			nextLogger->logMessage(level, message);
		}
	}

	AbstractLogger(int level):level(level){};

	virtual ~AbstractLogger() = 0;

protected:
	int level = 0;

	AbstractLogger *nextLogger;

	virtual void write(std::string message) = 0;
};

AbstractLogger::~AbstractLogger(){};

//Step 2
class ConsoleLogger: public AbstractLogger {
public:
	ConsoleLogger(int level):AbstractLogger(level){}

protected:
	void write(std::string message) override {
		std::cout << "Standard Console::Logger: " << message << std::endl;
	}
};

class ErrorLogger: public AbstractLogger {
public:
	ErrorLogger(int level):AbstractLogger(level){}

protected:
	void write(std::string message) override {
		std::cout << "Error Console::Logger: " << message << std::endl;
	}
};

class FileLogger: public AbstractLogger {
public:
	FileLogger(int level):AbstractLogger(level){}

protected:
	void write(std::string message) override {
		std::cout << "File::Logger: " << message << std::endl;
	}
};

//Step 3

static AbstractLogger * getChainOfLoggers()
{
	ErrorLogger *errorLogger = new ErrorLogger(AbstractLogger::ERROR);
	FileLogger *fileLogger = new FileLogger(FileLogger::DEBUG);
	AbstractLogger *consoleLogger = new ConsoleLogger(AbstractLogger::INFO);

	errorLogger->setNextLogger(fileLogger);

	fileLogger->setNextLogger(consoleLogger);

	return errorLogger;
}

int main()
{
	AbstractLogger *loggerChain = getChainOfLoggers();

	loggerChain->logMessage(AbstractLogger::INFO, "This is an information.");

	loggerChain->logMessage(AbstractLogger::DEBUG, "This is a debug level information.");

	loggerChain->logMessage(AbstractLogger::ERROR, "This is a error information.");

	return 0;
}
