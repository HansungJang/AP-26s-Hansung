#include<iostream>
using namespace std; 

int main(){
    int length;

    cout << "Enter charater length : ";
    cin >> length; 
    
    char* input = new char[length]; 

    for(int i =0; i<length; i++)
    {
        cin >> input[i]; 
    }

    for(int i =0; i<length; i++) cout << input[i]; 

    delete[] input; 
    return 0; 
}