#ifndef _log_n_vector_h_
#define _log_n_vector_h_

#include <cmath>
#include <memory>
#include <vector>

template <typename T>
class LogNVector {
    
    std::vector<std::unique_ptr<T[]> > arrays_;
    int size_, capacity_, count, capacity__;
public:
    LogNVector() {
        std::unique_ptr<T[]>array(new T[1]);
        arrays_.push_back(std::move(array));
        size_ = 1;
        count = 0;
        capacity_ = 1;
        capacity__ = 1;
    }

    //template <typename T>
    LogNVector(const LogNVector& other) : LogNVector() {
        for (int i = 0; i < other.size(); i++)
        {
             push_back(other[i]);    
        }
    }

    //template <typename T>
    LogNVector(std::initializer_list<T> ilist) : LogNVector() {
        for (T x : ilist)
        {
            push_back(x);
        }
    }

    //template <typename T>
    ~LogNVector() {
        // TODO
    }

    //template <typename T>
    int size() const noexcept {
        return count;
    }

    //template <typename T>
    int capacity() const noexcept {
        return capacity__;
    }

    //template <typename T>
    void push_back(const T& value) {
        // TODO
        if (capacity_ == 0)
        {
            size_ *= 2;
            //arrays_.push_back(new T[size_]);
            std::unique_ptr<T[]>array(new T[size_]);
            arrays_.push_back(std::move(array));
            capacity_ = size_;
            capacity__ += size_;
        }

        arrays_[arrays_.size() - 1][size_ - capacity_] = value;
        count++;
        capacity_--;
    }

    //template <typename T>
    const T& operator[](int index) const {
        int x = int(log2(index + 1));
        int y = index - (pow(2, x) - 1);
        return arrays_[x][y];
    }

    //template <typename T>
    T& operator[](int index) {
        int x = int(log2(index + 1));
        int y = index - (pow(2, x) - 1);
        return arrays_[x][y];
    }
};

#endif // _log_n_vector_h_#pragma once
