#include <string>
#include <iostream>

using namespace std;

class Address
{
private:
    string streetName;
    int houseNumber;
    int postalCode;
    string city;

public:
    Address(string name, int number, int zip, string place)
    {
        streetName = name;
        houseNumber = number;
        postalCode = zip;
        city = place;
    }

    void print(void)
    {
        cout << streetName << " " << houseNumber << ", " << postalCode << " " << city << endl;
    }

    void newAddress(string name, int number, int zip, string place)
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

int main(void)
{
    // Create a new address object:
    Address myAddress = Address("Pääskysentie", 1, 48220, "Kotka");

    // Print the current address:
    myAddress.print();

    // Attempt to change the address:
    myAddress.newAddress("Paraatikenttä", 7, 45100, "Kouvola");

    myAddress.print();

    return 0;
}