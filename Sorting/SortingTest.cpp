#include <gtest/gtest.h>

#include "Sorting.h"

struct SortTest : public BaseTest
{
};

namespace sorting {
static BubbleSort bubbleSort;
static InsertionSort insertionSort;
static ShellSort<GapHalf> shellHalfSort;

static void runTest(const std::string& input, const std::string& result)
{
    auto paramVec = splitString(input);
    auto size = toValueType(paramVec[0]);
    auto arrUPtr = std::make_unique<ValueType[]>(size);
    fillArray(arrUPtr.get(), paramVec[1]);
    for (ISort* sort : std::initializer_list<ISort*>{ &bubbleSort, &insertionSort, &shellHalfSort }) {
        std::cerr << sort->sortName() << ": ";
        if (sort->maxSize() < size) {
            std::cerr << " skip" << std::endl;
            continue;
        }
        auto arrUPtrCopy = std::make_unique<ValueType[]>(size);
        memcpy(arrUPtrCopy.get(), arrUPtr.get(), size * sizeof(ValueType));

        double timeVal = 0;
        TimeLapseWithoutResult(sort->sort(arrUPtrCopy.get(), size), timeVal);
        std::cerr << std::fixed << "time passed: " << timeVal << " seconds" << std::endl;

        EXPECT_EQ(result, toResult(arrUPtrCopy.get(), size));
    }
    std::cerr << std::endl;
}

TEST_P(SortTest, ProcessSort)
{
    static int i = 0;
    std::cerr << "test number " << i++ << ": " << std::endl;
    runTest(GetParam().input, GetParam().result);
}
INSTANTIATE_TEST_SUITE_P(RandomSortSuit, SortTest, testing::ValuesIn(readTestParams(sorting::kRandomTestPath)));
INSTANTIATE_TEST_SUITE_P(DigitsSortSuit, SortTest, testing::ValuesIn(readTestParams(sorting::kDigitsTestPath)));
INSTANTIATE_TEST_SUITE_P(SortedSortSuit, SortTest, testing::ValuesIn(readTestParams(sorting::kSortedTestPath)));
INSTANTIATE_TEST_SUITE_P(ReversSortSuit, SortTest, testing::ValuesIn(readTestParams(sorting::kReversTestPath)));

} // namespace sorting

//namespace shell_second {
//TEST(GapTest, GapStep)
//{
//    for (Gap gap(100); gap.getGap() > 0; gap.getNextGap()) {
//        std::cerr << "gap.: " << gap.getGap() << std::endl;
//    }
//}
//} // namespace shell_second
