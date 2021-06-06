#pragma once

#include "../BaseTask.h"

int32_t toDigit(const std::string& str)
{
    int32_t val = 0;
    for (auto ch : str) {
        val = val * 10 + ch - 0x30;
    }

    return val;
}

void fillArray(std::uint32_t* arr, const std::string& val)
{
    size_t left = 0;
    size_t curIndex = 0;
    for (size_t i = 0; i < val.size(); ++i) {
        if (val[i] == ' ') {
            arr[curIndex++] = toDigit(val.substr(left, i - left));
            left = i + 1;
        }
    }
    arr[curIndex] = toDigit(val.substr(left, val.size() - left));
}

std::string toString(std::uint32_t* arr, size_t size)
{
    std::string str = std::to_string(arr[0]);
    for (size_t i = 1; i < size; ++i) {
        str += ' ' + std::to_string(arr[i]);
    }

    return str;
}

template<typename T>
struct ISort
{
    ISort()
        : arr_(nullptr)
    {
    }

    std::string sort(const std::string& sizeStr, const std::string& val)
    {
        size_t size = toDigit(sizeStr);
        std::uint32_t arr[size];
        arr_ = arr;
        fillArray(arr, val);
        derived()->sort(arr, size);

        return toString(arr, size);
    }

    void swapVal(size_t lhs, size_t rhs)
    {
        auto tmp = arr_[lhs];
        arr_[lhs] = arr_[rhs];
        arr_[rhs] = tmp;
    }

private:
    T* derived() { return static_cast<T*>(this); }
    std::uint32_t* arr_;
};

template<typename T>
struct BubbleSort
    : public BaseTask<T>
    , public ISort<BubbleSort<T>>
{
    void sort(const std::uint32_t* arr, size_t size)
    {
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size - i - 1; ++j) {
                if (arr[j + 1] < arr[j]) {
                    ISort<BubbleSort<T>>::swapVal(j, j + 1);
                }
            }
        }
    }

    std::string run(const std::vector<std::string>& input) { return ISort<BubbleSort<T>>::sort(input[0], input[1]); }
};

struct BubbleSortRandomTask : public BubbleSort<BubbleSortRandomTask>
{
    std::string getPathImpl() const { return "../Sorting/sorting-tests/0.random"; }
};

struct BubbleSortDigitsTask : public BubbleSort<BubbleSortDigitsTask>
{
    std::string getPathImpl() const { return "../Sorting/sorting-tests/1.digits"; }
};
