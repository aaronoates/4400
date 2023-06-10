#include <iostream>
#include <list>

template<typename T>
void quicksort(std::list<T>& values) { // takes in an existing list of values of type T
    if (values.size() <= 1) {
        return;
    }

    T pivot = values.front();

    std::list<T> lesser;
    std::list<T> equal;
    std::list<T> greater;

    for (const auto& value : values) { //iterates through the list, each index is a value in values.
        if (value < pivot) {
            lesser.push_back(value); //adds the value to the list lesser if the value is less than the pivot
        } else if (value == pivot) {
            equal.push_back(value); //adds the value to the list equal if the value is equal to the pivot
        } else {
            greater.push_back(value); // adds the value to the list greater if the value is greater than the pivot
        }
    }

    quicksort(lesser);
    quicksort(greater);

    values.clear();

    values.splice(values.end(), lesser); //moves all the elements from lesser to the end of values list
    values.splice(values.end(), equal); //moves all the elements from equal to the end of values list
    values.splice(values.end(), greater); // moves all the elements from greater to the end of values list
}

int main() {
    std::list<int> numbers = {7, 2, 5, 1, 9, 3};

    std::cout << "Before sorting: ";
    for (const auto& value : numbers) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    quicksort(numbers);

    std::cout << "After sorting: ";
    for (const auto& value : numbers) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}