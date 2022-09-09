#include <iostream>

struct ComputerPartVisitor;

//Step 1
struct ComputerPart
{
	virtual void accept(ComputerPartVisitor *computerPartVisitor) = 0;
	virtual ~ComputerPart() = 0;
};
ComputerPart::~ComputerPart(){};

//Step 2
class Keyboard: public ComputerPart
{
public:
	void accept(ComputerPartVisitor *computerPartVisitor);
};

class Monitor: public ComputerPart
{
public:
	void accept(ComputerPartVisitor *computerPartVisitor);
};

class Mouse: public ComputerPart
{
public:
	void accept(ComputerPartVisitor *computerPartVisitor);
};

class Computer: public ComputerPart
{
	ComputerPart *parts[3] = {
		new Mouse,
		new Keyboard,
		new Monitor
	};

public:
	void accept(ComputerPartVisitor *computerPartVisitor);
};

//Step 3
struct ComputerPartVisitor
{
	virtual void visit(Computer *computer) = 0;
	virtual void visit(Mouse *mouse) = 0;
	virtual void visit(Keyboard *keyboard) = 0;
	virtual void visit(Monitor *monitor) = 0;
	virtual ~ComputerPartVisitor() = 0;
};
ComputerPartVisitor::~ComputerPartVisitor(){};

void Computer::accept(ComputerPartVisitor *computerPartVisitor)
{
	for(ComputerPart *part : parts){
		part->accept(computerPartVisitor);
	}

	computerPartVisitor->visit(this);
};

void Mouse::accept(ComputerPartVisitor *computerPartVisitor) {
	computerPartVisitor->visit(this);
};

void Keyboard::accept(ComputerPartVisitor *computerPartVisitor) {
	computerPartVisitor->visit(this);
};

void Monitor::accept(ComputerPartVisitor *computerPartVisitor) {
	computerPartVisitor->visit(this);
};

//Step 4

class ComputerPartDisplayVisitor: public ComputerPartVisitor
{
public:
	void visit(Computer *computer) override {
		std::cout << "Displaying Computer." << std::endl;
	}

	void visit(Mouse *mouse) override {
		std::cout << "Displaying Mouse." << std::endl;
	}

	void visit(Keyboard *keyboard) override {
		std::cout << "Displaying Keyboard." << std::endl;
	}

	void visit(Monitor *monitor) override {
		std::cout << "Displaying Monitor." << std::endl;
	}
};

//Step 5
int main(int argc, char *argv[])
{
	ComputerPart *computer = new Computer;
	computer->accept(new ComputerPartDisplayVisitor());
}


