#include<iostream>
#include<random>
#include<ctime>
#include<cstdlib>
#include<memory>

using namespace std;

int randomValue();
void alllocateNum (shared_ptr<int[]> randNum, int length); 
int worldValue = 0; 

int main()
{
    int length = 10000;
    srand(static_cast<unsigned int>(time(nullptr))); // 기준 seed 값 (매번 새로 호출하면 같은 값이 나오는 불쌍사가 발생함)

    for(int i = 0; i < length; i++)
    {
        // unique_ptr<int> randNum(new int[length]); 
       shared_ptr<int[]> randNum(new int[length]); 
        alllocateNum(randNum, length/100); 

        for(int j =0; j < length; j++)
        {
            cout << randNum[j];
        }
        cout << endl; 


        //for(int j=0; j< length; j++) cout << j+1 << ": "<< randNum[j]; 
        cout << endl; 

    }
    

  return 0; 
}

int randomValue()
{
    return (rand() % 10); // 0 ~ 9
}

int GenerateValue()
{
    return worldValue += 1; 
}

void alllocateNum (shared_ptr<int[]> randNum, int length)
{
    for(int j = 0; j < length; j++)
    {
        randNum[j] = GenerateValue(); //randomValue(); 
    }

    return; 
}

// void createArr(){
//     unique_ptr<int[]> intarr = make_unique<int[]>(100); 
//     for(int i =0 ; i < 100; i++)
//     {

//     }
// }



//{
// 
//}

// shared pointer로 주소 받아서 O(n^2) 
// 함수 안에서는  random 수 100개 만들어서 할당 