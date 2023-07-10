/*
 * Copyright 2018-2019 Jonathan Anderson
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

#include <cassert>
#include <cstddef>      // for definition of size_t
#include <functional>   // std::function
#include <memory>       // std::unique_ptr
#include <stack>
#include <iostream>
#include <string>

template<typename T, typename Comparator = std::less<T>>
class BinarySearchTree
{
    public:
	enum class Traversal
	{
		PreOrder,
		InOrder,
		PostOrder,
	};
    
    struct Node;
	//! Insert a new value into the appropriate place in the tree./*
	void insert(T && value, std::unique_ptr<Node> &node){// takes an r-value of type T and a reference parameter of type std::unique_ptr<Node>
        if (!node){
            node = std::make_unique<Node>(std::move(value)); //if no node yet exists, a new node is created and the value passed into the function is moved to it.
        } else if(compare_(value, node->element)) { //this else if block will run if the value passed into the function is less than the element being pointed to by the 'node'.
            if (node->left_) {
                insert(std::move(value), node->left_); //moves the value to a left node if one exists.
            } else {
                node->left_ = std::make_unique<Node>(std::move(value)); // if one doesn't exist, then a left-pointing unique pointer of type Node is created that stores the value.
            }
        } else if (compare_(node->element_, value)){
            if (node->right_){
                insert(std::move(value), node->right_);
            }
        }
		insert(std::move(value), root_); //recursive call of insert.
	}

	void dot(std::ostream &o) const //takes a reference to an object of type std::stream as a parameter.
	{
		o << "digraph {\n"; //assigns "digraph" to this object.

		if (root_)
		{
			root_->dot(o); // if a root exists, this root points to the recursive call of dot on o.
		}

		o << "}\n"; 
	}
    

	/**
	 * An iterator that can traverse the BST in some order.
	 *
	 * The iterator contains a "current" node, a stack of parent nodes and
	 * a Traversal value to remind it which strategy it's following.
	 */
	class Iterator{
	    public:
        Iterator(Node* current, Traversal order) : current_(current), order_(order){ /*The constructor takes a Node* representing the current node and a Traversal value indicating the traversal order. It initializes the current_ and order_ members and calls the initializeStack function if the current_ is not nullptr.*/
            if (current_){ //if the tree is not empty
                initializeStack();
            }
        }
		/**
		 * Move to the next node in the tree that should be accessed.
		 *
		 * This operator method just calls private methods to try and
		 * keep the logic of the various traversal mechanisms clear.
		 */
		Iterator operator++(int){ //The operator++ function overloads the post-increment operator and advances the iterator by calling the advance function.
            Iterator prev = *this;
            advance();
            return prev;
        }

		//! Dereference the iterator at its current position
		const T& operator*(){ //The operator* function overloads the dereference operator and returns a reference to the element stored in the current node.
            return current_->element_;
        }

		//! Is this iterator *not* the same as another?
		bool operator!=(const Iterator &other){//The operator!= function overloads the inequality operator and compares two iterators by checking if their current_ pointers are not equal.
            return current_ != other.current_;
        }

		// add whatever else you need here
        private:
    
        Node* current_;
        Traversal order_;
        std::stack<Node*> nodeStack_;
        void initializeStack(){ //The initializeStack function initializes the stack based on the traversal order.   
            if (order_ == Traversal::PreOrder){ //For pre-order traversal, it pushes the current node onto the stack.
                nodeStack_.push(current_);
            } else if (order_ == Traversal::InOrder){ //For in-order traversal, it pushes all the left nodes onto the stack.
                pushLeftNodes(current_);
            } else if (order_ == Traversal::PostOrder){ //For post-order traversal, it uses a temporary stack to store nodes and then pushes them onto the main stack in the correct order.
                pushPostOrderNodes(current_);
            }
        }

        void pushLeftNodes(Node* node){ //The pushLeftNodes function pushes all the left nodes of a given node onto the stack.
            while (node != nullptr){
                nodeStack_.push(node);
                node = node->left_.get();
            }
        }

        void pushPostOrderNodes(Node* node){ //The pushPostOrderNodes function pushes nodes onto the stack in the correct order for post-order traversal. It uses a temporary stack to store the nodes.
            std::stack<Node*> tempStack;
            while (node != nullptr || !tempStack.empty()){
                if (node != nullptr){
                    tempStack.push(node);
                    nodeStack_.push(node);
                    node = node->right_.get();
                } else {
                    node = tempStack.top();
                    tempStack.pop();
                    node = node->left_.get();
                }
            }
        }

    void advance(){ //The advance function moves the iterator to the next node based on the traversal order. 
        if (order_ == Traversal::PreOrder) {
            if (current_->left_) {
                nodeStack_.push(current_->left_.get());
                current_ = current_->left_.get();
            } else if (current_ ->right_){
                nodeStack_.push(current_->right_.get());
                current_ = current_->right_.get(); // gets the value stored in this node.
            } else {
                if (!nodeStack_.empty()) {
                    Node* parent = nodeStack_.top(); // returns a reference to the top element of the stack.
                    nodeStack_.pop(); //removes the top element of the nodeStack
                    while (!nodeStack_.empty() && (parent->right_ == nullptr || parent->right_.get() == current_)) { 
                        current_ = parent;
                        parent = nodeStack_.top();
                        nodeStack_.pop();
                    }
                    if (!nodeStack_.empty()) {
                        current_ = parent->right_.get();
                        nodeStack_.push(current_);
                    } else {
                        current_ = nullptr;
                    }
                } else {
                    current_ = nullptr;
                }
            }
        } else if (order_ == Traversal::InOrder){
            if (!nodeStack_.empty() || current_) {
                while (current_) {
                    nodeStack_.push(current_);
                    current_ = current_->left.get();
                } 
                current_ = nodeStack_.top();
                nodeStack_.pop();
                current_ = current_->right.get();
            } else {
                current_ = nullptr;
            }
        } else if (order_ == Traversal::PostOrder){
            if (!nodeStack_.empty() || current_) {
                while (current_) {
                    if (current_->right_) {
                        nodeStack_.push(current_->right_.get());
                    }
                    nodeStack_.push(current_);
                    current_ = current_->left.get();
                    
                }
                current_ = nodeStack_.top();
                nodeStack_.pop();
                if (!nodeStack_.empty() && current_->right_ && nodeStack_.top() == current_->right_.get()) {
                    nodeStack_.pop();
                    nodeStack_.push(current_);
                    current_ = current_->right_.get();
                } else {
                    current_ = nullptr;
                }
                
            }

        }
    }
    };
	

	Iterator begin(Traversal order){
        switch (order){
        case Traversal::PreOrder:
            return Iterator(root_.get(), order);
        case Traversal::InOrder:
            return Iterator(root_.get(), order);
        case Traversal::PostOrder:
            return Iterator(root_.get(), order);
        default:
            return Iterator(nullptr, order);
        }
    }
	Iterator end(){
        return Iterator(nullptr, Traversal::PreOrder);
    }

    //private:
	struct Node
	{
		Node(T value) : element_(std::move(value))
		{
		}

		void dot(std::ostream &o) const
		{
			// NOTE: this is slightly more complicated than strictly
			//       necessary (using addresses as names, etc.), but
			//       it will produce valid Dot output even when the
			//       node values are things like money (e.g., $17)

			o
				<< "  \"" << this << "\""
				<< " [ label = \"" << element_ << "\" ];\n";

			if (left_)
			{
				o
					<< "  \"" << this << "\""
					<< " -> "
					<< "\"" << left_.get() << "\""
					<< " [ label = \"L\" ]\n";

				left_->dot(o);
			}

			if (right_)
			{
				o
					<< "  \"" << this << "\""
					<< " -> "
					<< "\"" << right_.get() << "\""
					<< " [ label = \"R\" ]\n";

				right_->dot(o);
			}
		}

		T element_;
		std::unique_ptr<Node> left_;
		std::unique_ptr<Node> right_;
	};

	/**
	 * Internal implementation of recursive insert.
	 *
	 * //param   value      the value to insert
	 * //param   node       the root of the (sub-)tree being inserted into;
	 *                     may be null if the (sub-)tree is empty
	 *
	void insert(T &&value, std::unique_ptr<Node> &node){
		if (!node) {
			node = std::make_unique<Node>(std::move(value));
		}
		else if (compare_(value, node->element_)) {
            if (node->left_){
                insert(std::move(value), node->left_);
            } else {
                node->left_ = std::make_unique<Node>(std::move(value));
            }
			
		} else if (compare_(node->element_, value)) {
            if (node->right_) {
                insert(std::move(value), node->right_);
            } else {
                node->right_ = std::make_unique<Node>(std::move(value));
            }
			
		} else {
			// assuming no duplicates
		}*/
	

	Comparator compare_;
	std::unique_ptr<Node> root_;
};