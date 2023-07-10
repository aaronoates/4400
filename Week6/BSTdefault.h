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

	//! Insert a new value into the appropriate place in the tree.
	void insert(T value)
	{
		insert(std::move(value), root_);
	}

	void dot(std::ostream &o) const
	{
		o << "digraph {\n";

		if (root_)
		{
			root_->dot(o);
		}

		o << "}\n";
	}

	/**
	 * An iterator that can traverse the BST in some order.
	 *
	 * The iterator contains a "current" node, a stack of parent nodes and
	 * a Traversal value to remind it which strategy it's following.
	 */
	class Iterator
	{
	public:
        Iterator(Node* current, Traversal order) : current_(current), order_(order){ //The constructor takes a Node* representing the current node and a Traversal value indicating the traversal order. It initializes the current_ and order_ members and calls the initializeStack function if the current_ is not nullptr.
            if (current_){
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
        if (order_ == Traversal::PreOrder){ //For pre-order traversal, it pops the top node from the stack, sets it as the current node, and pushes the left nodes of its right child onto the stack. 
            current_ = nodeStack_.top();
            nodeStack_.pop();
            if (current_->right_){
                pushLeftNodes(current_->right_.get());
            }
        } else if (order_ == Traversal::InOrder){ //For in-order traversal, it pops the top node from the stack, sets it as the current node, and pushes the left nodes of its right child onto the stack
            current_ = nodeStack_.top();
            nodeStack_.pop();
            pushLeftNodes(current_->right_.get());
        } else if (order_ == Traversal::PostOrder){ //For post-order traversal, it pops the top node from the stack and checks if there is a parent node. If there is, it determines if the current node is the left child of the parent or not. If it is, it pushes the left nodes of the parent's right child onto the stack. Otherwise, it sets the parent node as the current node.
            nodeStack_.pop();
            if (!nodeStack_.empty()){
                Node* parent = nodeStack_.top();
                if (current_ == parent->left_.get()){
                    pushLeftNodes(parent->right_.get());
                } else {
                    current_ = parent;
                }
            } else {
                current_ = nullptr;
            }
        }
    }
};
	

	Iterator begin(Traversal order){
        switch (order){
        case Traversal::PreOrder:
            return Iterator(root_, order);
        case Traversal::InOrder:
            return Iterator(root_, order);
        case Traversal::PostOrder:
            return Iterator(root_, order);
        default:
            return Iterator(nullptr, order);
        }
    }
	Iterator end(){
        return Iterator(nullptr, Traversal::PreOrder);
    }

private:
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
	 * @param   value      the value to insert
	 * @param   node       the root of the (sub-)tree being inserted into;
	 *                     may be null if the (sub-)tree is empty
	 */
	void insert(T &&value, std::unique_ptr<Node> &node)
	{
		if (not node)
		{
			node = std::make_unique<Node>(std::move(value));
		}
		else if (compare_(value, node->element_))
		{
			insert(std::move(value), node->left_);
		}
		else if (compare_(node->element_, value))
		{
			insert(std::move(value), node->right_);
		}
		else
		{
			// assuming no duplicates
		}
	}

	Comparator compare_;
	std::unique_ptr<Node> root_;
};