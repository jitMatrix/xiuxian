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
void pop_front(std::vector<T> &vec) {
    if (vec.empty()) { throw std::runtime_error("pop empty vector"); }
    vec.erase(vec.begin());
}

template <typename T>
std::vector<T> merge(std::vector<T> &left, std::vector<T> &right) {
    std::vector<T> result;
    while(left.size() and right.size()) {
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
    int middle = 0;
    middle = arr.size() / 2;
    std::vector<T> left;
    std::vector<T> right;
    for (int i = 0; i < middle; ++i) {
        left.push_back(arr[i]);
    }
    for (int i = middle; i < arr.size(); ++i) {
        right.push_back(arr[i]);
    }

    std::vector<T> a = mergeSort<T>(left);
    std::vector<T> b = mergeSort<T>(right);

    return merge<T>(a, b);
}

int main() {
    std::vector<float> arr = {1.0f, 0.3f, 0.7f, 0.24f, 0.78f, 0.3f, 2.4f, 2.6f};
    std::cout << "before sort" << arr << std::endl;
    std::vector<float> sorted = mergeSort<float>(arr);
    std::cout << "after sort" << sorted << std::endl;

    return 0;
}
