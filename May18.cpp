#include <iostream> 
using namespace std;

void bubblesort (int array[], int size) { 
    for (int i = 0; i < size; i++) { //iterates through the created array
        for (int j = i+1; j < size; j++){ // iterates through the same array again
            if (array[i] > array[j]){ 
                int placeholder = array[i];
                array[i] = array[j];
                array[j] = placeholder; // if an element is greater than the one next to it, it switches the places of them so they're in
                // ascending order
            } 
            
           
        }
    }
   
}

int main() {
    const int size = 10;
    int RandomArray[size]; // initializes an empty array of size 10

    for (int a = 0; a < size; a++){
        RandomArray[a] = rand() % 10; // each element added to the list is a random number between 0 and 10
    }
    bubblesort(RandomArray, size);
   
    for (int step = 0; step < size; step++) {
        cout << RandomArray[step];
        // prints the new array, now in ascending order!
    }
     
    return 0;
}