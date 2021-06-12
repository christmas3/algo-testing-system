#pragma once

#include "../BaseTask.h"

namespace sorting {

const char* kRandomTestPath = "../Sorting/sorting-tests/0.random";
const char* kDigitsTestPath = "../Sorting/sorting-tests/1.digits";
const char* kSortedTestPath = "../Sorting/sorting-tests/2.sorted";
const char* kReversTestPath = "../Sorting/sorting-tests/3.revers";

using ValueType = std::int32_t;
using SizeType = size_t;

ValueType toValueType(const std::string& str)
{
    int32_t val = 0;
    for (auto ch : str) {
        val = val * 10 + ch - 0x30;
    }

    return val;
}

void fillArray(ValueType* arr, const std::string& val)
{
    size_t left = 0;
    size_t curIndex = 0;
    for (size_t i = 0; i < val.size(); ++i) {
        if (val[i] == ' ') {
            arr[curIndex++] = toValueType(val.substr(left, i - left));
            left = i + 1;
        }
    }
    arr[curIndex] = toValueType(val.substr(left, val.size() - left));
}

std::string toResult(ValueType* arr, SizeType size)
{
    std::string str = std::to_string(arr[0]);
    for (size_t i = 1; i < size; ++i) {
        str += ' ' + std::to_string(arr[i]);
    }

    return str;
}

void swapVal(ValueType* arr, SizeType lhs, SizeType rhs)
{
    auto tmp = arr[lhs];
    arr[lhs] = arr[rhs];
    arr[rhs] = tmp;
}

struct ISort
{
    [[nodiscard]] virtual const char* sortName() const = 0;
    [[nodiscard]] virtual SizeType maxSize() const = 0;

    virtual ~ISort() = default;
    virtual void sort(ValueType* arr, SizeType size) const = 0;
};

struct BubbleSort : public ISort
{
    [[nodiscard]] const char* sortName() const override { return "Bubble: "; }
    [[nodiscard]] SizeType maxSize() const override { return 100000; }

    void sort(ValueType* arr, SizeType size) const override
    {
        for (SizeType i = 0; i < size; ++i) {
            for (SizeType j = 0; j < size - i - 1; ++j) {
                if (arr[j + 1] < arr[j]) {
                    swapVal(arr, j, j + 1);
                }
            }
        }
    }
};

struct InsertionSort : public ISort
{
    [[nodiscard]] const char* sortName() const override { return "Insertion: "; }
    [[nodiscard]] SizeType maxSize() const override { return 100000; }

    void sort(ValueType* arr, SizeType size) const override
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
    SizeType findPos(ValueType* arr, SizeType size, ValueType val) const
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

using GapSize = std::int64_t;

template<typename G>
struct ShellSort : public ISort
{
    [[nodiscard]] const char* sortName() const override { return G::name(); }
    [[nodiscard]] SizeType maxSize() const override { return 10000000; }

    void sort(ValueType* arr, SizeType size) const override
    {
        G gapGen(size);
        for (GapSize gap = gapGen.getGap(); gap > 0; gap = gapGen.getNextGap()) {
            for (GapSize i = 0; i + gap < size; ++i) {
                GapSize j = i + gap;
                auto tmp = arr[j];
                while (j - gap >= 0 && tmp < arr[j - gap]) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = tmp;
            }
        }
    }
};

struct GapHalf
{
    GapSize getNextGap() { return gap_ /= 2; }
    [[nodiscard]] GapSize getGap() const { return gap_; }

    explicit GapHalf(std::int64_t size)
        : gap_(size / 2)
    {
    }

    static const char* name() { return "Shell sort with step half: "; }

private:
    GapSize gap_;
};

struct GapHibbard
{
    GapSize getNextGap() { return gap_ = (gap_ - 1) / 2; }
    [[nodiscard]] GapSize getGap() const { return gap_; }

    explicit GapHibbard(std::int64_t size)
        : gap_(0)
    {
        for (GapSize step = 1; step < size; step = (step + 1) * 2 - 1) {
            gap_ = step;
        }
    }

    static const char* name() { return "Shell sort with step Hibbard: "; }

private:
    GapSize gap_;
};

struct GapKnuth
{
    GapSize getNextGap() { return gap_ = gap_ / 3; }
    [[nodiscard]] GapSize getGap() const { return gap_; }

    explicit GapKnuth(std::int64_t size)
        : gap_(0)
    {
        auto maxStep = size / 3;
        for (GapSize step = 1; step < maxStep; step = step * 3 + 1) {
            gap_ = step;
        }
    }

    static const char* name() { return "Shell sort with step Knuth: "; }

private:
    GapSize gap_;
};

struct HeapSort : public ISort
{
    [[nodiscard]] const char* sortName() const override { return "Heap: "; }
    [[nodiscard]] SizeType maxSize() const override { return 10000000; }

    void sort(ValueType* arr, SizeType size) const override
    {
        for (std::int64_t root = size / 2 - 1; root >= 0; --root) {
            moveMaxToRoot(arr, root, size);
        }

        for (std::int64_t i = size - 1; i >= 0; --i) {
            swapVal(arr, 0, i);
            moveMaxToRoot(arr, 0, i);
        }
    }

private:
    void moveMaxToRoot(ValueType* arr, SizeType root, SizeType size) const
    {
        auto L = 2 * root + 1;
        auto R = L + 1;
        auto max = root;

        if (L < size && arr[max] < arr[L])
            max = L;
        if (R < size && arr[max] < arr[R])
            max = R;

        if (max == root)
            return;

        swapVal(arr, max, root);
        moveMaxToRoot(arr, max, size);
    }
};

} // namespace sorting
