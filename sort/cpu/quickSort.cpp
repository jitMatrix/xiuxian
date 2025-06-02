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

template <typename T>
std::vector<T> quickSortOutplace(std::vector<T> &arr) {
    std::int64_t pivot = arr[arr.size() / 2];
    std::vector<T> left, mid, right;
    for (std::int64_t i = 0; i < arr.size(); ++i) {
        if (arr[i] < pivot) {
            left.push_back(arr[i]);
        } else if (arr[i] > pivot) {
            right.push_back(arr[i]);
        } else {
            mid.push_back(arr[i]);
        }
    }
    std::vector<T> out;
    out.reserve(arr.size());
    if (!left.empty()) {
        std::vector<T> left_sorted = quickSortOutplace(left);
        out.insert(out.end(), left_sorted.begin(), left_sorted.end());
    }
    if (!mid.empty()) { out.insert(out.end(), mid.begin(), mid.end()); }
    if (!right.empty()) {
        std::vector<T> right_sorted = quickSortOutplace(right);
        out.insert(out.end(), right_sorted.begin(), right_sorted.end());
    }
    return out;
}

int main() {
    std::int64_t count = 10;
    std::vector<std::int64_t> arr;
    generator::init(arr,
            std::make_pair(std::pow(10, generator::minval_radix),
                    std::pow(10, generator::maxval_radix)),
            count);
    std::cout << "inplace before sort" << arr << std::endl;
    quickSort<std::int64_t>(arr, 0, arr.size() - 1);
    std::cout << "inplace after sort" << arr << std::endl;
    utils::check_ascend<std::int64_t>(arr);

    std::vector<std::int64_t> arr2;
    generator::init(arr2,
            std::make_pair(std::pow(10, generator::minval_radix),
                    std::pow(10, generator::maxval_radix)),
            count);
    std::cout << "outplace before sort" << arr2 << std::endl;
    auto arr_out = quickSortOutplace<std::int64_t>(arr2);
    std::cout << "outplace after sort" << arr_out << std::endl;
    utils::check_ascend<std::int64_t>(arr_out);

    return 0;
}
