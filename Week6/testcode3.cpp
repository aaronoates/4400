// Create a tree of integers:
#include "BSTdefault.h"
#include <iostream>
int main () {
    BinarySearchTree<int> t;

// Fancy way of not having to write BinarySearchTree<int> twice:
    const auto Order = decltype(t)::Traversal::InOrder;

// Insert the values 4, 2, 6, 1, 3, 5 and 7:
    for (int n : { 4, 2, 6, 1, 3, 5, 7 }){
	    t.insert(n);
    }

// The following should print: 1234567
    for (auto i = t.begin(Order); i != t.end(); i++)
    {
	    std::cout << *i;
    }
}
