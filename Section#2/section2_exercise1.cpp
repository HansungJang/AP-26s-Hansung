#include<iostream>
using namespace std; 

int main()
{
    int* num = new int(); 
    
    char* character = new char(); 

    string* word = new string(); 

    *num = 10; 
    *character = 'A';
    *word = "big"; 

    cout << *num <<*character << *word << endl; 
    delete num, character, word; 
    return 0; 
}