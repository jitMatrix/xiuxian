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
void shellSort(std::vector<T> &arr) {
    int gap, length = arr.size();
    gap = length / 2;
    while (gap) {
        T curr;
        for (int i = 0; i < length; i = i + gap) {
            curr = arr[i];
            int j = i - gap, orderIndex = i;
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
    std::vector<float> arr = {1.0f, 0.3f, 0.7f, 0.24f, 0.78f, 0.3f, 2.4f, 2.6f};
    std::cout << "before sort" << arr << std::endl;
    shellSort<float>(arr);
    std::cout << "after sort" << arr << std::endl;

    return 0;
}
