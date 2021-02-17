#include <iostream>
#include <iterator>
#include <vector>

#include "utils.hpp"

void countingSort(std::vector<std::int64_t> &arr, std::int64_t maxValue) {
    const std::int64_t bucketLen = maxValue + 1;
    std::vector<std::int64_t> bucket(bucketLen, 0);
    std::int64_t sortedIndex = 0;
    for (std::int64_t i = 0; i < arr.size(); ++i) {
        if (!bucket[arr[i]]) { bucket[arr[i]] = 0; }
        bucket[arr[i]] += 1;
    }
    for (std::int64_t i = 0; i < bucketLen; ++i) {
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
    countingSort(arr, utils::maxValue<std::int64_t>(arr));
    std::cout << "after sort" << arr << std::endl;
    utils::check_ascend<std::int64_t>(arr);

    return 0;
}
