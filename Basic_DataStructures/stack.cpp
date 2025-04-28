#include <iostream>

// Node structure
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T val) : data(val), next(nullptr) {}
};

// Stack class
template <typename T>
class Stack {
private:
    Node<T>* top;

public:
    Stack() : top(nullptr) {}

    // Push (insert) an element onto the stack
    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = top;
        top = newNode;
    }

    // Pop (remove) an element from the top of the stack
    void pop() {
        if (top == nullptr) {
            std::cout << "Stack is empty, cannot pop.\n";
            return;
        }
        Node<T>* temp = top;
        top = top->next;
        delete temp;
    }

    // Get the top element of the stack
    T getTop() {
        if (top == nullptr) {
            std::cout << "Stack is empty.\n";
            return T();  // Return default value of T
        }
        return top->data;
    }

    // Check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Print all elements of the stack
    void printStack() {
        if (top == nullptr) {
            std::cout << "Stack is empty.\n";
            return;
        }
        Node<T>* current = top;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Destructor to free the allocated memory
    ~Stack() {
        while (top != nullptr) {
            Node<T>* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

// Main function
//int main() {
//    Stack<int> s;
//
//    s.push(10);
//    s.push(20);
//    s.push(30);
//
//    std::cout << "Top element: " << s.getTop() << std::endl;
//
//    std::cout << "Stack elements: ";
//    s.printStack();
//
//    s.pop();
//    std::cout << "Top element after pop: " << s.getTop() << std::endl;
//
//    std::cout << "Stack elements after pop: ";
//    s.printStack();
//
//    s.pop();
//    s.pop();
//    s.pop();  // Attempt to pop from an empty stack
//
//    if (s.isEmpty()) {
//        std::cout << "Stack is empty.\n";
//    }
//
//    return 0;
//}