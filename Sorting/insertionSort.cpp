#include <iostream>
#include <string>
using namespace std;

// Generic Insertion Sort Function
template <typename T>
void insertionSort(T arr[], int size) {
    for (int i = 1; i < size; i++) {
        T key = arr[i];
        int j = i - 1;

        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// Utility function to print an array
template <typename T>
void printArray(T arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    // Integer example
    int intArr[] = {9, 3, 1, 5, 2};
    int intSize = sizeof(intArr) / sizeof(intArr[0]);
    insertionSort(intArr, intSize);
    cout << "Sorted int array: ";
    printArray(intArr, intSize);

    // Float example
    float floatArr[] = {4.5, 2.3, 5.6, 1.2};
    int floatSize = sizeof(floatArr) / sizeof(floatArr[0]);
    insertionSort(floatArr, floatSize);
    cout << "Sorted float array: ";
    printArray(floatArr, floatSize);

    // String example
    string strArr[] = {"peach", "apple", "mango", "banana"};
    int strSize = sizeof(strArr) / sizeof(strArr[0]);
    insertionSort(strArr, strSize);
    cout << "Sorted string array: ";
    printArray(strArr, strSize);

    return 0;
}
