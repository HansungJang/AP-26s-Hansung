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

class Property
{
    private: 
    string name; 
    string propertyID; 
    string owner; 
    Address address; 
   
    public: 
     Property(string name, string id, string owner, Address& addr) :
         name(name), propertyID(id), owner(owner), address(addr){}

    void print()
    {
        cout << name << ", " << propertyID << ", " << owner << " " ;
        address.print();
        cout << endl;  
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

Property inputNewProp(Address& addr)
{
    string name; 
    string propertyID; 
    string owner;
    
    cin.ignore(); 
    cout << "name : "; 
    getline(cin, name);
    cout << "propertyID : "; 
    getline(cin, propertyID);
    cout << "owner : "; 
    getline(cin, owner);
    
    return Property(name, propertyID, owner, addr);  
}

void printOutAddrList(list<Address>& list)
{
    int index =0; 
    for(Address& ad : list)
    {
        cout << index << " "; 
        ad.print();
        index +=1;  
    }
}

void printOutPropList(list<Property>& list)
{
    int index =0; 
    for(Property& ad : list)
    {
        cout << index << " "; 
        ad.print();
        index +=1;  
    }

}

int main(void)
{
    list<Address> adlist; 
    list<Property> prlist; 
    int input; 

    while(1)
    {
        int index = 0; 
        cout << endl; 

        if(!adlist.empty())
        {
            printOutAddrList(adlist); 
        }

        cout << "Menu" << endl; 
        cout << "#1. add new addr" << endl; 
        cout << "#2. edit addr" << endl; 
        cout << "#3. end" << endl; 
        cout << "#4 add properties" << endl; 
        cout << "#5 print saved properties" << endl; 

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
                    printOutAddrList(adlist); 

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
                            break; 
                        }
                        index++; 
                    }
                           
                }
            case 4: 
                {
                    if(adlist.empty()) {cout << "Empty address .... " << endl; break;}
                    printOutAddrList(adlist); 

                    index = 0; 
                    int input_index = 0; 
                    cout << "edit index Num : "; 
                    cin >> input_index; 

                    for(Address& ad : adlist)
                    {
                        if(index == input_index)
                        {
                            prlist.push_back(inputNewProp(ad)); 
                            break; 
                        }
                        index++; 
                    }
                    break; 
                }
            case 5 : 
                {
                    if(adlist.empty()) {cout << "Empty address .... " << endl; break;}
                    printOutPropList(prlist); 
                    break; 
                }
         default:
            break;
        }
        
        if(input == 3) break; 
    }


    return 0;
}

