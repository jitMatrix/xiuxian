#include <iostream>
#include <iterator>
#include <vector>

#include "utils.hpp"

template <typename T>
void pop_front(std::vector<T> &vec) {
    if (vec.empty()) { throw std::runtime_error("pop empty vector"); }
    vec.erase(vec.begin());
}

template <typename T>
std::vector<T> merge(std::vector<T> &left, std::vector<T> &right) {
    std::vector<T> result;
    while (left.size() and right.size()) {
        if (left[0] <= right[0]) {
            result.push_back(left[0]);
            pop_front(left);
        } else {
            result.push_back(right[0]);
            pop_front(right);
        }
    }
    while (left.size()) {
        result.push_back(left[0]);
        pop_front(left);
    }
    while (right.size()) {
        result.push_back(right[0]);
        pop_front(right);
    }

    return result;
}

template <typename T>
std::vector<T> mergeSort(std::vector<T> &arr) {
    if (arr.size() < 2) { return arr; }
    std::int64_t middle = 0;
    middle = arr.size() / 2;
    std::vector<T> left;
    std::vector<T> right;
    for (std::int64_t i = 0; i < middle; ++i) {
        left.push_back(arr[i]);
    }
    for (std::int64_t i = middle; i < arr.size(); ++i) {
        right.push_back(arr[i]);
    }

    std::vector<T> a = mergeSort<T>(left);
    std::vector<T> b = mergeSort<T>(right);

    return merge<T>(a, b);
}

int main() {
    std::int64_t count = 10;
    std::vector<std::int64_t> arr;
    generator::init(arr,
            std::make_pair(std::pow(10, generator::minval_radix),
                    std::pow(10, generator::maxval_radix)),
            count);
    std::cout << "before sort" << arr << std::endl;
    std::vector<std::int64_t> sorted = mergeSort<std::int64_t>(arr);
    std::cout << "after sort" << sorted << std::endl;
    utils::check_ascend<std::int64_t>(sorted);

    return 0;
}
