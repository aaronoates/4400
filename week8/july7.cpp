#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    int height; // AVL-specific attribute
};

class BinarySearchTree {
public:
    Node* root;

    // Constructor
    BinarySearchTree() {
        root = nullptr;
    }

    // Insert a node into the tree
    void insert(int value) {
        root = insertRecursive(root, value);
    }

    // Recursive insert helper function
    Node* insertRecursive(Node* root, int value) {
        if (root == nullptr) {
            Node* newNode = new Node;
            newNode->data = value;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->height = 1;
            return newNode;
        }

        if (value < root->data) {
            root->left = insertRecursive(root->left, value);
        } else {
            root->right = insertRecursive(root->right, value);
        }

        // Update height of the current node
        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

        return root;
    }

    // Get the height of a node (returns 0 for nullptr)
    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }
};

class AVLTree : public BinarySearchTree {
public:
    // Override the insert method to perform AVL rebalancing
    void insert(int value) {
        root = insertRecursive(root, value);
    }

    // Recursive insert helper function with AVL rebalancing
    Node* insertRecursive(Node* root, int value) {
        // Perform regular BST insertion
        root = BinarySearchTree::insertRecursive(root, value);

        // Update height of the current node
        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

        // Check balance factor
        int balanceFactor = getBalanceFactor(root);

        // Perform AVL rebalancing if necessary
        if (balanceFactor > 1) {
            if (value < root->left->data) {
                // Left-Left case: Perform a right rotation
                root = rightRotate(root);
            } else {
                // Left-Right case: Perform a left rotation followed by a right rotation
                root->left = leftRotate(root->left);
                root = rightRotate(root);
            }
        } else if (balanceFactor < -1) {
            if (value > root->right->data) {
                // Right-Right case: Perform a left rotation
                root = leftRotate(root);
            } else {
                // Right-Left case: Perform a right rotation followed by a left rotation
                root->right = rightRotate(root->right);
                root = leftRotate(root);
            }
        }

        return root;
    }

    // Get the balance factor of a node
    int getBalanceFactor(Node* node) {
        return getHeight(node->left) - getHeight(node->right);
    }

    // Perform a left rotation
    Node* leftRotate(Node* node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        // Update heights
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    // Perform a right rotation
    Node* rightRotate(Node* node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        // Update heights
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }
     Node* doubleRotate(Node* node) {
        if (getBalanceFactor(node) < 0) {
            // Right-Left case: Perform a right rotation on the right child,
            // followed by a left rotation on the current node
            node->right = rightRotate(node->right);
            return leftRotate(node);
        } else {
            // Left-Right case: Perform a left rotation on the left child,
            // followed by a right rotation on the current node
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

};

int main() {
    AVLTree tree;

    // Insert nodes
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    // Test the tree
    // You can use your previously-implemented GraphViz DOT output or
    // perform inorder traversal to check the tree structure.

    return 0;
}