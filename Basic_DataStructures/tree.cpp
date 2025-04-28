#include <iostream>

// Definition of a node in the binary search tree
template<typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;

    // Constructor
    TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

// Binary search tree class
template<typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    // Helper function to recursively insert a value into the BST
    TreeNode<T>* insertRecursive(TreeNode<T>* root, T value) {
        // If the tree is empty, create a new node
        if (root == nullptr) {
            return new TreeNode<T>(value);
        }

        // Otherwise, recur down the tree
        if (value < root->data) {
            root->left = insertRecursive(root->left, value);
        } else if (value > root->data) {
            root->right = insertRecursive(root->right, value);
        }

        // Return the (unchanged) node pointer
        return root;
    }

    // Helper function to perform inorder traversal recursively
    void inorderRecursive(TreeNode<T>* root) {
        if (root != nullptr) {
            inorderRecursive(root->left);
            std::cout << root->data << " ";
            inorderRecursive(root->right);
        }
    }

    // Helper function to recursively search for a value in the BST
    TreeNode<T>* searchRecursive(TreeNode<T>* root, T key) {
        // Base cases: root is null or key is present at the root
        if (root == nullptr || root->data == key) {
            return root;
        }

        // Key is greater than root's key
        if (root->data < key) {
            return searchRecursive(root->right, key);
        }

        // Key is smaller than root's key
        return searchRecursive(root->left, key);
    }

public:
    // Constructor
    BinarySearchTree() : root(nullptr) {}

    // Function to insert a value into the BST
    void insert(T value) {
        root = insertRecursive(root, value);
    }

    // Function to perform inorder traversal of the BST
    void inorderTraversal() {
        inorderRecursive(root);
        std::cout << std::endl;
    }

    // Function to search for a value in the BST
    TreeNode<T>* search(T key) {
        return searchRecursive(root, key);
    }
};

// Main function to demonstrate binary search tree operations
//int main() {
//    BinarySearchTree<int> bst;
//
//    // Insert elements into the BST
//    bst.insert(50);
//    bst.insert(30);
//    bst.insert(20);
//    bst.insert(40);
//    bst.insert(70);
//    bst.insert(60);
//    bst.insert(80);
//
//    // Perform inorder traversal to print the BST
//    std::cout << "Inorder traversal of BST: ";
//    bst.inorderTraversal();
//
//    // Search for a value in the BST
//    int key = 70;
//    TreeNode<int>* result = bst.search(key);
//    if (result != nullptr) {
//        std::cout << "Found " << key << " in the BST" << std::endl;
//    } else {
//        std::cout << key << " not found in the BST" << std::endl;
//    }
//
//    return 0;
//}