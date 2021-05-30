#pragma once

#include "Arrays.h"
#include "ForwardedList.h"

#include <assert.h>

template<typename T>
class PriorityQueue
{
public:
    PriorityQueue()
        : size_(0)
    {
    }
    ~PriorityQueue()
    {
        for (size_t i = 0; i < arr_.size(); ++i) {
            delete arr_.get(i);
        }
    }

    [[nodiscard]] size_t size() const { return size_; }
    [[nodiscard]] bool empty() const { return size() == 0; }
    const T& front() const
    {
        auto index = maxPriorIndex();
        assert(index != -1);

        return arr_.get(index)->flist.front();
    }
    void pop()
    {
        if (auto index = maxPriorIndex(); index != -1) {
            arr_.get(index)->flist.popFront();
            --size_;
        }
    }
    void push(std::uint32_t priority, const T& item)
    {
        size_t curIndex = arr_.size();
        if (!curIndex) {
            arr_.put(new PriorityList{ priority }, curIndex);
        }
        else {
            for (size_t i = 0; i < arr_.size(); ++i) {
                if (arr_.get(i)->priority <= priority) {
                    curIndex = i;
                    break;
                }
            }
            if (curIndex == arr_.size() || arr_.get(curIndex)->priority != priority) {
                arr_.put(new PriorityList{ priority }, curIndex);
            }
        }

        arr_.get(curIndex)->flist.pushBack(item);
        ++size_;
    }
    void print() const
    {
        for (size_t i = 0; i < arr_.size(); ++i) {
            std::cerr << "priority: " << arr_.get(i)->priority << ": ";
            arr_.get(i)->flist.print();
            std::cerr << " ";
        }
        std::cerr << std::endl;
    }

private:
    std::int64_t maxPriorIndex() const
    {
        for (size_t i = 0; i < arr_.size(); ++i) {
            if (!arr_.get(i)->flist.empty()) {
                return i;
            }
        }
        return -1;
    }

    struct PriorityList
    {
        std::uint32_t priority;
        ForwardedList<T> flist;
    };

    SingleArray<PriorityList*> arr_;
    size_t size_;
};
