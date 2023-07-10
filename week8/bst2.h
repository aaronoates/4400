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
#include <cstddef>
#include <functional>
#include <memory>
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

    struct Node
    {
        Node(T value) : element_(std::move(value)) {}

        void dot(std::ostream &o) const
        {
            o << "  \"" << this << "\""
              << " [ label = \"" << element_ << "\" ];\n";

            if (left_)
            {
                o << "  \"" << this << "\""
                  << " -> "
                  << "\"" << left_.get() << "\""
                  << " [ label = \"L\" ]\n";

                left_->dot(o);
            }

            if (right_)
            {
                o << "  \"" << this << "\""
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

    using NodePtr = std::unique_ptr<Node>;

    void insert(T &&value, NodePtr &node)
    {
        if (!node)
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

    void dot(std::ostream &o) const
    {
        o << "digraph {\n";

        if (root_)
        {
            root_->dot(o);
        }

        o << "}\n";
    }

    class Iterator
    {
    public:
        Iterator(Node *current, Traversal order)
            : current_(current), order_(order)
        {
            if (current_)
            {
                initializeStack();
            }
        }

        Iterator operator++(int)
        {
            Iterator prev = *this;
            advance();
            return prev;
        }

        const T &operator*()
        {
            return current_->element_;
        }

        bool operator!=(const Iterator &other)
        {
            return current_ != other.current_;
        }

    private:
        Node *current_;
        Traversal order_;
        std::stack<Node *> nodeStack_;

        void initializeStack()
        {
            if (order_ == Traversal::PreOrder)
            {
                nodeStack_.push(current_);
            }
            else if (order_ == Traversal::InOrder)
            {
                pushLeftNodes(current_);
            }
            else if (order_ == Traversal::PostOrder)
            {
                pushPostOrderNodes(current_);
            }
        }

        void pushLeftNodes(Node *node)
        {
            while (node != nullptr)
            {
                nodeStack_.push(node);
                node = node->left_.get();
            }
        }

        void pushPostOrderNodes(Node *node)
        {
            std::stack<Node *> tempStack;
            while (node != nullptr || !tempStack.empty())
            {
                if (node != nullptr)
                {
                    tempStack.push(node);
                    nodeStack_.push(node);
                    node = node->right_.get();
                }
                else
                {
                    node = tempStack.top();
                    tempStack.pop();
                    node = node->left_.get();
                }
            }
        }

        void advance()
        {
            if (order_ == Traversal::PreOrder)
            {
                current_ = nodeStack_.top();
                nodeStack_.pop();
                if (current_->right_)
                {
                    pushLeftNodes(current_->right_.get());
                }
            }
            else if (order_ == Traversal::InOrder)
            {
                current_ = nodeStack_.top();
                nodeStack_.pop();
                pushLeftNodes(current_->right_.get());
            }
            else if (order_ == Traversal::PostOrder)
            {
                nodeStack_.pop();
                if (!nodeStack_.empty())
                {
                    Node *parent = nodeStack_.top();
                    if (current_ == parent->left_.get())
                    {
                        pushLeftNodes(parent->right_.get());
                    }
                    else
                    {
                        current_ = parent;
                    }
                }
                else
                {
                    current_ = nullptr;
                }
            }
        }
    };

    Iterator begin(Traversal order)
    {
        switch (order)
        {
        case Traversal::PreOrder:
            return Iterator(root_.get(), order);
        case Traversal::InOrder:
            return Iterator(root_.get(), order);
        case Traversal::PostOrder:
            return Iterator(root_.get(), order);
        default:
            return
        };
    }
};