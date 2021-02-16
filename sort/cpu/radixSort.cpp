#include <iostream>
#include <iterator>
#include <math.h>
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

void radixSort(std::vector<int> &arr, int maxValue) {
    int digit = 0;
    int maxDigit = 1;
    while (pow(10, maxDigit) < maxValue) {
        maxDigit += 1;
    }

    while (digit < maxDigit) {
        std::vector<std::vector<int>> temp(10);
        for (int i = 0; i < arr.size(); ++i) {
            int t = static_cast<int>(
                    static_cast<int>(arr[i] / pow(10, digit)) % 10);
            temp[t].push_back(arr[i]);
        }

        std::vector<int> coll;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < temp[i].size(); ++j) {
                coll.push_back(temp[i][j]);
            }
        }

        arr = coll;
        digit += 1;
    }
}

int main() {
    std::vector<int> arr = {10, 3, 7, 24, 78, 3, 24, 26};
    std::cout << "before sort" << arr << std::endl;
    radixSort(arr, maxValue(arr));
    std::cout << "after sort" << arr << std::endl;

    return 0;
}
