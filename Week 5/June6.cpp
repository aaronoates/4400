#include <iostream>
#include <memory>

using namespace std;

class Node {
    public:
    double data;
    std::shared_ptr<Node> next; 
    Node(double value) : data(value), next(nullptr){ //Node constructor initializes the node object by setting the data variable as being equal to the value parameter, and sets *next to null.

    }
};

class linkedList {
    private:
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    size_t size;
    public:
    linkedList() : head(nullptr), tail(nullptr), size(0) { // linkedList constructor initializes the linkedList object by setting the head and tail to be null pointers and the size to be 0

    }
    ~linkedList(){
        delete this;
    } 

    void pushBack(double value){
        std::shared_ptr<Node> newNode;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        size++;
    }

     void pop_back() {
        if (head == nullptr) {
            std::cout << "Error: List is empty." << std::endl;
            return;
        }

        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            std::shared_ptr<Node> current = head;
            while (current->next != tail) {
                current = current->next;
            }
            tail = current;
            tail->next = nullptr;
        }

        size--;
    }

    void insert(size_t position, double value) {
        if (position > size) {
            std::cout << "Error: Invalid position." << std::endl;
            return;
        }

        if (position == size) {
            pushBack(value);
            return;
        }

        Node* newNode = new Node(value);

        if (position == 0) {
            newNode->next = head;
            
        } else {
            shared_ptr<Node> current = head;
            for (size_t i = 1; i < position; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            
        }

        size++;
    }

    void remove(size_t position) {
        if (position >= size) {
            std::cout << "Error: Invalid position." << std::endl;
            return;
        }

        if (position == size - 1) {
            pop_back();
            return;
        }

        if (position == 0) {
            shared_ptr<Node> temp = head;
            head = head->next;
            
        } else {
            shared_ptr<Node> current = head;
            for (size_t i = 1; i < position; i++) {
                current = current->next;
            }
            shared_ptr<Node> current = current->next;
             
            
        }

        size--;
    }

    double& operator[](size_t index) {
        if (index >= size) {
            std::cout << "Error: Invalid index." << std::endl;
            // Returning a reference to a temporary, just to handle errors
            // This is not ideal, but it's for demonstration purposes.
            static double dummy;
            return dummy;
        }

        shared_ptr<Node> current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    size_t getSize() const {
        return size;
    }

    void clear() {
        while (head != nullptr) {
            shared_ptr<Node> temp = head;
            head = head->next;
            
        }
        tail = nullptr;
        size = 0;
    }
};

