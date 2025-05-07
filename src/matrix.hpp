#pragma once

#include <cstddef>
#include <iostream>
#include <map>
#include <mutex>
#include <xutility>

template <typename T, T default_value>
class EProxy {
   public:
    EProxy(std::map<size_t, T>& map, size_t idx) : map_{map}, idx_{idx} {
        // std::cout << "EPROXY CTOR" << std::endl;
    }

    EProxy(const EProxy& o) = delete;
    EProxy& operator=(const EProxy& o) = delete;

    operator T() { return map_.contains(idx_) ? map_[idx_] : default_value; }

    EProxy<T, default_value>& operator=(const T& o) {
        (default_value == o) ? map_.erase(idx_) : map_[idx_] = o;
        return *this;
    }

    /*
    EProxy<T, default_value> next() const {
        auto n = std::next(iter_);
        return EProxy<T, default_value>{map_, idx_ + 1, n};
    }
    */
    // T operator*() { return map_.contains(idx_) ? map_[idx_] : default_value; }
    // EProxy<T, default_value> operator++() { return next(); }
    // bool operator==(const EProxy<T, default_value>& o) { return map_ == o.map_ && idx_ == o.idx_; }
    // bool operator!=(const EProxy<T, default_value>& o) { return !operator==(o); }

   private:
    std::map<size_t, T>& map_;
    const size_t idx_;
};

template <typename T, T default_value, size_t order = 2>
class Matrix {
    using SubType = Matrix<T, default_value, order - 1>;

   public:
    SubType& operator[](size_t idx) { return rows_[idx]; }

    [[nodiscard]] size_t size() const {
        size_t sum = 0;
        for (const auto& e : rows_) {
            sum += e.second.size();
        }
        return sum;
    }

   private:
    std::map<size_t, SubType> rows_;
};

template <typename T, T default_value>
class Matrix<T, default_value, 1> {
    using ProxyType = EProxy<T, default_value>;

   public:
    [[nodiscard]] size_t size() const { return els_.size(); }

    ProxyType operator[](size_t key) { return {els_, key}; }

    auto begin() { return els_.begin(); }
    auto end() { return els_.end(); }

    // const T& operator[](size_t idx) const { return els_.contains(idx) ? els_.find(idx)->second : default_value; }

   private:
    std::map<size_t, T> els_{};  // matrix elements container
};

template <typename T, size_t order>
class MatrixIterator {
    using ContainerType = std::map<size_t, T>;

   public:
    explicit MatrixIterator(ContainerType& c) : container_{c} {}

   private:
    ContainerType& container_;
};
