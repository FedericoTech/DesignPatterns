#include <iostream>
#include <list>
#include <algorithm>

//Step 1

class Person
{
	std::string name;
	std::string gender;
	std::string maritalStatus;

public:
	Person(std::string name, std::string gender, std::string maritalStatus):name(name), gender(gender), maritalStatus(maritalStatus){}

	std::string inline getName(){return name;}

	std::string inline getGender(){return gender;}

	std::string inline getMaritalStatus(){return maritalStatus;}

	bool operator == (Person const &p){
		return p.name.compare(this->name) == 0
			&& p.gender.compare(this->gender) == 0
			&& p.maritalStatus.compare(this->maritalStatus) == 0;
	}
};

//Step 2

struct Criteria {
	virtual std::list<Person> meetCriteria(std::list<Person> persons) = 0;
	virtual ~Criteria() {}
};

//Step 3

class CriteriaMale: public Criteria
{
public:
	std::list<Person> meetCriteria(std::list<Person> persons){
		std::list<Person> malePersons;

		for(Person person: persons){
			std::string gender = person.getGender();

			std::transform(gender.begin(), gender.end(), gender.begin(), ::toupper);

			if(gender.compare("MALE") == 0){
				malePersons.push_back(person);
			}
		}

		return malePersons;
	}
};

class CriteriaFemale: public Criteria
{
public:
	std::list<Person> meetCriteria(std::list<Person> persons){
		std::list<Person> femalePersons;

		for(Person person: persons){
			std::string gender = person.getGender();

			std::transform(gender.begin(), gender.end(), gender.begin(), ::toupper);

			if(gender.compare("FEMALE") == 0){
				femalePersons.push_back(person);
			}
		}

		return femalePersons;
	}
};

class CriteriaSingle: public Criteria
{
public:
	std::list<Person> meetCriteria(std::list<Person> persons){
		std::list<Person> singlePersons;

		for(Person person: persons){
			std::string maritalStatus = person.getMaritalStatus();

			std::transform(maritalStatus.begin(), maritalStatus.end(), maritalStatus.begin(), ::toupper);

			if(maritalStatus.compare("SINGLE") == 0){
				singlePersons.push_back(person);
			}
		}

		return singlePersons;
	}
};

class AndCriteria: public Criteria
{
	Criteria *criteria;
	Criteria *otherCriteria;
public:

	AndCriteria(Criteria *criteria, Criteria *otherCriteria): criteria(criteria), otherCriteria(otherCriteria){};

	std::list<Person> meetCriteria(std::list<Person> persons){
		std::list<Person> firstCriteriaPersons = criteria->meetCriteria(persons);

		return otherCriteria->meetCriteria(firstCriteriaPersons);
	}
};

class OrCriteria: public Criteria
{
	Criteria *criteria;
	Criteria *otherCriteria;
public:

	OrCriteria(Criteria *criteria, Criteria *otherCriteria): criteria(criteria), otherCriteria(otherCriteria){};

	std::list<Person> meetCriteria(std::list<Person> persons){
		std::list<Person> firstCriteriaItems = criteria->meetCriteria(persons);
		std::list<Person> otherCriteriaItems = otherCriteria->meetCriteria(persons);

		for(Person person: otherCriteriaItems){

			if(std::find(firstCriteriaItems.begin(), firstCriteriaItems.end(), person) == firstCriteriaItems.end()){
				firstCriteriaItems.push_back(person);
			}

		}

		return firstCriteriaItems;
	}
};

//Step 4

void printPersons(std::list<Person> persons){
	for(Person person : persons){
		std::cout << "Person : [ Name : " << person.getName()
			<< ", Gender : " << person.getGender()
			<< ", Marital Status : " << person.getMaritalStatus()
			<< " ]" << std::endl;
	}
}

int main()
{
	std::list<Person> persons;

	persons.push_back(Person("Robert", "Male", "Single"));
	persons.push_back(Person("John", "Male", "Married"));
	persons.push_back(Person("Laura", "Female", "Married"));
	persons.push_back(Person("Diana", "Female", "Single"));
	persons.push_back(Person("Mike", "Male", "Single"));
	persons.push_back(Person("Bobby", "Male", "Single"));

	Criteria *male = new CriteriaMale();
	Criteria *female = new CriteriaFemale();
	Criteria *single = new CriteriaSingle();
	Criteria *singleMale = new AndCriteria(single, male);
	Criteria *singleOrFemale = new OrCriteria(single, female);

	std::cout << "Males: " << std::endl;
	printPersons(male->meetCriteria(persons));

	std::cout << "Females: " << std::endl;
	printPersons(female->meetCriteria(persons));

	std::cout << "Single Males: " << std::endl;
	printPersons(singleMale->meetCriteria(persons));

	std::cout << "Single Or Females: " << std::endl;
	printPersons(singleOrFemale->meetCriteria(persons));

	return 0;
}
