#include<iostream>
#include<ostream>

class Context;

//Step 1
struct State{
	virtual void doAction(Context *) = 0;
	virtual ~State() = 0;
	friend std::ostream &operator << (std::ostream &, State const &);
};
State::~State(){}

//Step 2
class StartState: public State
{
public:
	void doAction(Context *);
};

class StopState: public State
{
public:
	void doAction(Context *);
};

std::ostream &operator << (std::ostream &os, State const &st)
{
	const StopState *ss = dynamic_cast<const StopState*>(&st);

	if(ss != nullptr)
	{
		os << "Stop State";
	} else {
		os << "Start State";
	}
	return os;
}

//Step 3
class Context
{
	State *state = nullptr;

public:
	void setState(State *state){
		this->state = state;
	}

	State *getState()
	{
		return state;
	}
};

void StartState::doAction(Context *context){
	std::cout << "Player is in start state" << std::endl;
	context->setState(this);
}

void StopState::doAction(Context *context){
	std::cout << "Player is in stop state" << std::endl;
	context->setState(this);
}

int main(int argc, char *argv[])
{
	Context context;

	StartState startState;
	startState.doAction(&context);

	std::cout << *(context.getState()) << std::endl;

	StopState stopState;
	stopState.doAction(&context);

	std::cout << *(context.getState()) << std::endl;

	return 0;
}
