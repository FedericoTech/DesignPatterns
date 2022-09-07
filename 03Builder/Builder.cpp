#include <iostream>
#include <cstdio>
#include <cstring>

enum PersistenceType
{
	File, Queue, Pathway
};

struct PersistenceAttribute
{
	PersistenceType type;
	char value[30];
};

class DistWorkPackage
{
public:
	DistWorkPackage(const char *type){
		sprintf(_desc, "Distributed Work Package for: %s", type);
	}

	void setFile(const char *f, const char *v){
		sprintf(_temp, "\n File(%s): %s", f, v);
		strcat(_desc, _temp);
	}

	void setQueue(const char *q, const char *v){
		sprintf(_temp, "\n Queue(%s): %s", q, v);
		strcat(_desc, _temp);
	}

	void setPathway(const char *p, const char *v){
		sprintf(_temp, "\n Pathway(%s): %s", p, v);
		strcat(_desc, _temp);
	}

	const char *getstate()
	{
		return _desc;
	}

private:
	char _desc[200], _temp[80];
};

struct Builder
{
	virtual void configureFile(const char *) = 0;
	virtual void configureQueue(const char *) = 0;
	virtual void configurePathway(const char *) = 0;
	virtual ~Builder() = 0;

	DistWorkPackage *getResult()
	{
		return _result;
	}

protected:
	DistWorkPackage *_result;
};

Builder::~Builder(){};

class UnixBuilder: public Builder
{
public:
	UnixBuilder()
	{
		_result = new DistWorkPackage("Unix");
	}

	void configureFile(const char *name){
		_result->setFile("flatFile", name);
	}

	void configureQueue(const char *queue){
		_result->setQueue("FIFO", queue);
	}

	void configurePathway(const char *type){
		_result->setPathway("thread", type);
	}
};

class VmsBuilder: public Builder
{
public:
	VmsBuilder()
	{
		_result = new DistWorkPackage("Vms");
	}

	void configureFile(const char *name){
		_result->setFile("ISAM", name);
	}

	void configureQueue(const char *queue){
		_result->setQueue("priority", queue);
	}

	void configurePathway(const char *type){
		_result->setPathway("LWP", type);
	}
};

class Reader
{
public:
	void setBuilder(Builder *b){
		_builder = b;
	}

	void construct(PersistenceAttribute[], int);
private:
	Builder *_builder;
};

void Reader::construct(PersistenceAttribute list[], int num){
	for(int i = 0; i < num; i++){
		if(list[i].type == File){
			_builder->configureFile(list[i].value);
		} else if(list[i].type == Queue){
			_builder->configureQueue(list[i].value);
		} else if(list[i].type == Pathway){
			_builder->configurePathway(list[i].value);
		}
	}
}

const int NUM_ENTRIES = 6;

PersistenceAttribute input[NUM_ENTRIES] = {
	{File, "state.data"},
	{File, "config.sys"},
	{Queue, "compute"},
	{Queue, "log"},
	{Pathway, "authentication"},
	{Pathway, "error processing"}
};

int main()
{
	UnixBuilder unixBuilder;

	VmsBuilder vmsBuilder;

	Reader reader;

	reader.setBuilder(&unixBuilder);
	reader.construct(input, NUM_ENTRIES);
	std::cout << unixBuilder.getResult()->getstate() << std::endl;

	reader.setBuilder(&vmsBuilder);
	reader.construct(input, NUM_ENTRIES);
	std::cout << vmsBuilder.getResult()->getstate() << std::endl;
}

