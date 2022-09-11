#include <iostream>
#include <list>

//Step 1
class StudentVO
{
	std::string name;
	int rollNo;
public:
	StudentVO(std::string name, int rollNo):name(name), rollNo(rollNo){};

	std::string getName(){ return name; };

	void setName(std::string name){ this->name = name; }

	int getRollNo(){ return rollNo; };

	void setRollNo(int name){ this->rollNo = rollNo; }
};

class StudentVOList: public std::list<StudentVO>
{
public:
	StudentVOList::iterator get(int index)
	{
		StudentVOList::iterator it = this->begin();
		std::advance(it, index);

		return it;
	}
};

//Step 2
class StudentBO
{
	//List is working as a database
	StudentVOList students;
public:
	StudentBO()
	{
		StudentVO student1("Robert", 0);
		StudentVO student2("John", 1);

		students.push_back(student1);
		students.push_back(student2);
	}

	void deleteStudent(StudentVO student)
	{
		students.erase(students.get(student.getRollNo()));

		std::cout << "Student: Roll No " << student.getRollNo() << ", deleted from database" << std::endl;
	}

	StudentVOList getAllStudents()
	{
		return students;
	}

	StudentVO getStudent(int rollNo)
	{
		return *students.get(rollNo);
	}

	void updateStudent(StudentVO student)
	{
		students.get(student.getRollNo())->setName(student.getName());

		std::cout << "Student: Roll No " << student.getRollNo() << ", updated in the database" << std::endl;
	}
};

//Step 3
int main(int argc, char *argv[])
{
	StudentBO studentBusinessObject;

	for(StudentVO student: studentBusinessObject.getAllStudents()){
		std::cout << "Student: [RollNo : " << student.getRollNo() << ", Name : " << student.getName() << " ]" << std::endl;
	}

	//update student
	StudentVO student = *studentBusinessObject.getAllStudents().get(0);
	student.setName("Michael");

	studentBusinessObject.updateStudent(student);

	//get the student
	student = studentBusinessObject.getStudent(0);

	std::cout << "Student: [RollNo : " << student.getRollNo() << ", Name : " << student.getName() << "] " << std::endl;

	return 0;
}
