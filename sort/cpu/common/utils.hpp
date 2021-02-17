#ifndef UTILS_HPP
#define UTILS_HPP

#include "generators.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
    if (!v.empty()) {
        out << '[';
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

namespace utils {

template <typename T>
void swap(T &a, T &b) {
    if (a > b) {
        T tmp = a;
        a = b;
        b = tmp;
    }
}

template <typename T>
T maxValue(std::vector<T> &arr) {
    T max = 0;
    for (std::int64_t i = 0; i < arr.size(); ++i) {
        if (arr[i] > max) { max = arr[i]; }
    }
    return max;
}

template <typename T>
void check_ascend(std::vector<T> arr) {
    for (std::int64_t i = 0; i < arr.size() - 1; ++i) {
        if (arr[i] > arr[i + 1]) { throw std::runtime_error("fail to sort"); }
    }
    std::cout << "sort successfully" << std::endl;
}

} // namespace utils

#endif // UTILS_HPP