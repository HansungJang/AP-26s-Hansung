#include<iostream>
using namespace std; 

/*
다중상속 : permission based roles 
*/

/*Part#1 : Base Class*/
class Person
{
        public :
        string name; 
        int age; 
        Person() : name(""), age(0) {}; 
        void printInfo(){cout << "name : " << name << ", " << "age : " << age <<endl;}
        ~Person(){}

};

class Vehicle
{
    public :
        string brand; 
        int maxSpeed; 
        Vehicle() : brand(""), maxSpeed(0) {}; 
        virtual void printInfo(){cout << "brand : " << brand << ", " << "maxSpeed : " << maxSpeed <<endl;}
        ~Vehicle(){}
};

class Teacher
{
    public :
        bool canTeacherDriving; 
        bool canTeacherFlying; 
        Teacher() : canTeacherDriving(false), canTeacherFlying(false){}; 
        void printPermission()
        {
            if(canTeacherDriving) cout << "I can teach Driving" << endl; 
            if(canTeacherFlying) cout << "I can teach Flying" << endl; 
        }
        ~Teacher(){}
};

/*Part#2 : Derived vehicle*/
class Car : public Vehicle
{
    public : 
        int numDoors; 
        Car(): numDoors(0) {}; 
            void printInfo() override
            {
                cout << "numDoors : " << numDoors << endl; 
            }
};

class Airplane : public Vehicle
{
    public : 
        double wingSpan; 
        Airplane() : wingSpan(0) {}; 
        virtual void printInfo() override
        {
            cout << "wingSpan : " << wingSpan << endl; 
        }
};

/*Part#3 : Driver Classes*/
class Driver : public Person
{
    public :
        Vehicle* vehicle;  
        Driver(){}; 
        void drive()
        {
            if(vehicle == nullptr) return; 
           if(typeid(*vehicle) == typeid(Car)) cout << "Driver is Driving" << endl; 
           if(typeid(*vehicle) == typeid(Airplane)) cout << "Driver is Flying" << endl; 

        //    if(dynamic_cast<Car*>(vehicle)) cout << "Driver is Driving" << endl; 
        //    if(dynamic_cast<Airplane*>(vehicle)) cout << "Driver is Flying" << endl; 

    }
        virtual void printInfo()
        {
            Person::printInfo();
            cout << "vehicle type : ";  
            (typeid(*vehicle) == typeid(Car)) ? cout << "Car " << endl : cout << "Airplane " << endl;  
        }
        ~Driver(){}
};

/*Part#4 : Multiple Inheritance*/
class DriverInstructor : public Person, public Teacher
{
    public: 
    DriverInstructor(){}
    void instructDriving()
    {
        if(canTeacherDriving) cout << "Enroll Driving Class" <<endl;          
    }
    void instructFlying()
    {
        if(canTeacherFlying) cout << "Enroll Flight Class" <<endl;          
    }
    virtual void printInfo()
    {
        Person::printInfo(); 
        Teacher::printPermission(); 
    }
};

/*Task#5 : Implements*/
int main()
{
    Car mycar;
    Airplane myplane; 
    Driver driver1, driver2; // driver1(Car), driver2(airplane)
    DriverInstructor teacher;  

    mycar.brand = "KIA"; 
    mycar.maxSpeed = 180; 
    mycar.numDoors = 4;
    
    myplane.brand = "Mercedens-Benz";
    myplane.maxSpeed = 360; 
    myplane.wingSpan = 380;


    driver1.age = 18; 
    driver1.name ="aaa"; 
    driver1.vehicle = &mycar; 

    driver2.age = 22; 
    driver2.name ="ddd"; 
    driver2.vehicle = &myplane;
    
    teacher.age = 20; 
    teacher.name ="ccc"; 
    teacher.canTeacherDriving = true; 
    teacher.canTeacherFlying = true; 
    
    // driver.printinfo
    driver1.printInfo(); 
    driver2.printInfo();
    // driver drive
    driver1.drive();
    driver2.drive(); 
    // instructor printinfo
    teacher.printInfo(); 
    // instructor instructdriving
    teacher.instructDriving();
    // instructor instructflying
    teacher.instructFlying();

    return 0; 
}
// class datatype 못받음  
// Vehicle의 virtual 가상함수 선언 -> polymorphic 상태 전환 datatype listen하도록 만들어줌 