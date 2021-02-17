#include <iostream>
#include <iterator>
#include <math.h>
#include <vector>

#include "utils.hpp"

template <typename T>
void insertionSort(std::vector<T> &arr) {
    T curr;
    for (std::int64_t i = 0; i < arr.size(); i++) {
        curr = arr[i];
        std::int64_t j = i - 1, orderIndex = i;
        while (j >= 0 && arr[j] >= curr) {
            arr[orderIndex--] = arr[j--];
        }
        arr[orderIndex] = curr;
    }
}

template <typename T>
void bucketSort(std::vector<T> &arr, std::int64_t bucketSize) {
    T minValue = arr[0];
    T maxValue = arr[0];
    for (std::int64_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < minValue) {
            minValue = arr[i];
        } else if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }

    std::int64_t bucketCount = floor((maxValue - minValue) / bucketSize) + 1;
    std::vector<std::vector<T>> buckets(bucketCount);

    for (std::int64_t i = 0; i < arr.size(); ++i) {
        buckets[floor((arr[i] - minValue) / bucketSize)].push_back(arr[i]);
    }

    arr.clear();
    for (std::int64_t i = 0; i < bucketCount; i++) {
        insertionSort<T>(buckets[i]);
        for (std::int64_t j = 0; j < buckets[i].size(); j++) {
            arr.push_back(buckets[i][j]);
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
    std::cout << "before sort" << arr << std::endl;
    bucketSort<std::int64_t>(arr, 5);
    std::cout << "after sort" << arr << std::endl;
    utils::check_ascend<std::int64_t>(arr);

    return 0;
}
