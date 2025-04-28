#include <iostream>

// Node structure
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T val) : data(val), next(nullptr) {}
};

// LinkedList class
template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    // Insert a new node at the beginning
    void insertAtBeginning(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = head;
        head = newNode;
    }

    // Insert a new node at the end
    void insertAtEnd(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Insert a new node after a given node
    void insertAfter(Node<T>* prevNode, T val) {
        if (prevNode == nullptr) {
            std::cout << "The given previous node cannot be nullptr\n";
            return;
        }
        Node<T>* newNode = new Node<T>(val);
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }

    // Delete the first occurrence of a given value
    void deleteNode(T val) {
        if (head == nullptr) {
            std::cout << "List is empty, cannot delete\n";
            return;
        }
        if (head->data == val) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node<T>* current = head;
        while (current->next != nullptr && current->next->data != val) {
            current = current->next;
        }
        if (current->next == nullptr) {
            std::cout << "Value not found in the list\n";
            return;
        }
        Node<T>* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    // Search for a value in the list
    bool search(T val) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == val) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Print all elements in the list
    void printList() {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Destructor to free the allocated memory
    ~LinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Main function
//int main() {
//    LinkedList<int> list;
//
//    list.insertAtEnd(10);
//    list.insertAtBeginning(20);
//    list.insertAtEnd(30);
//    list.insertAtBeginning(40);
//
//    std::cout << "List elements: ";
//    list.printList();
//
//    list.deleteNode(20);
//    std::cout << "List elements after deleting 20: ";
//    list.printList();
//
//    if (list.search(30)) {
//        std::cout << "Element 30 found in the list\n";
//    } else {
//        std::cout << "Element 30 not found in the list\n";
//    }
//
//    return 0;
//}