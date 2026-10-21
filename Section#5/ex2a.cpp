#include <iostream>
#include <stdlib.h>
using namespace std; 

class Person
{
	public:
		Person();
		Person(string pname, int page);
		string getName() const;
		void setName( string name );
		void setAge( int age );
		int getAge() const;
		void print() const;

	private:
		string name;
		int age; //If 0 is unknown.
};

Person::Person()
{
	name = "";
	age = 0;
}

Person::Person (string pname, int page)
{
	name = pname;

	if( page >= 0 && page < 120 ) {
        age = page;
	}
	else {
        throw std::invalid_argument( "Invalid Age" );
	}
}

string Person::getName() const
{
	return name;
}

int Person::getAge() const
{
	return age;
}

void Person::print() const
{
	cout << "Name : " << name << endl;
	cout << "Age : " << age << endl;
}

void Person::setName( string name )
{
	this->name = name;
}

void Person::setAge( int age )
{
    if( age >= 0 && age < 120 ) {
        this->age = age;
    }
    else {
        throw std::invalid_argument( "Invalid Age" );
    }
}

// student class 
class Student : Person
{
    private :
        int studentNumber; 
        int studyPoints; 

    public : 
    Student(): studentNumber(0), studyPoints(0){}

    void setStudentNumber(int num){ studentNumber = num;  }
    void setStudyPoints(int num) { studyPoints = num;  }
   int getStudentNumber() {return  studentNumber;}
   int getStudyPoints() {return studyPoints; }
}; 

// teacher class 
class Teacher : Person
{
    private :
        int workRoom; 
        float teachingYears; 

    public : 
    Teacher(): workRoom(0), teachingYears(0){}

    void setworkRoom(int num){ workRoom = num;  }
    void setteachingYears(int num) { teachingYears = num;  }
   int getworkRoom() {return  workRoom;}
   float getteachingYears() {return teachingYears; }
}; 