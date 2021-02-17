#include <iostream>
#include <iterator>
#include <vector>

#include "utils.hpp"

template <typename T>
void selectSort(std::vector<T> &arr) {
    std::int64_t minindex = 0;
    for (std::int64_t i = 0; i < arr.size(); ++i) {
        minindex = i;
        for (std::int64_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minindex]) { minindex = j; }
        }
        utils::swap<T>(arr[i], arr[minindex]);
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
    selectSort<std::int64_t>(arr);
    std::cout << "after sort" << arr << std::endl;
    utils::check_ascend<std::int64_t>(arr);

    return 0;
}
