#include <iostream>
#include <list>
using namespace std; 

class Course 
{
    public : 
    string name; 
    string code; 
    int credits; 

    Course(string n="", string cd="", int cr=0)
    {
        name = n; 
        code = cd; 
        credits = cr; 
    }
}; 

class Student 
{
    public : 
    string name; 
    string studentNumber; 
    int credits; 

    Student(string n = "", string sn ="", int cr =0) // 임시값 설정 설정해 줄 것 (compiler 설정)
    {
        name = n; 
        studentNumber = sn; 
        credits = cr; 
    }
}; 

class StudyRecord 
{
    public : 
    Student student; 
    Course course; 
    int grade; 

    StudyRecord(Student s, Course co, int gr) // student, course에 초기화 하지 않으면 할당 문제 err
    {
        student = s; 
        course = co; 
        grade = gr; 
    }
}; 

int main()
{
    list<Student> students;
    students.push_back(Student("a", "1", 1)); 
    students.push_back(Student("b", "2", 2));
    students.push_back(Student("c", "3", 3));
    students.push_back(Student("d", "4", 4));

    Course oop("Object-Oriented Programming", "PO00ED10-3004", 5);  

    list<StudyRecord> records; 

    for(Student s : students)
    {
        records.push_back(StudyRecord(s, oop, 3));
    }

    for(StudyRecord sr : records)
    {
        cout << sr.student.name << endl;   
    }

    return 0; 
}