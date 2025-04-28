#include <iostream>

// Node structure
template<typename T>
struct Node {
    T data;
    Node *next;

    Node(T val) : data(val), next(nullptr) {}
};

// Queue class
template<typename T>
class Queue {
private:
    Node<T> *front;
    Node<T> *rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Enqueue (insert) an element at the rear of the queue
    void enqueue(T val) {
        Node<T> *newNode = new Node<T>(val);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Dequeue (remove) an element from the front of the queue
    void dequeue() {
        if (front == nullptr) {
            std::cout << "Queue is empty, cannot dequeue.\n";
            return;
        }
        Node<T> *temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    // Get the front element of the queue
    T getFront() {
        if (front == nullptr) {
            std::cout << "Queue is empty.\n";
            return T();  // Return default value of T
        }
        return front->data;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // Print all elements of the queue
    void printQueue() {
        if (front == nullptr) {
            std::cout << "Queue is empty.\n";
            return;
        }
        Node<T> *current = front;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Destructor to free the allocated memory
    ~Queue() {
        while (front != nullptr) {
            Node<T> *temp = front;
            front = front->next;
            delete temp;
        }
    }
};

// Main function
//int main() {
//    Queue<int> q;
//
//    q.enqueue(10);
//    q.enqueue(20);
//    q.enqueue(30);
//
//    std::cout << "Front element: " << q.getFront() << std::endl;
//
//    std::cout << "Queue elements: ";
//    q.printQueue();
//
//    q.dequeue();
//    std::cout << "Front element after dequeue: " << q.getFront() << std::endl;
//
//    std::cout << "Queue elements after dequeue: ";
//    q.printQueue();
//
//    q.dequeue();
//    q.dequeue();
//    q.dequeue();  // Attempt to dequeue from an empty queue
//
//    if (q.isEmpty()) {
//        std::cout << "Queue is empty.\n";
//    }
//
//    return 0;
//}