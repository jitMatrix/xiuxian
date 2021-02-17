#include <iostream>
#include <iterator>
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

void countingSort(std::vector<std::int64_t> &arr, int maxValue) {
    const int bucketLen = maxValue + 1;
    std::vector<std::int64_t> bucket(bucketLen, 0);
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
    std::int64_t count = 10;
    std::vector<std::int64_t> arr;
    generator::init(arr,
            std::make_pair(std::pow(10, generator::minval_radix),
                    std::pow(10, generator::maxval_radix)),
            count);
    countingSort(arr, maxValue(arr));
    std::cout << "after sort" << arr << std::endl;
    check_ascend<std::int64_t>(arr);

    return 0;
}
