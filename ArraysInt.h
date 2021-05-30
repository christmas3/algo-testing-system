#pragma once

#include <iostream>
#include <memory>

template<typename T>
class IArray;

template<typename T>
using ArrayPtr = std::shared_ptr<IArray<T>>;

template<typename T>
class IArray
{
public:
    typedef size_t SizeType;

    [[nodiscard]] virtual SizeType size() const = 0;
    [[nodiscard]] virtual SizeType capacity() const = 0;
    [[nodiscard]] virtual bool empty() const { return size() == 0; }
    virtual T get(SizeType index) const = 0;

    virtual void putBack(const T& item) { put(item, size()); };
    virtual void put(const T& item, SizeType index) = 0;

    virtual T remove(SizeType index) = 0;
    virtual T removeBack() { return remove(size() - 1); };
    virtual void clear() = 0;

    virtual ArrayPtr<T> getCopy() const = 0;

    virtual void print() const
    {
        for (SizeType i = 0; i < size(); ++i) {
            std::cerr << get(i) << " ";
        }
        std::cerr << std::endl;
    }

    virtual ~IArray() = default;
};
