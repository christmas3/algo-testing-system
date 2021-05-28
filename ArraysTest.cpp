#include <gtest/gtest.h>
#include <random>

#include "Arrays.h"

#define TimeLapse(code, time)                             \
    {                                                     \
        auto begin_t = std::clock();                      \
        code;                                             \
        auto end_t = std::clock();                        \
        time = (float)(end_t - begin_t) / CLOCKS_PER_SEC; \
    }

template<typename T>
void testPutBack(ArrayPtr<T>& arr, size_t total)
{
    double timeVal = 0;
    TimeLapse(
        {
            for (int i = 0; i < total; ++i) {
                arr->putBack(i);
            }
        },
        timeVal);

    std::cerr << __FUNCTION__ << ": " << total << " time: " << std::fixed << timeVal << " seconds" << std::endl;
    EXPECT_EQ(arr->size(), total);
    EXPECT_EQ(arr->get(0), 0);
    EXPECT_EQ(arr->get(100), 100);
    EXPECT_EQ(arr->get(total - 1), total - 1);
}

template<typename T>
void testPutFront(ArrayPtr<T>& arr, size_t total)
{
    double timeVal = 0;
    TimeLapse(
        {
            for (int i = 0; i < total; ++i) {
                arr->put(i, 0);
            }
        },
        timeVal);

    std::cerr << __FUNCTION__ << ": " << total << " time: " << std::fixed << timeVal << " seconds" << std::endl;
    EXPECT_EQ(arr->size(), total);
    EXPECT_EQ(arr->get(0), total - 1);
    EXPECT_EQ(arr->get(100), total - 101);
    EXPECT_EQ(arr->get(total - 1), 0);
}

template<typename T>
void testPutRandom(ArrayPtr<T>& arr, size_t total)
{
    double timeVal = 0;
    std::default_random_engine dre;
    std::uniform_int_distribution<int> di(0, total);

    TimeLapse(
        {
            for (int i = 0; i < total; ++i) {
                arr->put(i, di(dre) % (arr->size() + 1));
            }
        },
        timeVal);

    std::cerr << __FUNCTION__ << ": " << total << " time: " << std::fixed << timeVal << " seconds" << std::endl;
    EXPECT_EQ(arr->size(), total);
}

template<typename T>
void testPutMiddle(ArrayPtr<T>& arr, size_t total)
{
    double timeVal = 0;
    TimeLapse(
        {
            for (int i = 0; i < total; ++i) {
                arr->put(i, arr->size() / 2);
            }
        },
        timeVal);

    std::cerr << __FUNCTION__ << ": " << total << " time: " << std::fixed << timeVal << " seconds" << std::endl;
    EXPECT_EQ(arr->size(), total);
    EXPECT_EQ(arr->get(0), 1);
    EXPECT_EQ(arr->get(total / 2 - 1), total - 1);
    EXPECT_EQ(arr->get(total - 1), 0);
}

template<typename T>
void testGetFront(ArrayPtr<T>& arr, size_t total)
{
    double timeVal = 0;
    EXPECT_EQ(arr->get(0), 0);
    TimeLapse(
        {
            for (int i = 0; i < total; ++i) {
                arr->get(0);
            }
        },
        timeVal);

    std::cerr << __FUNCTION__ << ": " << total << " time: " << std::fixed << timeVal << " seconds" << std::endl;
    EXPECT_EQ(arr->size(), total);
}

template<typename T>
void testGetBack(ArrayPtr<T>& arr, size_t total)
{
    double timeVal = 0;
    auto back = arr->size() - 1;
    EXPECT_EQ(arr->get(back), total - 1);
    TimeLapse(
        {
            for (int i = 0; i < total; ++i) {
                arr->get(back);
            }
        },
        timeVal);

    std::cerr << __FUNCTION__ << ": " << total << " time: " << std::fixed << timeVal << " seconds" << std::endl;
    EXPECT_EQ(arr->size(), total);
}

template<typename T>
void testGetRandom(ArrayPtr<T>& arr, size_t total)
{
    double timeVal = 0;
    std::default_random_engine dre;
    std::uniform_int_distribution<int> di(0, total);

    TimeLapse(
        {
            for (int i = 0; i < total; ++i) {
                arr->get(di(dre) % arr->size());
            }
        },
        timeVal);

    std::cerr << __FUNCTION__ << ": " << total << " time: " << std::fixed << timeVal << " seconds" << std::endl;
    EXPECT_EQ(arr->size(), total);
}

template<typename T>
void testRemoveFront(ArrayPtr<T>& arr, size_t total)
{
    ASSERT_FALSE(arr->empty());
    double timeVal = 0;
    TimeLapse(
        {
            for (int i = 0; i < total; ++i) {
                //                arr->remove(0);
                EXPECT_EQ(arr->remove(0), i);
                EXPECT_EQ(arr->size(), total - i - 1);
            }
        },
        timeVal);

    std::cerr << __FUNCTION__ << ": " << total << " time: " << std::fixed << timeVal << " seconds" << std::endl;
    EXPECT_EQ(arr->empty(), true);
}

template<typename T>
void testRemoveRandom(ArrayPtr<T>& arr, size_t total)
{
    ASSERT_FALSE(arr->empty());
    std::default_random_engine dre;
    std::uniform_int_distribution<int> di(0, total);
    double timeVal = 0;
    TimeLapse(
        {
            for (int i = 0; i < total; ++i) {
                arr->remove(di(dre) % arr->size());
            }
        },
        timeVal);

    std::cerr << __FUNCTION__ << ": " << total << " time: " << std::fixed << timeVal << " seconds" << std::endl;
    EXPECT_EQ(arr->empty(), true);
}

template<typename T>
void testRemoveMiddle(ArrayPtr<T>& arr, size_t total)
{
    ASSERT_FALSE(arr->empty());
    double timeVal = 0;
    TimeLapse(
        {
            for (int i = 0; i < total; ++i) {
                if (i == 0) {
                    EXPECT_EQ(arr->remove(arr->size() / 2), total / 2);
                }
                else if (i + 1 == total) {
                    EXPECT_EQ(arr->remove(arr->size() / 2), 0);
                }
                else {
                    arr->remove(arr->size() / 2);
                }
            }
        },
        timeVal);

    std::cerr << __FUNCTION__ << ": " << total << " time: " << std::fixed << timeVal << " seconds" << std::endl;
    EXPECT_EQ(arr->empty(), true);
}

template<typename T>
void testRemoveBack(ArrayPtr<T>& arr, size_t total)
{
    ASSERT_FALSE(arr->empty());
    double timeVal = 0;
    TimeLapse(
        {
            for (int i = 0; i < total; ++i) {
                //                arr->removeBack();
                EXPECT_EQ(arr->removeBack(), total - i - 1);
                EXPECT_EQ(arr->size(), total - i - 1);
            }
        },
        timeVal);

    std::cerr << __FUNCTION__ << ": " << total << " time: " << std::fixed << timeVal << " seconds" << std::endl;
    EXPECT_EQ(arr->empty(), true);
}

template<typename T>
void testArray(ArrayPtr<T>& arr, size_t total, size_t capacity)
{
    testPutMiddle(arr, total);
    arr->clear();
    EXPECT_EQ(arr->empty(), true);

    testPutRandom(arr, total);
    arr->clear();
    EXPECT_EQ(arr->empty(), true);

    testPutFront(arr, total);
    arr->clear();
    EXPECT_EQ(arr->empty(), true);

    testPutBack(arr, total);

    std::cerr << "arr->capacity(): " << arr->capacity() << std::endl;

    testGetFront(arr, total);
    testGetBack(arr, total);
    testGetRandom(arr, total);

    auto arrCopy = arr->getCopy();
    EXPECT_EQ(arrCopy->size(), total);
    testRemoveFront(arrCopy, total);
    EXPECT_TRUE(arrCopy->empty());
    EXPECT_EQ(arrCopy->capacity(), capacity);

    arrCopy = arr->getCopy();
    testRemoveRandom(arrCopy, total);
    EXPECT_TRUE(arrCopy->empty());
    EXPECT_EQ(arrCopy->capacity(), capacity);

    arrCopy = arr->getCopy();
    testRemoveMiddle(arrCopy, total);
    EXPECT_TRUE(arrCopy->empty());
    EXPECT_EQ(arrCopy->capacity(), capacity);

    arrCopy = arr->getCopy();
    testRemoveBack(arrCopy, total);
    EXPECT_TRUE(arrCopy->empty());
    EXPECT_EQ(arrCopy->capacity(), capacity);
}

static const size_t kTotal = 100000;

TEST(Arrays, SingleArray)
{
    ArrayPtr<std::uint32_t> arr = std::make_shared<SingleArray<std::uint32_t>>();
    testArray(arr, kTotal, 0);
}

TEST(Arrays, VectorArray)
{
    ArrayPtr<std::uint32_t> arr = std::make_shared<VectorArray<std::uint32_t>>();
    testArray(arr, kTotal, arr->capacity());
}

TEST(Arrays, FactorArray)
{
    ArrayPtr<std::uint32_t> arr = std::make_shared<FactorArray<std::uint32_t>>();
    testArray(arr, kTotal, arr->capacity());
}

TEST(Arrays, FixedArray)
{
    ArrayPtr<std::uint32_t> arr = std::make_shared<FixedArray<std::uint32_t>>();

    EXPECT_EQ(arr->capacity(), 100);
    EXPECT_EQ(arr->size(), 0);

    for (size_t i = 0; i < arr->capacity(); ++i) {
        arr->put(i, arr->size() / 2);
    }
    EXPECT_EQ(arr->size(), 100);
    arr->print();

    auto removed = arr->removeBack();
    EXPECT_EQ(removed, 0);
    EXPECT_EQ(arr->size(), 99);

    arr->put(101, 50);
    EXPECT_EQ(arr->size(), 100);
    EXPECT_EQ(arr->get(50), 101);
    EXPECT_EQ(arr->get(99), 2);
    arr->print();
}

TEST(Arrays, MatrixArray)
{
    ArrayPtr<std::uint32_t> arr = std::make_shared<MatrixArray<std::uint32_t>>();
    testArray(arr, kTotal, arr->capacity());
}

TEST(Arrays, StlVectorArray)
{
    ArrayPtr<std::uint32_t> arr = std::make_shared<StlVectorArray<std::uint32_t>>();
    EXPECT_EQ(arr->capacity(), 0);
    EXPECT_EQ(arr->size(), 0);
    testArray(arr, kTotal, arr->capacity());
}
