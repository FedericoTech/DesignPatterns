#include <iostream>
#include <list>
#include <ostream>

//Step 1

class Employee
{
	std::string name;
	std::string dept;
	int salary;
	std::list<Employee> subordinates;
public:

	Employee(std::string name, std::string dept, int sal):name(name), dept(dept), salary(sal){}

	void add(Employee &e)
	{
		subordinates.push_back(e);
	}

	void remove(Employee &e)
	{
		subordinates.remove(e);
	}

	std::list<Employee> getSubordinates()
	{
		return subordinates;
	}

	bool operator == (const Employee &e) {
		return e.name == this->name
			&& e.dept == (*this).dept
			&& e.salary == this->salary;
	}

	friend std::ostream& operator << (std::ostream& os, const Employee e);
};

std::ostream& operator << (std::ostream &os, const Employee e){
	os << "Employee :[ Name : " << e.name
		<< ", dept : " << e.dept
		<< ", salary : " << (&e)->salary
		<< " ]";
	return os;
}

//Step 2
int main()
{

	Employee CEO("John", "CEO", 30000);

	Employee headSales = Employee("Robert", "Head Sales", 20000);

	Employee headMarketing = {"Michael", "HeadMarketing", 20000};

	Employee clerk1("Laura", "Marketing", 10000);
	Employee clerk2 = {"Bob", "Marketing", 10000};

	Employee salesExecutive1 = Employee("Richard", "Sales", 10000);
	Employee salesExecutive2("Rob", "Sales", 10000);

	headSales.add(salesExecutive1);
	headSales.add(salesExecutive2);

	headMarketing.add(clerk1);
	headMarketing.add(clerk2);

	CEO.add(headSales);
	CEO.add(headMarketing);

	//print all employees of the organization
	std::cout << CEO << std::endl;

	for(Employee headEmployee : CEO.getSubordinates()){
		std::cout << headEmployee << std::endl;

		for(Employee employee : headEmployee.getSubordinates()){
			std::cout << employee << std::endl;
		}
	}

	return 0;
}
