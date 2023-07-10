/*
 * Copyright 2018 Jonathan Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "BST.h"
#include <iostream>



int main(){
	BinarySearchTree<int> t;
	const auto Order = decltype(t)::Traversal::InOrder;

// Insert the values 4, 2, 6, 1, 3, 5 and 7:
	for (int n : { 4, 2, 6, 1, 3, 5, 7 }){
		t.insert(n);
	}

// The following should print: 1234567
	for (auto i = t.begin(Order); i != t.end(); ++i){
		std::cout << *i;
	}
}