#include <iostream>
#include <string>
#include <queue>

int main() {
    std::queue<int> myQueue;

    std::string command;
    while (true) {
        std::cout << "Enter a command (enqueue NUMBER, dequeue): ";
        std::cin >> command;

        if (command == "enqueue") {
            int number;
            std::cin >> number;
            myQueue.push(number);
            std::cout << "Enqueued " << number << " successfully." << std::endl;
        } else if (command == "dequeue") {
            if (myQueue.empty()) {
                std::cout << "Queue is empty. Cannot dequeue." << std::endl;
            } else {
                int front = myQueue.front();
                myQueue.pop();
                std::cout << "Dequeued " << front << " successfully." << std::endl;
            }
        } else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }

    return 0;
}