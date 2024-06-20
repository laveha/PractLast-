#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <iomanip>

class MergeSort {
public:
    void Sort(std::vector<int>& array) {
        if (array.size() <= 1) return;
        std::vector<int> left(array.begin(), array.begin() + array.size() / 2);
        std::vector<int> right(array.begin() + array.size() / 2, array.end());

        std::thread leftThread(&MergeSort::Sort, this, std::ref(left));
        std::thread rightThread(&MergeSort::Sort, this, std::ref(right));

        leftThread.join();
        rightThread.join();

        Merge(array, left, right);
    }

private:
    void Merge(std::vector<int>& result, const std::vector<int>& left, const std::vector<int>& right) {
        auto it = result.begin();
        auto itLeft = left.begin();
        auto itRight = right.begin();

        while (itLeft != left.end() && itRight != right.end()) {
            if (*itLeft < *itRight) {
                *it++ = *itLeft++;
            }
            else {
                *it++ = *itRight++;
            }
        }

        while (itLeft != left.end()) {
            *it++ = *itLeft++;
        }

        while (itRight != right.end()) {
            *it++ = *itRight++;
        }
    }
};

void printArray(const std::vector<int>& array) {
    std::cout << "[ ";
    for (const int& num : array) {
        std::cout << num << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    MergeSort sorter;
    std::vector<int> array(10);

    std::cout << "==== Параллельная сортировка слиянием ====" << std::endl;
    std::cout << "Введите 10 целых чисел для сортировки:" << std::endl;

    for (int i = 0; i < 10; ++i) {
        std::cout << "Число " << i + 1 << ": ";
        std::cin >> array[i];
    }

    std::cout << "\nИсходный массив: ";
    printArray(array);

    std::cout << "\nСортировка массива...\n" << std::endl;

    std::thread mergeSortThread([&sorter, &array]() {
        sorter.Sort(array);
        });

    mergeSortThread.join();

    std::cout << "Отсортированный массив: ";
    printArray(array);

    std::cout << "\nСортировка завершена успешно." << std::endl;

    return 0;
}
