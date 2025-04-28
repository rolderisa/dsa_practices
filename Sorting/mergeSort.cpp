#include <iostream>
#include <string>
using namespace std;

// Merge Function for Merging Two Sorted Subarrays
template <typename T>
void merge(T arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    T* L = new T[n1];
    T* R = new T[n2];

    // Copy data into temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // Merge the temporary arrays back into arr[]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k++] = L[i++];
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k++] = R[j++];
    }

    // Free the dynamically allocated memory
    delete[] L;
    delete[] R;
}

// Merge Sort Function
template <typename T>
void mergeSort(T arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);         // Sort first half
        mergeSort(arr, mid + 1, right);    // Sort second half

        merge(arr, left, mid, right);      // Merge the sorted halves
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
    int intArr[] = {38, 27, 43, 3, 9, 82, 10};
    int intSize = sizeof(intArr) / sizeof(intArr[0]);
    mergeSort(intArr, 0, intSize - 1);
    cout << "Sorted int array: ";
    printArray(intArr, intSize);

    // Float array
    float floatArr[] = {5.1, 2.3, 7.8, 1.2};
    int floatSize = sizeof(floatArr) / sizeof(floatArr[0]);
    mergeSort(floatArr, 0, floatSize - 1);
    cout << "Sorted float array: ";
    printArray(floatArr, floatSize);

    // String array
    string strArr[] = {"pear", "apple", "grape", "orange"};
    int strSize = sizeof(strArr) / sizeof(strArr[0]);
    mergeSort(strArr, 0, strSize - 1);
    cout << "Sorted string array: ";
    printArray(strArr, strSize);

    return 0;
}
