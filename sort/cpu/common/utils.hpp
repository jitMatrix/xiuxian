#ifndef UTILS_HPP
#define UTILS_HPP

#include "generators.hpp"

template <typename T>
void check_ascend(std::vector<T> arr) {
    for (std::int64_t i = 0; i < arr.size() - 1; ++i) {
        if (arr[i] > arr[i + 1]) { throw std::runtime_error("fail to sort"); }
    }
    std::cout << "sort successfully" << std::endl;
}

#endif // UTILS_HPP