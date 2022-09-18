#include <iostream>
#include <list>
#include <algorithm>

//Step 1
class Memento
{
	std::string state;

public:
	Memento(std::string state):state(state){};

	std::string getState()
	{
		return state;
	}
/*
	~Memento(){
		std::cout << "memento destructor " << state << std::endl;
	}
*/
};

//Step 2
class Originator
{
	std::string state;

public:
	void setState(std::string state)
	{
		this->state = state;
	}

	std::string getState()
	{
		return state;
	}

	Memento *saveStateToMemento()
	{
		return new Memento(state);
	}

	void getStateFromMemento(Memento *memento)
	{
		state = memento->getState();
	}
};

//State 3
class CareTaker
{
	std::list<Memento *> mementoList;

public:
	void add(Memento *state){
		mementoList.push_back(state);
	}

	Memento *get(int index)
	{
		auto l_front = mementoList.begin();
		std::advance(l_front, index);
		return *l_front;
	}

	~CareTaker(){
		for(Memento *m : mementoList){
			delete m;
		}
	}
};

int main(int argc, char *argv[])
{
	Originator originator;
	CareTaker careTaker;

	originator.setState("State #1");
	originator.setState("State #2");

	careTaker.add(originator.saveStateToMemento());

	originator.setState("State #3");
	careTaker.add(originator.saveStateToMemento());

	originator.setState("state #4");
	std::cout << "Current State: " << originator.getState() << std::endl;

	originator.getStateFromMemento(careTaker.get(0));
	std::cout << "First saved State: " << originator.getState() << std::endl;

	originator.getStateFromMemento(careTaker.get(1));
	std::cout << "Second saved State: " << originator.getState() << std::endl;

	return 0;
}
