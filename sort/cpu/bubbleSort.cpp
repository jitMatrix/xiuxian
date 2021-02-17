#include <iostream>
#include <iterator>
#include <vector>

#include "utils.hpp"

template <typename T>
void bubbleSort(std::vector<T> &arr) {
    for (std::int64_t i = 0; i < arr.size(); ++i) {
        for (std::int64_t j = 0; j < arr.size() - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) { utils::swap<T>(arr[j], arr[j + 1]); }
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
    bubbleSort<std::int64_t>(arr);
    std::cout << "after sort" << arr << std::endl;
    utils::check_ascend<std::int64_t>(arr);

    return 0;
}
