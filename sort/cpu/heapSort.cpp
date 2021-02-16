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
void heapAdjust(std::vector<T> &arr, int length, int root) {
    T curParent = arr[root];
    int child = 2 * root + 1;
    while (child < length) {
        if (child + 1 < length && arr[child] < arr[child + 1]) {
            child++;
        }
        if (curParent < arr[child]) {
            arr[root] = arr[child];
            root = child;
            child = 2 * root + 1;
        } else {
            break;
        }
    }
    arr[root] = curParent;
}

template <typename T>
void heapSort(std::vector<T> &arr, int length) {
    for (int i = length / 2 - 1; i >= 0; --i) {
        heapAdjust<T>(arr, length, i);
    }
    for (int i = length - 1; i >= 0; --i) {
        swap<T>(arr[0], arr[i]);
        heapAdjust<T>(arr, i, 0);
    }
}

int main() {
    std::vector<float> arr = {1.0f, 0.3f, 0.7f, 0.24f, 0.78f, 0.3f, 2.4f, 2.6f};
    std::cout << "before sort" << arr << std::endl;
    heapSort<float>(arr, arr.size());
    std::cout << "after sort" << arr << std::endl;

    return 0;
}
