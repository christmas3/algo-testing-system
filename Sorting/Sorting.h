#pragma once

#include "../BaseTask.h"

template<typename T>
T toValueType(const std::string& str)
{
    int32_t val = 0;
    for (auto ch : str) {
        val = val * 10 + ch - 0x30;
    }

    return val;
}

template<typename T>
void fillArray(T* arr, const std::string& val)
{
    size_t left = 0;
    size_t curIndex = 0;
    for (size_t i = 0; i < val.size(); ++i) {
        if (val[i] == ' ') {
            arr[curIndex++] = toValueType<T>(val.substr(left, i - left));
            left = i + 1;
        }
    }
    arr[curIndex] = toValueType<T>(val.substr(left, val.size() - left));
}

template<typename T>
std::string toResult(T* arr, size_t size)
{
    std::string str = std::to_string(arr[0]);
    for (size_t i = 1; i < size; ++i) {
        str += ' ' + std::to_string(arr[i]);
    }

    return str;
}

template<typename T>
struct ISort : public BaseTask<T>
{
    using ValueType = std::int32_t;
    using SizeType = size_t;

    [[nodiscard]] virtual std::string getPathImpl() const = 0;
    [[nodiscard]] bool needTimeLapse() const { return false; }

    std::string sort(const std::string& sizeStr, const std::string& val)
    {
        auto size = toValueType<SizeType>(sizeStr);
        ValueType arr[size];
        arr_ = arr;
        fillArray(arr, val);
        double timeVal = 0;
        TimeLapseWithoutResult(derived()->sort(arr, size), timeVal);
        std::cerr << std::fixed << "time passed: " << timeVal << " seconds" << std::endl;

        return toResult(arr, size);
    }

    void swapVal(SizeType lhs, SizeType rhs)
    {
        auto tmp = arr_[lhs];
        arr_[lhs] = arr_[rhs];
        arr_[rhs] = tmp;
    }

    std::string run(const std::vector<std::string>& input) { return sort(input[0], input[1]); }

    ISort()
        : arr_(nullptr)
    {
    }

private:
    T* derived() { return static_cast<T*>(this); }
    ValueType* arr_;
};

namespace bubble {

template<typename T>
struct Sort : public ISort<Sort<T>>
{
    using SizeType = typename ISort<Sort<T>>::SizeType;
    using ValueType = typename ISort<Sort<T>>::ValueType;

    void sort(const ValueType* arr, SizeType size)
    {
        for (SizeType i = 0; i < size; ++i) {
            for (SizeType j = 0; j < size - i - 1; ++j) {
                if (arr[j + 1] < arr[j]) {
                    ISort<Sort<T>>::swapVal(j, j + 1);
                }
            }
        }
    }
};

struct RandomSortTask : public Sort<RandomSortTask>
{
    [[nodiscard]] std::string getPathImpl() const override { return "../Sorting/sorting-tests/0.random"; }
};

struct DigitsSortTask : public Sort<DigitsSortTask>
{
    [[nodiscard]] std::string getPathImpl() const override { return "../Sorting/sorting-tests/1.digits"; }
};

struct SortedSortTask : public Sort<SortedSortTask>
{
    [[nodiscard]] std::string getPathImpl() const override { return "../Sorting/sorting-tests/2.sorted"; }
};

struct ReversSortTask : public Sort<ReversSortTask>
{
    [[nodiscard]] std::string getPathImpl() const override { return "../Sorting/sorting-tests/3.revers"; }
};

} // namespace bubble

namespace insertion {
template<typename T>
struct Sort : public ISort<Sort<T>>
{
    using SizeType = typename ISort<Sort<T>>::SizeType;
    using ValueType = typename ISort<Sort<T>>::ValueType;

    void sort(ValueType* arr, SizeType size)
    {
        for (SizeType i = 1; i < size; ++i) {
            auto j = i;
            auto val = arr[j];
            if (val > arr[j - 1])
                continue;
            auto pos = findPos(arr, j, val);
            while (j > pos) {
                arr[j] = arr[j - 1];
                --j;
            }
            if (j != i) {
                arr[j] = val;
            }
        }
    }

private:
    SizeType findPos(ValueType* arr, SizeType size, ValueType val)
    {
        std::int64_t left = 0, right = size - 1, m = 0;
        while (left <= right) {
            m = (right + left) / 2;
            if (arr[m] > val) {
                right = m - 1;
            }
            else if (arr[m] < val) {
                left = m + 1;
                m = left;
            }
            else {
                break;
            }
        }

        return m;
    }
};

struct RandomSortTask : public Sort<RandomSortTask>
{
    [[nodiscard]] std::string getPathImpl() const override { return "../Sorting/sorting-tests/0.random"; }
};

struct DigitsSortTask : public Sort<DigitsSortTask>
{
    [[nodiscard]] std::string getPathImpl() const override { return "../Sorting/sorting-tests/1.digits"; }
};

struct SortedSortTask : public Sort<SortedSortTask>
{
    [[nodiscard]] std::string getPathImpl() const override { return "../Sorting/sorting-tests/2.sorted"; }
};

struct ReversSortTask : public Sort<ReversSortTask>
{
    [[nodiscard]] std::string getPathImpl() const override { return "../Sorting/sorting-tests/3.revers"; }
};

} // namespace insertion

namespace shell {
template<typename T>
struct Sort : public ISort<Sort<T>>
{
    using SizeType = typename ISort<Sort<T>>::SizeType;
    using ValueType = typename ISort<Sort<T>>::ValueType;

    void sort(ValueType* arr, SizeType size)
    {
        for (SizeType i = 1; i < size; ++i) {
            auto j = i;
            auto val = arr[j];
            if (val > arr[j - 1])
                continue;
            auto pos = findPos(arr, j, val);
            while (j > pos) {
                arr[j] = arr[j - 1];
                --j;
            }
            if (j != i) {
                arr[j] = val;
            }
        }
    }
};

struct RandomSortTask : public Sort<RandomSortTask>
{
    [[nodiscard]] std::string getPathImpl() const override { return "../Sorting/sorting-tests/0.random"; }
};

struct DigitsSortTask : public Sort<DigitsSortTask>
{
    [[nodiscard]] std::string getPathImpl() const override { return "../Sorting/sorting-tests/1.digits"; }
};

struct SortedSortTask : public Sort<SortedSortTask>
{
    [[nodiscard]] std::string getPathImpl() const override { return "../Sorting/sorting-tests/2.sorted"; }
};

struct ReversSortTask : public Sort<ReversSortTask>
{
    [[nodiscard]] std::string getPathImpl() const override { return "../Sorting/sorting-tests/3.revers"; }
};
} // namespace shell
