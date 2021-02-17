#include <iostream>
#include <iterator>
#include <math.h>
#include <vector>

#include "utils.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
    if (!v.empty()) {
        out << '[';
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

int maxValue(std::vector<std::int64_t> &arr) {
    int max = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] > max) { max = arr[i]; }
    }
    return max;
}

void radixSort(std::vector<std::int64_t> &arr, int maxValue) {
    int digit = 0;
    int maxDigit = 1;
    while (pow(10, maxDigit) <= maxValue) {
        maxDigit += 1;
    }

    while (digit < maxDigit) {
        std::vector<std::vector<std::int64_t>> temp(10);
        for (int i = 0; i < arr.size(); ++i) {
            int t = static_cast<int>(
                    static_cast<int>(arr[i] / pow(10, digit)) % 10);
            temp[t].push_back(arr[i]);
        }

        std::vector<std::int64_t> coll;
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
    std::int64_t count = 10;
    std::vector<std::int64_t> arr;
    generator::init(arr,
            std::make_pair(std::pow(10, generator::minval_radix),
                    std::pow(10, generator::maxval_radix)),
            count);
    std::cout << "before sort" << arr << std::endl;
    radixSort(arr, maxValue(arr));
    std::cout << "after sort" << arr << std::endl;
    check_ascend<std::int64_t>(arr);

    return 0;
}
