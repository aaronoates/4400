#include <iostream>
using namespace std;

int main () {
    int fact; 
    cout << "enter an integer." << endl;
    cin >> fact;
    for (int i = fact - 1; i >= 1; i--) {
        fact *= i;
    }
    cout << fact << endl;
    char goAgain;
    cout << "would you like to try another number? Y/N" << endl;
    cin >> goAgain;
    if (goAgain == 'Y') {
        main();
    
    } else {
        return 0;
    }
    
    
}