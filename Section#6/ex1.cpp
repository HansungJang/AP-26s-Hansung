#include <iostream>
using namespace std; 
/*
다중 상속시 : ambiguity 문제 
-> 똑같은 parent를 여러번 호출, 같은 함수 호출err

sol 
- virtual ; keyword를 통해서 참조하는 함수 / 변수를 고정하는 것 
- :: 연산 ; 상속받은 어디에서 가지고 올건지 명시 
- 이름 바꾸기 ; 나중 코드 직관성 관리 어려워짐 (비추)
*/


class m1 
{
    private : 
    string name; 
    public : 
        string* classdata;  
        m1():name("m1")
        {
            cout << "#m1 constructed" <<endl; 
            classdata = new string("Anton"); 
        };
        void print(){ cout << name << endl; } 
        ~m1()
        {
            cout << "#m1 deconstructed" << endl;
            delete classdata; 
        }; 
}; 

class m2 : public m1 
{
    private : 
    string name; 
    public : 
        m2():name("m2"){ cout << "#m2 constructed" <<endl; };
        void print(){ cout << name << endl; } 
        ~m2()
        {
            cout << "classdata : " << *classdata << endl; 
            cout << "#m2 deconstructed" << endl;
        }; 
}; 

class m3 : public m1 
{
    private : 
    string name; 
    public : 
        m3():name("m3"){ cout << "#m3 constructed" <<endl; };
        void print(){ cout << name << endl; } 
        ~m3(){ cout << "#m3 deconstructed" << endl;}; 
}; 


class m4 : public m2, public m3 
{
    private : 
    string name; 
    public : 
        m4():name("m4"){ cout << "#m4 constructed" <<endl; };
        void print(){ cout << name << endl; } 
        ~m4(){ cout << "#m4 deconstructed" << endl;}; 
}; 


int main()
{
    m4 class4; 
    class4.print(); 
    return 0; 
}
