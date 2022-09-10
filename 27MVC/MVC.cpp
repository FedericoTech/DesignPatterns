#include <iostream>

//Step 1, This is the model
class Student
{
	std::string rollNo;
	std::string name;

public:
	std::string getRollNo()
	{
		return rollNo;
	}

	void setRollNo(std::string rollNo)
	{
		this->rollNo = rollNo;
	}

	std::string getName()
	{
		return name;
	}

	void setName(std::string name)
	{
		this->name = name;
	}
};

//Step 2, View
class StudentView
{
public:
	void printStudentDetails(std::string studentName, std::string studentRollNo)
	{
		std::cout << "Strudent: " << std::endl;

		std::cout << "Name: " << studentName << std::endl;

		std::cout << "Roll No: " << studentRollNo << std::endl;
	}
};

//Step 3, Controller
class StudentController
{
	Student *model;
	StudentView *view;
public:
	StudentController(Student *model, StudentView *view):model(model), view(view){}

	void setStudentName(std::string name)
	{
		model->setName(name);
	}

	std::string getStudentName()
	{
		return model->getName();
	}

	void setStudentRollNo(std::string rollNo)
	{
		model->setRollNo(rollNo);
	}

	std::string getStudentRollNo()
	{
		return model->getRollNo();
	}

	void updateView()
	{
		view->printStudentDetails(model->getName(), model->getRollNo());
	}
};

static Student *retrieveStudentFromDatabase()
{
	Student *student = new Student();
	student->setName("Robert");
	student->setRollNo("10");

	return student;
}

//Step 4
int main(int argc, char *argv[])
{
	//fetch student record based on his roll no from the database
	Student model = *retrieveStudentFromDatabase();

	//Create a view : to write student details on console
	StudentView view;

	StudentController controller(&model, &view);

	controller.updateView();

	//update model data
	controller.setStudentName("John");

	controller.updateView();

}
