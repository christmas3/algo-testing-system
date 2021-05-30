#pragma once

#include "ArraysInt.h"

#include <vector>

template<typename T>
class SingleArray : public IArray<T>
{
public:
    SingleArray()
        : arr_(nullptr)
        , size_(0)
    {
    }

    ~SingleArray() override { delete[] arr_; }
    using SizeType = typename IArray<T>::SizeType;

    SizeType size() const override { return size_; }
    SizeType capacity() const override { return size_; }
    T get(SizeType index) const override { return arr_[index]; }
    void put(const T& item, SizeType index) override
    {
        auto* newArray = new T[size_ + 1];
        if (index) {
            memcpy(newArray, arr_, index * sizeof(T));
        }
        newArray[index] = item;
        if (index < size_) {
            memcpy(newArray + index + 1, arr_ + index, (size_ - index) * sizeof(T));
        }
        delete[] arr_;
        arr_ = newArray;
        ++size_;
    }
    T remove(SizeType index) override
    {
        T removed{};
        if (index >= size_) {
            return removed;
        }
        if (size_) {
            removed = arr_[index];
            if (size_ == 1) {
                clear();
                return removed;
            }
            auto* newArray = new T[size_ - 1];
            if (index) {
                memcpy(newArray, arr_, index * sizeof(T));
            }
            if (index < size_ - 1) {
                memcpy(newArray + index, arr_ + index + 1, (size_ - index - 1) * sizeof(T));
            }
            delete[] arr_;
            arr_ = newArray;
            --size_;
        }

        return removed;
    }

    ArrayPtr<T> getCopy() const override { return std::shared_ptr<SingleArray<T>>(getCopyPtr()); }

    SingleArray<T>* getCopyPtr() const
    {
        auto* copy = new SingleArray<T>();
        if (IArray<T>::empty()) {
            return copy;
        }
        copy->arr_ = new T[size_];
        memcpy(copy->arr_, arr_, size_ * sizeof(T));
        copy->size_ = size_;

        return copy;
    }

    void clear() override
    {
        delete[] arr_;
        arr_ = nullptr;
        size_ = 0;
    }

private:
    T* arr_;
    size_t size_;
};

template<typename T>
class VectorArray : public IArray<T>
{
public:
    using SizeType = typename IArray<T>::SizeType;

    explicit VectorArray(SizeType size = 10)
        : arr_(new T[size * sizeof(T)])
        , size_(0)
        , capacity_(size)
        , step_(size)
    {
    }
    ~VectorArray() override { delete[] arr_; }

    SizeType size() const override { return size_; }
    SizeType capacity() const override { return capacity_; }
    T get(SizeType index) const override { return arr_[index]; }
    void put(const T& item, SizeType index) override
    {
        if (size_ == capacity_) {
            resize(index);
        }
        else if (index != size_) {
            memmove(arr_ + index + 1, arr_ + index, (size_ - index) * sizeof(T));
        }
        arr_[index] = item;
        ++size_;
    }
    T remove(SizeType index) override
    {
        assert(size_ > index);

        if (isNeedToShrink()) {
            shrink();
        }

        --size_;
        T removed = arr_[index];
        if (index < size_) {
            memmove(arr_ + index, arr_ + index + 1, (size_ - index) * sizeof(T));
        }

        return removed;
    }
    void clear() override
    {
        delete[] arr_;
        arr_ = new T[step_ * sizeof(T)];
        size_ = 0;
        capacity_ = step_;
    }
    ArrayPtr<T> getCopy() const override
    {
        auto copy = std::make_shared<VectorArray<T>>();
        if (IArray<T>::empty()) {
            return copy;
        }
        copy->arr_ = new T[capacity_];
        memcpy(copy->arr_, arr_, size_ * sizeof(T));
        copy->size_ = size_;
        copy->step_ = step_;
        copy->capacity_ = capacity_;

        return copy;
    }

protected:
    virtual SizeType increaseCapacity() const { return capacity_ + step_; }
    //    [[nodiscard]] virtual bool isNeedToShrink() const { return capacity_ - size_ >= step_ * 2 - 1; }
    [[nodiscard]] virtual bool isNeedToShrink() const { return size_ < step_; }
    virtual SizeType shrinkCapacity() const { return capacity_ - step_; }

private:
    void resize(SizeType index)
    {
        capacity_ = increaseCapacity();
        auto* newArr = new T[capacity_];
        if (index) {
            memcpy(newArr, arr_, index * sizeof(T));
        }
        if (index < size_) {
            memcpy(newArr + index + 1, arr_ + index, (size_ - index) * sizeof(T));
        }
        delete[] arr_;
        arr_ = newArr;
    }

    void shrink()
    {
        capacity_ = step_;
        auto* newArr = new T[capacity_];
        memcpy(newArr, arr_, size_ * sizeof(T));
        delete[] arr_;
        arr_ = newArr;
    }

    T* arr_;
    SizeType size_;
    SizeType capacity_;
    std::uint32_t step_;
};

template<typename T>
class FactorArray : public VectorArray<T>
{
public:
    using VectorArray<T>::VectorArray;
    using SizeType = typename VectorArray<T>::SizeType;

protected:
    SizeType increaseCapacity() const override { return VectorArray<T>::capacity() * 2; }
};

template<typename T>
class FixedArray : public IArray<T>
{
public:
    using SizeType = typename IArray<T>::SizeType;

    explicit FixedArray(SizeType size = 100)
        : arr_(new T[size * sizeof(T)])
        , size_(0)
        , capacity_(size)
    {
    }
    ~FixedArray() override { delete[] arr_; }

    SizeType size() const override { return size_; }
    SizeType capacity() const override { return capacity_; }
    T get(SizeType index) const override { return arr_[index]; }
    void put(const T& item, SizeType index) override
    {
        assert(size_ < capacity_);
        if (index != size_) {
            memmove(arr_ + index + 1, arr_ + index, (size_ - index) * sizeof(T));
        }
        arr_[index] = item;
        ++size_;
    }

    T remove(SizeType index) override
    {
        assert(!IArray<T>::empty());
        assert(size_ > index);

        --size_;
        T removed = arr_[index];
        if (index < size_) {
            memmove(arr_ + index, arr_ + index + 1, (size_ - index) * sizeof(T));
        }

        return removed;
    }
    void clear() override
    {
        delete[] arr_;
        arr_ = new T[capacity_ * sizeof(T)];
        size_ = 0;
    }
    ArrayPtr<T> getCopy() const override { return ArrayPtr<T>(getCopyPtr()); }

    FixedArray<T>* getCopyPtr() const
    {
        auto* copy = new FixedArray<T>(capacity_);
        if (IArray<T>::empty()) {
            return copy;
        }

        memcpy(copy->arr_, arr_, size_ * sizeof(T));
        copy->size_ = size_;
        copy->capacity_ = capacity_;

        return copy;
    }

private:
    T* arr_;
    SizeType size_;
    SizeType capacity_;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const FixedArray<T>& arr)
{
    for (typename FixedArray<T>::SizeType i = 0; i < arr.size(); ++i) {
        out << arr.get(i) << " ";
    }
    return out << std::endl;
}

template<typename T>
class MatrixArray : public IArray<T>
{
public:
    using SizeType = typename IArray<T>::SizeType;

    explicit MatrixArray(SizeType size = 100)
        : arr_(new SingleArray<FixedArray<T>*>)
        , size_(0)
        , vectorSize_(size)
        , capacity_(0)
    {
    }

    MatrixArray(const MatrixArray& arr)
        : arr_(new SingleArray<FixedArray<T>*>)
        , size_(arr.size_)
        , vectorSize_(arr.vectorSize_)
        , capacity_(arr.capacity_)
    {
        for (int i = 0; i < arr.arr_->size(); ++i) {
            arr_->putBack(arr.arr_->get(i)->getCopyPtr());
        }
    }

    ~MatrixArray() override
    {
        for (int i = 0; i < arr_->size(); ++i) {
            delete arr_->get(i);
        }
        delete arr_;
    }

    SizeType size() const override { return size_; }
    SizeType capacity() const override { return capacity_; }
    T get(SizeType index) const override
    {
        assert(index < size_);
        return arr_->get(index / vectorSize_)->get(index % vectorSize_);
    }
    void put(const T& item, SizeType index) override
    {
        if (size_ == capacity_) {
            resize();
        }
        insertItem(item, index);
        ++size_;
    }

    T remove(SizeType index) override
    {
        assert(index < size_);
        SizeType first = index / vectorSize_;
        T removed = arr_->get(first)->remove(index % vectorSize_);
        align(first);
        --size_;
        if (capacity_ - size_ >= vectorSize_) {
            arr_->removeBack();
            capacity_ -= vectorSize_;
        }

        return removed;
    }

    void clear() override
    {
        for (int i = 0; i < arr_->size(); ++i) {
            delete arr_->get(i);
        }
        arr_->clear();
        size_ = capacity_ = 0;
    }

    ArrayPtr<T> getCopy() const override { return ArrayPtr<T>(new MatrixArray<T>(*this)); }

private:
    void resize()
    {
        arr_->putBack(new FixedArray<T>(vectorSize_));
        capacity_ += vectorSize_;
    }
    void insertItem(const T& item, SizeType index)
    {
        SizeType firstIndex = index / vectorSize_;
        if (firstIndex == arr_->size() - 1) {
            arr_->get(firstIndex)->put(item, index % vectorSize_);
            return;
        }
        auto last = arr_->get(firstIndex)->removeBack();
        arr_->get(firstIndex)->put(item, index % vectorSize_);
        insertItem(last, (firstIndex + 1) * vectorSize_);
    }
    void align(SizeType firstIndex)
    {
        if (firstIndex == arr_->size() - 1) {
            return;
        }
        arr_->get(firstIndex)->putBack(arr_->get(firstIndex + 1)->remove(0));
        align(firstIndex + 1);
    }

    SingleArray<FixedArray<T>*>* arr_;
    SizeType size_;
    SizeType vectorSize_;
    SizeType capacity_;
};

template<typename T>
class StlVectorArray : public IArray<T>
{
public:
    using SizeType = typename IArray<T>::SizeType;

    StlVectorArray() = default;
    StlVectorArray(const StlVectorArray& rhs)
        : arr_(rhs.arr_)
    {
    }

    SizeType size() const override { return arr_.size(); }
    SizeType capacity() const override { return arr_.capacity(); }
    T get(SizeType index) const override { return arr_[index]; }
    void putBack(const T& item) override { arr_.push_back(item); }
    void put(const T& item, SizeType index) override { arr_.insert(arr_.begin() + index, item); }
    T remove(SizeType index) override
    {
        auto removed = std::move(arr_[index]);
        arr_.erase(arr_.begin() + index);
        shrink();
        return removed;
    }
    T removeBack() override
    {
        auto removed = std::move(arr_.back());
        arr_.pop_back();
        shrink();
        return removed;
    }
    void clear() override
    {
        arr_.clear();
        arr_.shrink_to_fit();
    }
    ArrayPtr<T> getCopy() const override { return ArrayPtr<T>(new StlVectorArray<T>(*this)); }

private:
    void shrink()
    {
        if (!size()) {
            arr_.shrink_to_fit();
        }
    }

    std::vector<T> arr_;
};
