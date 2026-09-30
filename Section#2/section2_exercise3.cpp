#include<iostream>
using namespace std; 


template<typename T> T getValue(T input)
{
    cout << input; 
    return 0; 
}

int main()
{
    getValue<int>(10); 
    getValue<char>('A'); 
    getValue<string>("Team"); 

    return 0; 
}

