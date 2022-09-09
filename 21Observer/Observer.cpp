#include <iostream>
#include <list>
#include <algorithm>
#include <bitset>

class Subject;

//Step 1
struct Observer
{
	protected:
		Subject * subject = nullptr;
		Observer(){};
		Observer(Subject *subject):subject(subject){}
	public:
		virtual void update() = 0;
		virtual ~Observer() = 0;
};
Observer::~Observer(){};

//Step 2
class Subject
{
	std::list<Observer *> observers;

	int state;
public:
	int getState()
	{
		return state;
	}

	void setState(int state)
	{
		this->state = state;

		notifyAllObservers();
	}

	void attach(Observer *observer)
	{
		observers.push_back(observer);
	}

	void notifyAllObservers()
	{
		for_each(
			observers.begin(), observers.end(),
			[](Observer *o){
				o->update();
			}
		);
	}
};

//Step 3
class BinaryObserver: public Observer
{
	public:
	BinaryObserver(Subject *subject):Observer(subject)
	{
		//this->subject = subject;
		this->subject->attach(this);
	}

	void update() override {
		std::cout << "Binary String: " << std::bitset<sizeof (int)>(subject->getState()) << std::endl;
	}
};

class OctalObserver: public Observer
{
	public:
	OctalObserver(Subject *subject)//:Observer(subject)
	{
		this->subject = subject;
		this->subject->attach(this);
	}

	void update() override {
		std::cout << "Octal String: " << std::oct << subject->getState() << std::endl;
	}
};

class HexaObserver: public Observer
{
public:
	HexaObserver(Subject *subject):Observer(subject)
	{
		//this->subject = subject;
		this->subject->attach(this);
	}

	void update() override {
		std::cout << "Hex String: " << std::hex << std::uppercase << subject->getState() << std::endl;
	}
};

int main(int argc, char *argv[])
{
	Subject subject;

	HexaObserver hexaObserver(&subject);
	OctalObserver octalObserver(&subject);
	BinaryObserver binaryObserver(&subject);

	std::cout << "First state change: 15" << std::endl;
	subject.setState(15);

	std::cout << "Second state change: 10" << std::endl;
	subject.setState(10);

	return 0;
}
