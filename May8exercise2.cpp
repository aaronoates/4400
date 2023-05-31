#include <iostream>
using namespace std;

class Weapon {
public:
    string sword = "sword";
    string gun = "gun";
    string car = "car";


};

class isWeapon : public Weapon {
    string choice;
    public:
    void check() {
        cout << "choose an object; sword, gun, or car" << endl;
        cin >> choice; 
        if (choice == sword) {
            cout << "weapon." << endl;
        } else if (choice == gun) {
            cout << "weapon." << endl;
        } else if (choice == car) {
            cout << "not a weapon." << endl;
        } else {
            cout << "not sure." << endl;
        }
        

        }
        
    
};

int main () {
    Weapon w;
    isWeapon i;
    i.check();
    main();
}
