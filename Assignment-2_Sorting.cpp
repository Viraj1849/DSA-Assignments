#include <iostream>

using namespace std;

int main() {

    int tempRead[] = {30, 25, 27, 22, 28, 31, 26}; // Sample temperature data

    int l = sizeof(tempRead) / sizeof(tempRead[0]);

    // Sorting temperatures using Bubble Sort algorithm
    for (int i = 0; i < l - 1; ++i) {
        for (int j = 0; j < l - i - 1; ++j) {
            if (tempRead[j] > tempRead[j + 1]) {
                int tempValue = tempRead[j];
                tempRead[j] = tempRead[j + 1];
                tempRead[j + 1] = tempValue;
            }
        }
    }

    // Print the sorted temperature values
    cout << "Temperatures sorted in ascending order:\n";
    for (int i = 0; i < l; ++i) {
        cout << tempRead[i] << " ";
    }
    cout << endl;
}
