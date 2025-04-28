#include <iostream>
#include <string>
using namespace std;

// Generic Selection Sort Function
template <typename T>
void selectionSort(T arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;

        // Find index of the minimum element
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Swap if a smaller element was found
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
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
    // Integer array
    int intArr[] = {64, 25, 12, 22, 11};
    int intSize = sizeof(intArr) / sizeof(intArr[0]);
    selectionSort(intArr, intSize);
    cout << "Sorted int array: ";
    printArray(intArr, intSize);

    // Float array
    float floatArr[] = {3.5, 1.2, 4.7, 2.8};
    int floatSize = sizeof(floatArr) / sizeof(floatArr[0]);
    selectionSort(floatArr, floatSize);
    cout << "Sorted float array: ";
    printArray(floatArr, floatSize);

    // String array
    string strArr[] = {"grape", "apple", "orange", "banana"};
    int strSize = sizeof(strArr) / sizeof(strArr[0]);
    selectionSort(strArr, strSize);
    cout << "Sorted string array: ";
    printArray(strArr, strSize);

    return 0;
}
