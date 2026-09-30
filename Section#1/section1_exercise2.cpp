#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <string>
using namespace std; 

int main()
{
    int size; 
    string input; // use for length
    char * inputMemory;
    int* enctyp;   
    
    for(int i = 0 ; i < size; i++)
    {
        //1.  string 데이터 타입으로 문자열을 읽음 -> 길이 추출(.legth)
        cout << "Enter Random String : "; 
        getline(cin, input);

        size = input.size();


        //2. malloc으로 문자열 저장 arr를 생성  
        inputMemory = (char*)malloc( size * sizeof(char));  // 문자열 마지막에 공배 문자 처리 
        enctyp = (int*)malloc( size * sizeof(int));

        //3. 문자 기준으로 random 숫자 (함수)
        // 아이디어 encrption 
        
        // #pseudo code 
        //srand(time(NULL)) 
        // 교수님 ecrpted 아이디어 코드는 (rand() 함수 사용, -50 ~ 50 사이 숫자를 사용 
        // crpted string : ascii + rndom 숫자 
        // crpted num : random 숫자 
        // 문자열 마지막에 '\0' 추가 
        

        for(int i =0; i < size; i++)
        {
           
            inputMemory += input[i]; 
            enctyp += encrp_func(input[i]);
        }
        
        // 실행시간 O(1)

    }

    free(inputMemory); 
    free(enctyp); 
    return 0; 
}

int encrp_func(char input)
{
    // Time base random 
    // - char input -> ascii 받고, Time 함수 , range (0, 9)  
    srand(time(0));


}