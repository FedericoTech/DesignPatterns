#include <iostream>

//Step 1
struct Strategy
{
	virtual int doOperation(int num1, int num2) = 0;
	virtual ~Strategy() = 0;
};

Strategy::~Strategy(){};

//Step 2
class OperationAdd: public Strategy
{
	int doOperation(int num1, int num2){
		return num1 + num2;
	}
};

class OperationSubstract: public Strategy
{
	int doOperation(int num1, int num2){
		return num1 - num2;
	}
};

class OperationMultiply: public Strategy
{
	int doOperation(int num1, int num2){
		return num1 * num2;
	}
};

//Step 3

class Context
{
	Strategy *strategy;

public:
	Context(Strategy *strategy):strategy(strategy){};

	int executeStrategy(int num1, int num2)
	{
		return strategy->doOperation(num1, num2);
	}
};

int main(int argc, char **argv)
{
	Context *context = new Context(new OperationAdd());

	std::cout << "10 + 5 = " << context->executeStrategy(10, 5) << std::endl;
	delete context;

	context = new Context(new OperationSubstract());

	std::cout << "10 - 5 = " << context->executeStrategy(10, 5) << std::endl;
	delete context;

	context = new Context(new OperationMultiply());

	std::cout << "10 * 5 = " << context->executeStrategy(10, 5) << std::endl;
	delete context;

	return 0;
}
