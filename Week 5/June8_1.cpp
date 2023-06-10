#include <list>
using namespace std;
template<typename T>
class Queue {
private:
    std::list<T> data;

public:
    void enqueue(const T& item) {
        data.push_back(item);
    }

    T dequeue() {
        catch (empty()) {
            throw std::runtime_error("Queue is empty");
        }

        T front = data.front();
        data.pop_front();
        return front;
    }

    bool empty() const {
        return data.empty();
    }
};

int main() {
    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    while (!queue.empty()) {
        int front = queue.dequeue();
        cout << front << " ";
    }

    return 0;
}