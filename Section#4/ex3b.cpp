#include <string>
#include <iostream>
#include <list>

// 수정 부분 입력이 니상하게 감 수정할 것
using namespace std;

class Address
{
private: // initialize memeber var ; error 발생하는 거 막기 위해서 / sybtatical valide 
    string streetName;
    int houseNumber;
    int postalCode;
    string city;

public:
    
    Address(string name ="", int number =0, int zip =0, string place ="")
    {
        streetName = name;
        houseNumber = number;
        postalCode = zip;
        city = place;
    }
    // : steetName(street), houseNumber(number), postalCode(zip), city(place)
    // ':' 으로 초기화 하는 방법도 있다

    string getStreetName() {return streetName;}
    int getHouseNumber(){return houseNumber;}
    int getPostalCode(){return postalCode;}
    string getCity(){return city;}

    void print(void)
    {
        cout << streetName << " " << houseNumber << ", " << postalCode << " " << city << endl;
    }

    void UpdateAddress(string name, int number, int zip, string place)
    {
        char input; 
        cout << "Are you sure tyou want to change the address [y/n]: "; 
        cin >> input; 

        if(input == 'y' || input == 'Y')
        {
            streetName = name;
            houseNumber = number;
            postalCode = zip;
            city = place;
            cout << "Address updated successfully.\n";
        }
    }
};

Address inputNewAddr()
{
    string name; 
    int number; 
    int zip; 
    string place; 
        cin.ignore(); 
        cout << "name : "; 
        getline(cin, name);
        cout << "number : ";  
        cin >> number; cin.ignore(); 
        cout << "zip : ";  
        cin >> zip; cin.ignore(); 
        cout << "place : ";  
        getline(cin, place); 

   return  Address(name, number, zip, place); 
}

int main(void)
{
    list<Address> adlist; 
    int input; 

    while(1)
    {
        int index = 0; 
        cout << endl; 

        if(!adlist.empty())
        {
            for(Address& ad : adlist)
            {
                cout << index << " "; 
                ad.print();
                index +=1;  
            }

        }

        cout << "Menu" << endl; 
        cout << "#1. add new addr" << endl; 
        cout << "#2. edit addr" << endl; 
        cout << "#3. end" << endl; 

        cout << "Choose Menu : " ; 
        cin >> input; 

        switch (input)
        {
        case 1: 
                {
                    Address newAddr = inputNewAddr(); 
                    adlist.push_back(newAddr); 
                    break;
                }

        case 2: 
                {
                    index = 0; 
                    for(Address& ad : adlist)
                    {
                        cout << index << " "; 
                        ad.print();
                        index +=1;  
                    }

                    index = 0; 
                    int input_index = 0; 
                    cout << "edit index Num : "; 
                    cin >> input_index; 

                    for(Address& ad : adlist)
                    {
                        if(index == input_index)
                        {
                            Address newAddr = inputNewAddr(); 
                            ad.UpdateAddress(newAddr.getStreetName(), newAddr.getHouseNumber(), newAddr.getPostalCode(), newAddr.getCity()); 
                        }
                        index++; 
                    }
                           
                }
         default:
            break;
        }
        
        if(input == 3) break; 
    }


    return 0;
}

