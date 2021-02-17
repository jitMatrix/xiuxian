#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <cstdint>
#include <random>
#include <vector>

namespace generator {

const std::int64_t minval_radix = 7;
const std::int64_t maxval_radix = 8;

template <class Container = std::vector<std::int64_t>>
void generate_random_sequence(Container &arr, std::int64_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, size);

#ifdef XIUXIAN_WITH_OPENMP
#pragma omp parallel for
#endif
    for (std::int64_t index = 0; index < size; index++)
        arr[index] = dist(gen);
}

void init(std::vector<std::int64_t> &arr,
        std::pair<std::int64_t, std::int64_t> range, std::int64_t &count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(range.first, range.second);

    if (arr.size() <= 0) {
        if (count == 0) count = dist(gen);

        arr.clear();
        arr.resize(count);
    }

    generate_random_sequence(arr, count);
}

} // namespace generator

#endif // GENERATORS_HPP
