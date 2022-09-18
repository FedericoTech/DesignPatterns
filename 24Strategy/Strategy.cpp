#include <iostream>

//Step 1
struct Strategy
{
	virtual int doOperation(int num1, int num2) = 0;
	virtual ~Strategy() = 0;
	virtual Strategy *clone() = 0; // this method is to clone the class when copy assigning
};

Strategy::~Strategy(){};

//Step 2
class OperationAdd: public Strategy
{
	int doOperation(int num1, int num2){
		return num1 + num2;
	}

	OperationAdd * clone() {
		return new OperationAdd(*this);
	}
};

class OperationSubstract: public Strategy
{
	int doOperation(int num1, int num2){
		return num1 - num2;
	}

	OperationSubstract *clone() {
		return new OperationSubstract(*this);
	}
};

class OperationMultiply: public Strategy
{
	int doOperation(int num1, int num2){
		return num1 * num2;
	}

	OperationMultiply *clone() {
		return new OperationMultiply(*this);
	}
};

//Step 3

class Context
{
	Strategy *strategy;

public:
	Context(Strategy *strategy):strategy(strategy){};

	Context &operator=(Context const& other) //copy assignment operator
	{
		//if the copy is on the own instance...
		if(this == &other){ return *this; }

		delete strategy; //delete the current strategy instance.

		//because the pointer is abstract, we use the clone method to clone que the type accordingly
		this->strategy = other.strategy ? other.strategy->clone() : nullptr;

		return *this; //now we return the present object
	}

	int executeStrategy(int num1, int num2)
	{
		return strategy->doOperation(num1, num2);
	}

	~Context()
	{
		delete strategy;
	}
};

int main(int argc, char **argv)
{
	Context context(new OperationAdd());

	std::cout << "10 + 5 = " << context.executeStrategy(10, 5) << std::endl;

	context = Context(new OperationSubstract());

	std::cout << "10 - 5 = " << context.executeStrategy(10, 5) << std::endl;

	context = Context(new OperationMultiply());

	std::cout << "10 * 5 = " << context.executeStrategy(10, 5) << std::endl;

	return 0;
}
