#include <iostream>
#include <list>
#include <memory>

//Step 1
class Student
{
	std::string name;
	int rollNo;

public:
	Student(std::string name, int rollNo):name(name), rollNo(rollNo) {};

	std::string getName()
	{
		return name;
	}

	void setName(std::string name)
	{
		this->name = name;
	}

	int getRollNo()
	{
		return rollNo;
	}

	void setRollNo(int rollNo)
	{
		this->rollNo = rollNo;
	}
};

class StudentList: public std::list<Student>
{
public:
	StudentList::iterator get(int index)
	{
		auto it = this->begin();
		std::advance(it, index);
		return it;
	}
};

//Step 2
struct StudentDao {
	virtual StudentList getAllStudents() = 0;
	virtual Student getStudent(int rollNo) = 0;
	virtual void updateStudent(Student student) = 0;
	virtual void deleteStudent(Student student) = 0;
	virtual ~StudentDao() = 0;
};
StudentDao::~StudentDao(){};

//Step 3
class StudentDaoImpl: public StudentDao
{
	StudentList students;

public:
	StudentDaoImpl(std::initializer_list<Student> list)
	{
		for(Student st: list){
			students.push_back(std::move(st));
		}
	}

	void deleteStudent(Student student) override {


		std::list<Student>::iterator it = students.get(student.getRollNo());
		students.erase(it);

		std::cout << "Student: Roll No " << student.getRollNo() << ", deleted from database" << std::endl;
	}

	StudentList getAllStudents() override {
		return students;
	}

	Student getStudent(int rollNo) override {
		auto it = students.get(rollNo);
		return *it;
	}

	void updateStudent(Student student) override {
		StudentList::iterator it = students.get(student.getRollNo());
		it->setName(student.getName());

		std::cout << "Student: Roll No " << student.getRollNo() << ", updated in the database" << std::endl;
	}
};

//Step 4
int main(int argc, char *argv[])
{
	std::unique_ptr<StudentDao>studentDao = std::make_unique<StudentDaoImpl>(StudentDaoImpl {{"Robert", 0}, {"John", 1}});

	for(Student student: studentDao->getAllStudents()){
		std::cout << "Student: [RollNo : " << student.getRollNo() << ", Name : " << student.getName() << " ]" << std::endl;
	}

	Student student = *(studentDao->getAllStudents().get(0));

	student.setName("Michael");
	studentDao->updateStudent(student);

	student = studentDao->getStudent(0);

	std::cout << "Student: [RollNo : " << student.getRollNo() << ", Name: " << student.getName() << " ]" << std::endl;

	return 0;
}
