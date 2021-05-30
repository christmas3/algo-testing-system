#include "PriorityQueue.h"

#include <gtest/gtest.h>

TEST(PriorityQueue, ForwardedList)
{
    ForwardedList<std::uint32_t> flist;
    EXPECT_EQ(flist.size(), 0);
    EXPECT_TRUE(flist.empty());

    for (int i = 0; i < 10; ++i) {
        flist.pushBack(i);
    }
    flist.print();
    EXPECT_EQ(flist.size(), 10);
    EXPECT_FALSE(flist.empty());

    for (int i = 0; i < 10; ++i) {
        std::cerr << "flist.front(): " << flist.front() << std::endl;
        flist.popFront();
    }
    EXPECT_EQ(flist.size(), 0);
    EXPECT_TRUE(flist.empty());
}

TEST(PriorityQueue, PriorityQueue)
{
    PriorityQueue<std::uint32_t> queue;
    EXPECT_EQ(queue.size(), 0);
    EXPECT_TRUE(queue.empty());

    for (int i = 0; i < 10; ++i) {
        queue.push(10, i);
    }
    queue.print();
    EXPECT_EQ(queue.size(), 10);
    EXPECT_FALSE(queue.empty());

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(queue.front(), i);
        queue.pop();
    }
    queue.print();
    EXPECT_EQ(queue.size(), 0);
    EXPECT_TRUE(queue.empty());

    queue.push(5, 1);
    queue.push(5, 2);

    queue.push(6, 4);
    queue.push(6, 3);

    queue.push(3, 5);
    queue.push(3, 6);

    EXPECT_EQ(queue.size(), 6);
    EXPECT_FALSE(queue.empty());
    queue.print();

    std::vector<std::uint32_t> popSequence = { 4, 3, 1, 2, 5, 6 };

    size_t i = 0;
    while (!queue.empty()) {
        EXPECT_EQ(popSequence[i++], queue.front());
        queue.pop();
    }
    queue.print();
    EXPECT_EQ(queue.size(), 0);
    EXPECT_TRUE(queue.empty());
}
