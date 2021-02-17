#include <iostream>
#include <iterator>
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

int main() {
    std::int64_t count = 10;
    std::vector<std::int64_t> arr;
    generator::init(arr,
            std::make_pair(std::pow(10, generator::minval_radix),
                    std::pow(10, generator::maxval_radix)),
            count);
    std::cout << "before sort" << arr << std::endl;
    insertionSort<std::int64_t>(arr);
    std::cout << "after sort" << arr << std::endl;
    utils::check_ascend<std::int64_t>(arr);

    return 0;
}
