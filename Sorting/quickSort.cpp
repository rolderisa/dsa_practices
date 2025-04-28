#include <iostream>
#include <string>
using namespace std;

// Partition function for Quick Sort
template <typename T>
int partition(T arr[], int low, int high) {
    T pivot = arr[high];  // Pivot element
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);  // Swap elements
        }
    }
    swap(arr[i + 1], arr[high]);  // Swap the pivot element with the element at i + 1
    return (i + 1);  // Return the partition index
}

// Quick Sort function
template <typename T>
void quickSort(T arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // Partition index
        quickSort(arr, low, pi - 1);  // Recursively sort the left subarray
        quickSort(arr, pi + 1, high); // Recursively sort the right subarray
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
    int intArr[] = {10, 7, 8, 9, 1, 5};
    int intSize = sizeof(intArr) / sizeof(intArr[0]);
    quickSort(intArr, 0, intSize - 1);
    cout << "Sorted int array: ";
    printArray(intArr, intSize);

    // Float array
    float floatArr[] = {3.4, 1.1, 5.7, 2.8};
    int floatSize = sizeof(floatArr) / sizeof(floatArr[0]);
    quickSort(floatArr, 0, floatSize - 1);
    cout << "Sorted float array: ";
    printArray(floatArr, floatSize);

    // String array
    string strArr[] = {"pear", "apple", "grape", "orange"};
    int strSize = sizeof(strArr) / sizeof(strArr[0]);
    quickSort(strArr, 0, strSize - 1);
    cout << "Sorted string array: ";
    printArray(strArr, strSize);

    return 0;
}
