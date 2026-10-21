/*virtual - override 연습; class pointer연습*/

#include <iostream>
#include <stdlib.h>
#include <vector>



/*
* error student와 teacher 값이 마지막 값 동일한 출력 문제 해결할것
*/

using namespace std; 

class Person
{
	public:
		Person();
		Person(string pname, int page);
		string getName() const;
		virtual void setName( string name );
		virtual void setAge( int age );
		int getAge() const;
		void print() const;
        virtual void eat(); 
        virtual ~Person() = default; 

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

void Person::eat()
{
    cout << "every human eats" << endl; 
}

// student class 
class Student : public Person
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
   void eat() override { cout << "Price is 3.1 eur" <<endl;}
}; 

// teacher class 
class Teacher : public Person
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
    void eat() override { cout << "Price is 11 eur" <<endl;}

}; 


int main()
{
    vector<unique_ptr<Person>> queue; // smart pointer 
    int num = 5; 

    for (int i =0; i < num; i++)
    {
        char a = 65 + i;  
        string name(1, a); // 문자열 형식으로 저장하는 방법 

        unique_ptr<Person> person; // pointer대신 smart_pointer 사용 memory leak 문제 해결하는 것 

        if(i%2 == 0)
        {
            person = make_unique<Student>(); 
        }
        else 
        {
            person = make_unique<Teacher>(); 
        }

        person->setName(name); 
        person->setAge(i); 
        queue.push_back(move(person)); // std::move elements locate new region // 생명주기 문제였으므로 옯기는 방법 
    }

    for(const auto& p : queue)
    {
        p->print(); 
        p->eat(); 
    }

    return 0; 
}