#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>


T radixSort(std::vector<T>& arr) {
    if (arr.empty()) {
        return;
    } elif (T == std::string) { //this block only runs if T is of type string
        size_t getMaxStringLength(const std::vector<T>& arr) {
            size_t maxLen = 0;
            for (const std::string& str : arr) {
                maxLen = std::max(maxLen, str.length());
            }
        
        }

         // Find the maximum length among all strings
        size_t maxLen = getMaxStringLength(arr);

    // Perform counting sort for each character position from right to left
        for (int pos = maxLen - 1; pos >= 0; --pos) {
            const size_t numChars = 256; // Assuming ASCII characters

            std::vector<int> count(numChars, 0);
            std::vector<std::string> output(arr.size());

        // Count the frequency of characters at the current position
            for (const std::string& str : arr) {
                int index = (pos < str.length()) ? static_cast<int>(str[pos]) : 0;
                count[index]++;
            }

        // Calculate the cumulative count
            for (int i = 1; i < numChars; ++i) {
                count[i] += count[i - 1];
            }

        // Build the sorted output array
            for (int i = arr.size() - 1; i >= 0; --i) {
                int index = (pos < arr[i].length()) ? static_cast<int>(arr[i][pos]) : 0;
                output[count[index] - 1] = arr[i];
                count[index]--;
            }

        // Copy the sorted output array to the original array
            for (size_t i = 0; i < arr.size(); ++i) {
                arr[i] = output[i];
            }
        }
    } else {
        T maxVal = *std::max_element(arr.begin(), arr.end());

    // Perform counting sort for each digit
        for (T exp = 1; maxVal / exp > 0; exp *= 10) {
            std::vector<T> output(arr.size());
            std::vector<int> count(10, 0);

        // Count the frequency of digits at the current place value
            for (size_t i = 0; i < arr.size(); ++i) {
                count[(arr[i] / exp) % 10]++;
            }

        // Calculate the cumulative count
            for (int i = 1; i < 10; ++i) {
                count[i] += count[i - 1];
            }

        // Build the sorted output array
            for (int i = arr.size() - 1; i >= 0; --i) {
                output[count[(arr[i] / exp) % 10] - 1] = arr[i];
                count[(arr[i] / exp) % 10]--;
            }

        // Copy the sorted output array to the original array
            for (size_t i = 0; i < arr.size(); ++i) {
                arr[i] = output[i];
            }
    }
    }

    // Find the maximum element to determine the maximum number of digits
    
}

int main () {
    std::vector<int> sample = {5, 4, 3, 2, 1};
    radixSort(sample);
    cout << &sample << endl;
    std::vector<string> samplestring = {"Mario", "Zelda", "Pokemon", "Super Smash Bros", "God Of War"};
    radixSort(samplestring);
    cout << &samplestring << endl;

}
