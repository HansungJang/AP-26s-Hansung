// struct의 메모리 사이즈 크기가 균일해야 

// #topic 
// - 구조체로 학생 대아토 저장하는 데이터 저장 보관소 만든다고 생각해보자 
// - 공간이 충분& initial 하면 malloc () / 공간이 부족하면 realloc 으로 공간 확보 

// #task 
// 1) struct을 사용하여 (name, studentID, address, credits) 만듬 
// 2) new or malloc 활용하여 임의 size 만듬 
// 3) while(1) loop를 통해서 사용자 입력받음 (입력 계속 받을지 y/n 입력 확인)
// 4) size범위에 도달하면 realloc함수를 사용하여 size * 2 사용
// 5) n 입력 -> while loop 나오고, 입력받은 배열 모두 출력후 종료 (free 잊지 말것)

#include<iostream>
#include<sstream>
#include<string>
using namespace std; 


typedef struct studentInfo 
{
    string* name; 
    int studentNumber; 
    string* address; 
    int credits; 
} studentInfo; 

int main()
{
    studentInfo* s_storage; 
    int size = 3; 
    s_storage = (studentInfo*)malloc(size * sizeof(studentInfo));
    char inputState; 
    int storageAmount = 0; 

    string input_name;
    int input_studentNumber; 
    string input_address; 
    int input_credits;  

    do{
        cout << "Do you want insert student Info [y/n] : "; 
        cin >> inputState;
        cin.ignore();

        if(inputState == 'n' || inputState == 'N') break; 
        if(storageAmount >= size -1 )
        {
            int newsize = 2 * size;
            studentInfo* news_storage;  
            news_storage = (studentInfo*)realloc(s_storage, (newsize * sizeof(studentInfo)));
            
            s_storage = news_storage; 
            size = newsize; 
        }

        cout << "Student Name : "; 
        getline(cin, input_name); 
        cout << "Student Number : "; 
        cin >> input_studentNumber; 
        cin.ignore(); 
        cout << "Student Address : "; 
        getline(cin, input_address);
        cout << "Student Credits : ";  
        cin >> input_credits;

        s_storage[storageAmount].name = new string(input_name); 
        s_storage[storageAmount].studentNumber = input_studentNumber; 
        s_storage[storageAmount].address = new string(input_address); 
        s_storage[storageAmount].credits = input_credits; 

        storageAmount += 1; 

    }while(1); 

    for(int i =0; i < storageAmount; i++)
    {
        cout << "Student #" << i+1 << endl; 
        cout << "Student Name : " << *(s_storage[i].name) << endl; 
        cout << "Student Number : " << s_storage[i].studentNumber << endl; 
        cout << "Student Address : " << *(s_storage[i].address) << endl; 
        cout << "Student Credits : " << s_storage[i].credits << endl << endl; 
    }

    for(int  i =0; i< storageAmount; i++)
    {
        delete s_storage[i].name; 
        delete s_storage[i].address; 
    }

    free(s_storage);
    return 0; 
}