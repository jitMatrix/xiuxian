#include <iostream>
#include <iterator>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
    if (!v.empty()) {
        out << '[';
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

template <typename T>
void swap(T &a, T &b) {
    if (a > b) {
        T tmp = a;
        a = b;
        b = tmp;
    }
}

template <typename T>
void bubbleSort(std::vector<T> &arr) {
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = 0; j < arr.size() - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) { swap(arr[j], arr[j + 1]); }
        }
    }
}

int main() {
    std::vector<float> arr = {1.0f, 0.3f, 0.7f, 0.24f, 0.78f, 0.3f, 2.4f, 2.6f};
    std::cout << "before sort" << arr << std::endl;
    bubbleSort<float>(arr);
    std::cout << "after sort" << arr << std::endl;

    return 0;
}
