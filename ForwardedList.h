#pragma once

#include <iostream>

template<typename T>
struct IList
{
    [[nodiscard]] virtual size_t size() const = 0;
    [[nodiscard]] virtual bool empty() const { return size() == 0; };
    virtual const T& front() const = 0;
    virtual void popFront() = 0;
    virtual void pushBack(const T& item) = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
};

template<typename T>
class ForwardedList : public IList<T>
{
public:
    ForwardedList()
        : begin_(nullptr)
        , end_(nullptr)
        , size_(0)
    {
    }
    ~ForwardedList() { clear(); }

    [[nodiscard]] size_t size() const override { return size_; }
    [[nodiscard]] bool empty() const override { return IList<T>::empty(); }
    const T& front() const override { return begin_->value; }
    void popFront() override
    {
        auto* removed = begin_;
        begin_ = begin_->next;
        delete removed;
        --size_;
    }
    void pushBack(const T& item) override
    {
        auto* newItem = new Item{ item, nullptr };
        if (!empty()) {
            end_->next = newItem;
        }
        else {
            begin_ = newItem;
        }
        end_ = newItem;
        ++size_;
    }
    void print() const override
    {
        for (Item* current = begin_; current != nullptr; current = current->next) {
            std::cerr << current->value << " ";
        }
        std::cerr << std::endl;
    }
    void clear() override
    {
        Item* current = begin_;
        while (current) {
            Item* removed = current;
            current = current->next;
            delete removed;
        }
        begin_ = end_ = nullptr;
        size_ = 0;
    }

private:
    struct Item
    {
        T value;
        Item* next;
    };
    Item* begin_;
    Item* end_;
    size_t size_;
};