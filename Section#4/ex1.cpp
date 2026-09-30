#include <iostream>
#include <list>
using namespace std; 

class Product
{
    public : 
    string name; 
    string unit; 

    Product(string n, string u) // 특수 case 
    {
        name = n; 
        unit = u; 
    }
}; 

int main() // 메모리 할당과 class 사용에 대해서 알아보는 예제 
{
    list<Product> shoppinglist; 
    Product milk("Milk", "litter");
    shoppinglist.push_back(milk); 
    shoppinglist.push_back(milk); 
    shoppinglist.push_back(Product("cheese", "slice"));
    
    for(Product product : shoppinglist){
        cout << product.name << ", " << product.unit << endl; 
    }
    
    return 0; 
}