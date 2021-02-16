#include <iostream>
#include <iterator>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
    if (!v.empty()) {
        out << '[';
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

int maxValue(std::vector<int> &arr) {
    int max = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] > max) { max = arr[i]; }
    }
    return max;
}

void countingSort(std::vector<int> &arr, int maxValue) {
    const int bucketLen = maxValue + 1;
    std::vector<int> bucket(bucketLen, 0);
    int sortedIndex = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if (!bucket[arr[i]]) { bucket[arr[i]] = 0; }
        bucket[arr[i]] += 1;
    }
    for (int i = 0; i < bucketLen; ++i) {
        while (bucket[i] > 0) {
            arr[sortedIndex++] = i;
            bucket[i] -= 1;
        }
    }
}

int main() {
    std::vector<int> arr = {10, 3, 7, 24, 78, 3, 24, 26};
    std::cout << "before sort" << arr << std::endl;
    countingSort(arr, maxValue(arr));
    std::cout << "after sort" << arr << std::endl;

    return 0;
}
