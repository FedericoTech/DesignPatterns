#include <iostream>
#include <memory>

class GlobalClass
{
	int m_value;

	static std::shared_ptr<GlobalClass> s_instance;

	GlobalClass(int v = 0) //we make the constructor private
	{
		m_value = v;
	}

	GlobalClass(GlobalClass const &) = delete; //we get rid of the copy constructor

	GlobalClass& operator=(GlobalClass const &) = delete;	//we get rid of the copy assignation

public:
	int get_value(){ return m_value; }

	void set_value(int v) { m_value = v;}

	static std::shared_ptr<GlobalClass> instance()
	{
		if(s_instance == nullptr){
			s_instance = std::move(std::shared_ptr<GlobalClass>(new GlobalClass));
		}

		return s_instance;
	}
};

std::shared_ptr<GlobalClass> GlobalClass::s_instance = nullptr;

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
	//we can get raw pointers from the instance
	GlobalClass *ello = GlobalClass::instance().get();
	GlobalClass *ello2 = GlobalClass::instance().get();
	//and the raw pointers point to the same instance
	std::cout << "ello == ello2 ? " << (ello == ello2) << std::endl;

	std::cout << __FUNCTION__ << ": global_ptr is " << GlobalClass::instance()->get_value() << std::endl;
	foo();
	bar();

	return 0;
}
