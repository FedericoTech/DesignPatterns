#include <iostream>
#include <memory>

//Step 1

struct Expression
{
	virtual bool interpret(std::string context) = 0;
	virtual ~Expression() = 0;
};

Expression::~Expression(){};

//Step 2
class TerminalExpression: public Expression {
	std::string data;

public:
	TerminalExpression(std::string data): data(data) {};

	bool interpret(std::string context) override {
		return context.find(data, 0) != std::string::npos;
	}
};

class OrExpression: public Expression
{
	Expression *expr1;
	Expression *expr2;

public:
	OrExpression() = delete;

	OrExpression(Expression *expr1, Expression *expr2): expr1(expr1), expr2(expr2){};

	bool interpret(std::string context){
		return expr1->interpret(context) || expr2->interpret(context);
	}

	~OrExpression()
	{
		delete expr1;
		delete expr2;
	}
};

class AndExpression: public Expression
{
	Expression *expr1;
	Expression *expr2;

public:
	AndExpression() = delete;

	AndExpression(Expression *expr1, Expression *expr2):expr1(expr1), expr2(expr2){};

	bool interpret(std::string context){
		return expr1->interpret(context) && expr2->interpret(context);
	}

	~AndExpression(){
		delete expr1;
		delete expr2;
	}
};

//Step 3

//Rule: Robert and John are male
static Expression * getMaleExpression()
{
	Expression *robert = new TerminalExpression("Robert");
	Expression *john = new TerminalExpression("John");

	return new OrExpression(robert, john);
}

//Rule: Julie is a married women
static Expression * getMarriedWomanExpression()
{
	Expression *julie = new TerminalExpression("Julie");
	Expression *married = new TerminalExpression("Married");

	return new AndExpression(julie, married);
}

int main()
{
	std::unique_ptr<Expression> isMale(getMaleExpression());

	std::unique_ptr<Expression> isMarriedWoman(getMarriedWomanExpression());

	std::cout << "John is male? " << (isMale->interpret("John") ? "yes" : "no") << std::endl;

	std::cout << "Julie is a married woman? " << (isMarriedWoman->interpret("Married Julie") ? "yes" : "no") << std::endl;

	return 0;
}
