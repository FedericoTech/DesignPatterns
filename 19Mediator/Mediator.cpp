#include <iostream>
#include <ctime>
#include <cstring>



class ChatRoom;	//the declaration is down bellow

//Step 1

class User
{
	std::string name;

public:
	std::string getName()
	{
		return name;
	};

	void setName(std::string name)
	{
		this->name = name;
	};

	User(std::string name):name(name){};

	void setMessage(std::string); //we are not implementing here but after ChatRoom declaration
};

//Step 2
class ChatRoom
{
public:
	static void showMessage(User *user, std::string message){
		time_t now = time(0);

		char* dt = strtok(ctime(&now), "\n"); //strok to remove the \n

		std::cout << dt << " [" << user->getName() << "] : " << message << std::endl;
	}
};

//now we implement the method
void User::setMessage(std::string message)
{
	ChatRoom::showMessage(this, message);
}

//Step 3
int main() {
	User *robert = new User("Robert");
	User *john = new User("John");

	robert->setMessage("Hi! John!");
	john->setMessage("Hello! Robert!");
}


