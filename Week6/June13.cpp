#include <iostream>
#include <sstream>
#include <vector> 
#include <memory>
using namespace std;
template<typename T>
class Tree {
    public:
        /**
         * Set the value of the tree's root node.
        */
        Tree<T>& setRoot(T value){
            T root = unique_ptr<value>;
        }

        /**
        * Add a leaf node to the top level of this tree.
        */
        Tree<T>& addChild(T value){
            T child = unique_ptr<value>;
            root->child;
        }

        /**
       * Add a subtree to the top level of this tree, using move
        * semantics to "steal" the subtree's nodes.
        */
        Tree<T>& addSubtree(Tree&& subTree){
            T thesubTree = std::move(subTree);
            
        }

        Tree<T> addSibling(T value){
            T sibling = unique_ptr<value>
            child->sibling;
        }

        void visit(const T &value){
            static size_t i = 0;
            cout << "Node" << i++ < 
        }
        
};


int main() {
    Tree<double> Tree1;
    Tree<double> Tree2;
    Tree1.setRoot(5);
    Tree1.addChild(6);
    Tree1.addSubtree(std::move(Tree2));
    return 0;
}






//June 15.1: I would say that using shared pointers in place of unique pointers is not necessary, because each child node only points to one sibling, meaning no node is being pointed to by two different nodes. Therefore, using unique pointers should still be fine.