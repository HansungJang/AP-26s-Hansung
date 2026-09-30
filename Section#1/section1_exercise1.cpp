#include<iostream>
#include<stdlib.h>
using namespace std;

int main(){
    int num; 
    int* child_age; 

    cin >> num;
    cin.ignore();
    child_age = (int*)malloc(num * sizeof(int));

    for(int i = 0; i < num; i++){
        cout << "Input" << i + 1 << ": "; 
        cin >> child_age[i];
    }

    for(int i = 0; i < num; i++){
        cout << child_age[i] << " ";
    }
    
    free(child_age);
    return 0;
}