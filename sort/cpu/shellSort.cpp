#include <iostream>
#include <iterator>
#include <vector>

#include "utils.hpp"

template <typename T>
void shellSort(std::vector<T> &arr) {
    std::int64_t gap, length = arr.size();
    gap = length / 2;
    while (gap) {
        T curr;
        for (std::int64_t i = 0; i < length; i = i + gap) {
            curr = arr[i];
            std::int64_t j = i - gap, orderIndex = i;
            while (j >= 0 && arr[j] >= curr) {
                arr[orderIndex] = arr[j];
                orderIndex -= gap;
                j -= gap;
            }
            arr[orderIndex] = curr;
        }
        gap /= 2;
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
    shellSort<std::int64_t>(arr);
    std::cout << "after sort" << arr << std::endl;
    utils::check_ascend<std::int64_t>(arr);

    return 0;
}
