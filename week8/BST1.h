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
private:
    struct Node
    {
        Node(T value) : element_(std::move(value))
        {
        }

        void dot(std::ostream &o) const
        {
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

public:
    

    //! Insert a new value into the appropriate place in the tree.
    void insert(T value)
    {
        if (root_)
        {
            insert(std::move(value), root_);
        }
        else
        {
            root_ = std::make_unique<Node>(std::move(value));
        }
    }

    void dot(std::ostream &o) const
    {
        o << "digraph {\n";

        if (root_ != nullptr)
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
        Iterator(Node* current, Traversal order) : current_(current), order_(order)
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

        const T& operator*()
        {
            return current_->element_;
        }

        bool operator!=(const Iterator& other)
        {
            return current_ != other.current_;
        }

    private:
        Node* current_;
        Traversal order_;
        std::stack<Node*> nodeStack_;

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

        void pushLeftNodes(Node* node)
        {
            while (node != nullptr) 
            {
                nodeStack_.push(node);
                node = node->left_.get();
            }
        }

        void pushPostOrderNodes(Node* node)
        {
            std::stack<Node*> tempStack;
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
                if (current_->left_)
                {
                    nodeStack_.push(current_->left_.get());
                    current_ = current_->left_.get();
                }
                else if (current_->right_)
                {
                    nodeStack_.push(current_->right_.get());
                    current_ = current_->right_.get();
                }
                else
                {
                    while (!nodeStack_.empty())
                    {
                        Node* parent = nodeStack_.top();
                        nodeStack_.pop();
                        if (parent->right_ && parent->right_.get() != current_)
                        {
                            current_ = parent->right_.get();
                            nodeStack_.push(current_);
                            break;
                        }
                        current_ = parent;
                    }

                    if (nodeStack_.empty())
                    {
                        current_ = nullptr;
                    }
                }
            }
            else if (order_ == Traversal::InOrder)
            {
                if (!nodeStack_.empty() || current_ != nullptr)
                {
                    while (current_ != nullptr)
                    {
                        nodeStack_.push(current_);
                        
                        current_ = current_->left_.get();

                    }
                    if (!nodeStack_.empty())
                    {
                        current_ = nodeStack_.top();
                        nodeStack_.pop();
                        parent = current_->right_.get();
                    }
                }
            }
            else if (order_ == Traversal::PostOrder)
            {
                while (!nodeStack_.empty() && (current_ == nodeStack_.top()->right_.get() || nodeStack_.top()->right_ ==nullptr))
                {
                    current_ = nodeStack_.top();
                    nodeStack_.pop();
                }
                if (!nodeStack_.empty())
                {
                    current_ = nodeStack_.top()->right_.get();
                    pushLeftNodes(current_);
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
            {
                Node* current = root_.get();
                while (current && current->left_)
                {
                    current = current->left_.get();
                }
                return Iterator(current, order);
            }
            case Traversal::PostOrder:
            {
                Node* current = root_.get();
                while (current && (current->left_ || current->right_))
                {
                    if (current->left_)
                    {
                        current = current->left_.get();
                    }
                    else
                    {
                        current = current->right_.get();
                    }
                }
                return Iterator(current, order);
            }
            default:
                return Iterator(nullptr, order);
        }
    }

    Iterator end()
    {
        return Iterator(nullptr, Traversal::PreOrder);
    }

private:
    void insert(T&& value, std::unique_ptr<Node>& node)
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

    Comparator compare_;
    std::unique_ptr<Node> root_;
};