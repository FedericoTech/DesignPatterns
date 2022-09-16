#include <iostream>
#include <list>
#include <algorithm>
#include <memory>

//Step 1

class Person
{
	std::string name;
	std::string gender;
	std::string maritalStatus;

public:
	Person(std::string name, std::string gender, std::string maritalStatus)
		:name(name),
		 gender(gender),
		 maritalStatus(maritalStatus){}

	std::string inline getName() const {return name;}

	std::string inline getGender() const {return gender;}

	std::string inline getMaritalStatus() const {return maritalStatus;}

	bool operator == (Person const &p){
		return p.name.compare(this->name) == 0
			&& p.gender.compare(this->gender) == 0
			&& p.maritalStatus.compare(this->maritalStatus) == 0;
	}

	friend std::ostream& operator << (std::ostream& os, const Person p);
};

std::ostream& operator << (std::ostream &os, const Person p)
{
	os << "Person : [ Name : " << p.getName()
		<< ", Gender : " << p.getGender()
		<< ", Marital Status : " << p.getMaritalStatus()
		<< " ]";
	return os;
}

//Step 2

struct Criteria {
	virtual std::list<Person> meetCriteria(std::list<Person> &persons) = 0;
	virtual ~Criteria() = 0;
};
Criteria::~Criteria(){};

//Step 3

class CriteriaMale: public Criteria
{
public:
	std::list<Person> meetCriteria(std::list<Person> &persons){
		std::list<Person> malePersons;

		for(Person person: persons){
			std::string gender = person.getGender();

			std::transform(gender.begin(), gender.end(), gender.begin(), ::toupper);

			if(gender.compare("MALE") == 0){
				malePersons.push_back(person);
			}
		}

		return std::move(malePersons);
	}
};

class CriteriaFemale: public Criteria
{
public:
	std::list<Person> meetCriteria(std::list<Person> &persons){
		std::list<Person> femalePersons;

		for(Person person: persons){
			std::string gender = person.getGender();

			std::transform(gender.begin(), gender.end(), gender.begin(), ::toupper);

			if(gender.compare("FEMALE") == 0){
				femalePersons.push_back(person);
			}
		}

		return std::move(femalePersons);
	}
};

class CriteriaSingle: public Criteria
{
public:
	std::list<Person> meetCriteria(std::list<Person> &persons){
		std::list<Person> singlePersons;

		for(Person person: persons){
			std::string maritalStatus = person.getMaritalStatus();

			std::transform(maritalStatus.begin(), maritalStatus.end(), maritalStatus.begin(), ::toupper);

			if(maritalStatus.compare("SINGLE") == 0){
				singlePersons.push_back(person);
			}
		}

		return std::move(singlePersons);
	}
};

class AndCriteria: public Criteria
{
	std::shared_ptr<Criteria> criteria;
	std::shared_ptr<Criteria> otherCriteria;
public:

	AndCriteria(std::shared_ptr<Criteria> criteria, std::shared_ptr<Criteria> otherCriteria)
		: criteria(criteria),
		  otherCriteria(otherCriteria){};

	std::list<Person> meetCriteria(std::list<Person> &persons){
		std::list<Person> firstCriteriaPersons = criteria->meetCriteria(persons);

		return std::move(otherCriteria->meetCriteria(firstCriteriaPersons));
	}
};

class OrCriteria: public Criteria
{
	std::shared_ptr<Criteria> criteria;
	std::shared_ptr<Criteria> otherCriteria;

public:
	OrCriteria(std::shared_ptr<Criteria> criteria, std::shared_ptr<Criteria> otherCriteria)
		: criteria(criteria),
		  otherCriteria(otherCriteria){};

	std::list<Person> meetCriteria(std::list<Person> &persons){
		std::list<Person> firstCriteriaItems = criteria->meetCriteria(persons);
		std::list<Person> otherCriteriaItems = otherCriteria->meetCriteria(persons);

		for(Person person: otherCriteriaItems){

			if(std::find(firstCriteriaItems.begin(), firstCriteriaItems.end(), person) == firstCriteriaItems.end()){
				firstCriteriaItems.push_back(person);
			}

		}

		return std::move(firstCriteriaItems);
	}
};

//Step 4

void printPersons(const std::list<Person> persons){
	for(Person person : persons){
		std::cout << person << std::endl;
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

	std::shared_ptr<Criteria> male = std::make_shared<CriteriaMale>();
	std::shared_ptr<Criteria> female = std::make_shared<CriteriaFemale>();
	std::shared_ptr<Criteria> single = std::make_shared<CriteriaSingle>();

	std::unique_ptr<Criteria> singleMale = std::make_unique<AndCriteria>(single, male);
	std::unique_ptr<Criteria> singleOrFemale = std::make_unique<OrCriteria>(single, female);


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
