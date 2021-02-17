#include <iostream>
#include <iterator>
#include <math.h>
#include <vector>

#include "utils.hpp"

void radixSort(std::vector<std::int64_t> &arr, std::int64_t maxValue) {
    std::int64_t digit = 0;
    std::int64_t maxDigit = 1;
    while (pow(10, maxDigit) <= maxValue) {
        maxDigit += 1;
    }

    while (digit < maxDigit) {
        std::vector<std::vector<std::int64_t>> temp(10);
        for (std::int64_t i = 0; i < arr.size(); ++i) {
            std::int64_t t = static_cast<std::int64_t>(
                    static_cast<std::int64_t>(arr[i] / pow(10, digit)) % 10);
            temp[t].push_back(arr[i]);
        }

        std::vector<std::int64_t> coll;
        for (std::int64_t i = 0; i < 10; ++i) {
            for (std::int64_t j = 0; j < temp[i].size(); ++j) {
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
    radixSort(arr, utils::maxValue<std::int64_t>(arr));
    std::cout << "after sort" << arr << std::endl;
    utils::check_ascend<std::int64_t>(arr);

    return 0;
}
