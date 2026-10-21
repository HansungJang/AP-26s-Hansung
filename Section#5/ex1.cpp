#include <iostream>
#include <string>
using namespace std;

class Character {
public:
    string name;
    int x;          // Horizontal position
    int y;          // Vertical position
    bool crouching; // Is the character crouching
    bool inAir;     // Is the character in the air (jumping)

    // Constructor
    Character(string n) : name("No"), x(0), y(0), crouching(false), inAir(false) {
        cout << "Character " << name << " created.\n";
    }

    // Destructor
    ~Character() {
        cout << "Character " << name << " destroyed.\n";
    }
};

class Enemy {
public:
    string name;
    int x;          // Horizontal position
    int y;          // Vertical position
    int damage;     // How much damage the enemy deals

    // Constructor
    Enemy(string n, int dmg) : name("No"), x(0), y(0), damage(dmg) {
        cout << "Enemy " << name << " created.\n";
    }

    // Destructor
    ~Enemy() {
        cout << "Enemy " << name << " destroyed.\n";
    }
};

int main() {
    cout << "Creating character and enemy:\n";
    Character player("Hero");
    Enemy villain("Villain", 10);

    cout << "Game execution ending, objects will be destroyed.\n";

    return 0;
}