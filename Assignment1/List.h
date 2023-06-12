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

#include <cstdint>
using namespace std;

template<typename T>
class List
{
public:
	//! An iterator over the list
	class iterator;
	
private:
    class Node{
        T data;
        unique_ptr<Node> next;
        Node(const T& value) : data(value) next(nullptr) {} // Defines a constructor that takes a constant reference to a value of type T and initializes data member with the provided value.
        Node(T&& value) : data(std::move(value)), next(nullptr) {} // Move constructor that takes an r-value reference to a value of type T and initializes data by moving the provided value.
    };

public:
    class iterator {
    public:
        iterator(Node* node) : current(node) {} //default constructor that takes a pointer to a node in the list, and initializes the current node to be the provided node.
		/**
		 * The dereference operator.
		 *
		 * @returns   a reference to the "current" element
		 */
		T& operator*() const{
            return current->data;
        }

		/**
		 * Pre-increment operator (i.e., `++i`).
		 *
		 * This method increments the iterator and then returns a
		 * reference to the newly-incremented iterator.
		 *
		 * @returns   a reference to this iterator, after incrementing
		 */
		iterator& operator++(){
            if (current) {
                current = current->next.get();
            }
            return *this;
        }

		/**
		 * Post-increment operator (i.e., `i++`).
		 *
		 * This method returns a copy of this iterator as it currently
		 * is (i.e., pointing where it currently points) and _then_
		 * increments itself.
		 *
		 * @param     ignored   this is only used to distinguish the two
		 *                      increment operators (pre- and post-)
		 *                      from each other: its value should be
		 *                      ignored
		 *
		 * @returns   an iterator to the previously-current element
		 */
		iterator operator++(int ignored)
        {
            iterator temp(*this->ignored);
            ++(*this);
            return temp;
        }

		//! Is this iterator pointing at the same place as another one?
		bool operator== (const iterator& other) const{
            return current == other.current;
        }

		//! Is this iterator pointing at a different place from another?
		bool operator!= (const iterator& other) const{
            return !(*this == other);
        }

    private:
        Node* current;
    };

	//! Default constructor
public:
	List() : head(nullptr), tail(nullptr), listSize(0) {} //initializes an empty linked List
       
    

	//! Copy constructor
	List(const List& other){ //takes a constant reference to an element in the list that is repeated and copies it
        copyFrom(other);
    }

	//! Move constructor
	List(List&& other){ //takes a reference to the r-value other and moves it from it's original memory allocation.
        moveFrom(std::move(other));
    }

	//! Destructor
	~List() {
        clear(); //clears the list.
    }

 
	//! Copy assignment operator
	List& operator= (const List& other){ //takes a constant reference to an element in the list that is repeated and checks if this element is its repeat. 
        if (this != &other)
        {
            clear();
            copyFrom(other); // if it isn't, it copies its memory allocation.
        }
        return *this;
    }

	//! Move assignment operator
	List& operator= (List&& other){ //takes a reference to the r-value other and evaluates if this element is repeated.
         if (this != &other) // if this operator is not the reference to other, it erases it and recieves the memory allocation from other.
        {
            clear();
            moveFrom(std::move(other));
        }
        return *this;
    }


	//
	// Accessors:
	//
	//! How many elements are in this list?
	size_t size() const{
        return listSize;
    }

	//! Is this list empty?
	bool empty() const{
        return listSize == 0;
    }

	//! Get an iterator to the beginning of the list
	iterator begin(){
        return iterator(head.get());
    }

	//! Get an iterator just past the end of the list
	iterator end(){
        return iterator(nullptr);
    }


	//
	// Mutators:
	//
	//! Copy an element to the front of the list
	void push_front(const T& value){
        std::unique_ptr<Node> newNode = std::make_unique<Node>(value);
        newNode->next = std::move(head);
        head = std::move(newNode);
        if (!tail) {
            tail = head.get();
        }
        ++listSize;
    }

	//! Move an element to the front of the list
	void push_front(T&& value){
        std::unique_ptr<Node> newNode = std::make_unique<Node>(std::move(value));
        newNode->next = std::move(head);
        head = std::move(newNode);
        if (!tail){
            tail = head.get();
        }
        ++listSize;
    }

	//! Copy an element to the back of the list
	void push_back(const T& value){
        std::unique_ptr<Node> newNode = std::make_unique<Node>(value);
        if (!head){
            head = std::move(newNode);
            tail = head.get();
        } else {
            tail->next = std::move(newNode);
            tail = tail->next.get();
        }
        ++listSize;
    }

	//! Add an element to the back of the list
	void push_back(T&& value) {
        std::unique_ptr<Node> newNode = std::make_unique<Node>(std::move(value));
        if (!head){
            head = std::move(newNode);
            tail = head.get();
        }else{
            tail->next = std::move(newNode);
            tail = tail->next.get();
        }
        ++listSize;
    }

	/**
	 * Copy an element into an arbitrary location.
	 *
	 * This method makes a copy of an element and inserts that copy into a
	 * location pointed at by the given iterator. After insertion into a
	 * list of n elements, the list should contain n+1 elements (i.e., no
	 * existing element should be replaced).
	 *
	 * @returns   an iterator pointing at the newly-inserted element
	 */
	iterator insert(iterator, const T& value){
        if (pos == begin()){
            push_front(value);
            return begin();
        } else if (pos == end()) {
            push_back(value);
            return iterator(tail);
        } else {
            std::unique_ptr<Node> newNode = std::make_unique<Node>(value);
            Node* prevNode = pos.current->next.get();
            newNode->next = std::move(pos.current->next);
            pos.current->next = std::move(newNode);
            ++listSize;
            return iterator(prevNode);
        }
    }

	/**
	 * Move an element into an arbitrary location.
	 *
	 * This method inserts an element into a location pointed at by the
	 * given iterator, using move semantics to avoid copies. After insertion
	 * into a list of n elements, the list should contain n+1 elements
	 * (i.e., no existing element should be replaced).
	 *
	 * @returns   an iterator pointing at the newly-inserted element
	 */
	iterator insert(iterator, T&& value){
        if (pos == begin()){
            push_front(std::move(value));
            return begin();
        } else if (pos == end()){
            push_back(std::move(value));
            return iterator(tail);
        } else{
            std::unique_ptr<Node> newNode = std::make_unique<Node>(std::move(value));
            Node* prevNode = pos.current->next.get();
            newNode->next = std::move(pos.current->next);
            pos.current->next = std::move(newNode);
            ++listSize;
            return iterator(prevNode);
        }
    }

	//! Remove an element from an arbitrary location
	void erase(iterator){
        if (pos == begin()){
            head = std::move(head->next);
            if (!head){
                tail = nullptr;
            }
        } else {
            iterator prev = begin();
            while (prev.current->next.get() != pos.current) {
                ++prev;
            }
            prev.current->next = std::move(pos.current->next);
            if (pos.current == tail){
                tail = prev.current;
            }
                
        }

        --listSize;
    }

private:
	// Add whatever you need to add here
    Node* head;
    Node* tail;
    size_t listSize;

    void copyFrom(const List& other)
    {
        for (const T& value : other)
            push_back(value);
    }

    void moveFrom(List&& other)
    {
        head = std::move(other.head);
        tail = other.tail;
        listSize = other.listSize;

        other.tail = nullptr;
        other.listSize = 0;
    }

    void clear()
    {
        head.reset();
        tail = nullptr;
        listSize = 0;
    }
};