#include <iostream>
#include <iterator>
#include <vector>

#include "utils.hpp"

template <typename T>
std::int64_t partition(
        std::vector<T> &arr, std::int64_t low, std::int64_t high) {
    T pivot = arr[low];
    while (low < high) {
        while (low < high && arr[high] >= pivot) {
            --high;
        }
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot) {
            ++low;
        }
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

template <typename T>
void quickSort(std::vector<T> &arr, std::int64_t low, std::int64_t high) {
    if (low < high) {
        std::int64_t pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
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
    quickSort<std::int64_t>(arr, 0, arr.size() - 1);
    std::cout << "after sort" << arr << std::endl;
    utils::check_ascend<std::int64_t>(arr);

    return 0;
}
