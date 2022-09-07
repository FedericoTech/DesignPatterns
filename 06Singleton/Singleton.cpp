#include <iostream>

class GlobalClass
{
	int m_value;
	static GlobalClass *s_instance;

	GlobalClass(int v = 0) //we make the constructor private
	{
		m_value = v;
	}

	void operator = (GlobalClass const&) = delete;	//we get rid of the copy constructor

public:
	int get_value(){ return m_value; }

	void set_value(int v) { m_value = v;}

	static GlobalClass *instance()
	{
		if(!s_instance){
			s_instance = new GlobalClass;
		}

		return s_instance;
	}
};

GlobalClass *GlobalClass::s_instance = 0;

void foo(void){
	GlobalClass::instance()->set_value(1);
	std::cout << __FUNCTION__ << ": global_ptr is " << GlobalClass::instance()->get_value() << std::endl;
}

void bar(void){
	GlobalClass::instance()->set_value(2);
	std::cout << __FUNCTION__ << ": global_ptr is " << GlobalClass::instance()->get_value() << std::endl;
}

int main()
{
	std::cout << __FUNCTION__ << ": global_ptr is " << GlobalClass::instance()->get_value() << std::endl;
	foo();
	bar();

	return 0;
}
