#include<iostream>
#include<stdlib.h>
using namespace std; 

/*
inheritance 컨셉 이용하면 뭘할 수 있는가? 
-> 객체 안에서 성질 공유가 가능하니까 재활용성이 높아짐
ex) enemy 만든다고 할때 기본적인 공격, 특성에 대해서 parent class 만들어 놓으면 코드 refactor 효과

*/



class Parent 
{
    public : 
        Parent(){}; 
        void print()
        {
            cout << "I'm a parent" << endl; 
        }
}; 

class child : Parent
{
    public : 
        void print()
        {
            cout << "I'm a child " << endl; 
            Parent::print(); 
        }
};


int main(){

    child mychild; 
    mychild.print(); 

    return 0; 
}