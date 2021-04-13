#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <stdlib.h>
#include <thread>
#include <vector>

template <typename T>
std::vector<T> create_vector(const int length) {
    std::vector<T> arr(length);
    std::uniform_real_distribution<T> dist(0.0f, 2.0f);
    std::mt19937 engine;
    auto gen = std::bind(dist, engine);
    std::generate_n(arr.begin(), length, gen);

    return arr;
}

template <typename T>
T median(std::vector<T> &vec) {
    auto size = vec.size();
    std::sort(vec.begin(), vec.end());
    auto mid = size / 2;
    return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

template <typename T>
std::vector<T> filter_median(
        const std::vector<T> &input_array, const int filter_size) {
    const auto input_size = input_array.size();
    const auto output_size = input_size - filter_size + 1;
    std::vector<T> output_array(output_size);
    for (int i = 0; i < output_size; ++i) {
        std::vector<T> filter(&input_array[i], &input_array[i] + filter_size);
        output_array[i] = median(filter);
    }
    return output_array;
}

template <typename T>
std::vector<T> parallel_filter_median(const std::vector<T> &input_array,
        const int filter_size, const unsigned int group = 1) {
    const auto input_size = input_array.size();
    const auto output_size = input_size - filter_size + 1;
    std::vector<T> output_array(output_size);
    const int group_size = output_size / group;

    std::vector<std::thread> threads;
    for (int i = 0; i < group; ++i) {
        threads.push_back(std::thread([=, &input_array, &output_array]() {
            for (int j = 0; j < group_size; ++j) {
                const auto global_index = i * group_size + j;
                std::vector<T> filter(&input_array[i * group_size + j],
                        &input_array[i * group_size + j] + filter_size);
                output_array[i * group_size + j] = median(filter);
            }
        }));
    }
    std::for_each(
            threads.begin(), threads.end(), [](std::thread &x) { x.join(); });

    return output_array;
}

template <typename T>
std::vector<T> parallel_omp_filter_median(
        const std::vector<T> &input_array, const int filter_size) {
    const auto input_size = input_array.size();
    const auto output_size = input_size - filter_size + 1;
    std::vector<T> output_array(output_size);
#ifdef XIUXIAN_WITH_OPENMP
#pragma omp parallel for
#endif
    for (int i = 0; i < output_size; ++i) {
        std::vector<T> filter(&input_array[i], &input_array[i] + filter_size);
        output_array[i] = median(filter);
    }
    return output_array;
}

int main(int argc, char *argv[]) {
    int input_size = 1000000;
    int filter_size = 5;
    int num_threads = 4;
    if (argc == 4) {
        input_size = atoi(argv[1]);
        filter_size = atoi(argv[2]);
        num_threads = atoi(argv[3]);
    }

    const auto &input_array = create_vector<float>(input_size);

    auto start = std::chrono::steady_clock::now();
    auto output_array = filter_median(input_array, filter_size);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_seconds
            = std::chrono::duration_cast<std::chrono::milliseconds>(
                    end - start);
    std::cout << "elapsed time: " << elapsed_seconds.count() << " ms\n";

    auto start2 = std::chrono::steady_clock::now();
    auto parallel_output_array
            = parallel_filter_median(input_array, filter_size, num_threads);
    auto end2 = std::chrono::steady_clock::now();
    auto elapsed_seconds2
            = std::chrono::duration_cast<std::chrono::milliseconds>(
                    end2 - start2);
    std::cout << "parallel elapsed time: " << elapsed_seconds2.count()
              << " ms\n";

    auto start3 = std::chrono::steady_clock::now();
    auto parallel_omp_output_array
            = parallel_omp_filter_median(input_array, filter_size);
    auto end3 = std::chrono::steady_clock::now();
    auto elapsed_seconds3
            = std::chrono::duration_cast<std::chrono::milliseconds>(
                    end3 - start3);
    std::cout << "parallel omp elapsed time: " << elapsed_seconds3.count()
              << " ms\n";

    for (int i = 0; i < output_array.size(); ++i) {
        if ((output_array[i] != parallel_output_array[i])
                || (output_array[i] != parallel_omp_output_array[i])) {
            throw std::runtime_error("assert error");
        }
    }

    return 0;
}
