#pragma once

#include <cstddef>
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <xutility>

template <typename Container, typename Container::ValueType default_value>
class EProxy {
   public:
    using ValueType = typename Container::ValueType;
    using KeyType = typename Container::KeyType;

    EProxy(Container& c, typename Container::KeyType key) : cont_{c}, key_{key} {
        // std::cout << "EPROXY CTOR" << std::endl;
    }

    EProxy(const EProxy& o) = delete;
    EProxy& operator=(const EProxy& o) = delete;

    operator ValueType() {
        auto it = find_if(cont_.begin(), cont_.end(), [this](ValueType e) { return e.key == key_; });
        return (cont_.end() == it) ? default_value : (*it).value;
    }

    EProxy<Container, default_value>& operator=(const ValueType& o) {
        (default_value == o) ? cont_.Erase(key_) : cont_.Set(key_, o);
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
    Container& cont_;
    const KeyType key_;
};

/*
// Класс вложеных ключей
template <size_t KeyOrder>
class Key {
   public:
    explicit Key(size_t k, Key<KeyOrder - 1> inner) : k_{k}, inner_{inner} {}
    bool operator==(const Key& o) { return (k_ == o.k_) & (inner_ == o.inner_); }

   private:
    const size_t k_;
    Key<KeyOrder - 1> inner_;
};

template <>
class Key<1> {
   public:
    explicit Key(size_t k) : k_{k} {}
    bool operator==(const Key& o) const { return (k_ == o.k_); }

   private:
    const size_t k_;
};

template <typename C, size_t kKeyOrder>
class Access {
   public:
    Access(C& c, Key<kKeyOrder> k) : container_{c}, key_{k} {}
    Access<C, kKeyOrder + 1> operator[](size_t idx) {
        return Access<C, kKeyOrder + 1>{container_, Key<kKeyOrder + 1>{idx, key_}};
    }

    operator typename C::ValueType() {
        if constexpr (kKeyOrder == C::kMatrixOrder) {
            return EProxy<C, C::kDefaultValue>{container_, key_};
        }
    }

   private:
    C& container_;
    Key<kKeyOrder> key_;
};
*/
template <typename M>
class ProxyCell {
    using MatrixElemet = typename M::ValueType;

   public:
    ProxyCell(M& matrix, size_t row, size_t col) : matrix_{matrix}, row_{row}, col_{col} {}

    operator typename MatrixElemet::ValueType() const {
        auto it = std::find_if(
            matrix_.begin(), matrix_.end(), [&](MatrixElemet e) { return e.row == row_ && e.col == col_; });
        return (matrix_.end() == it) ? M::kDefaultValue : it->value;
    }

    // Присваивание
    ProxyCell<M>& operator=(typename MatrixElemet::ValueType o) {
        auto it = std::find_if(
            matrix_.begin(), matrix_.end(), [&](MatrixElemet e) { return e.row == row_ && e.col == col_; });

        if (matrix_.end() == it) {  // элемент не существует
            if (M::kDefaultValue == o) {
                // do nothing
            } else {
                auto cur = matrix_.insert(it, {o, row_, col_});
            }
        } else {  // элемент существует
            if (M::kDefaultValue == o) {
                matrix_.erase(it);
            } else {
                it->value = o;
            }
        }

        return *this;
    }

   private:
    M& matrix_;
    size_t row_;
    size_t col_;
};

template <typename M>
class ProxyRow {
   public:
    ProxyRow(M& matrix, size_t row) : matrix_{matrix}, row_{row} {}
    ProxyCell<M> operator[](size_t col) { return ProxyCell<M>(matrix_, row_, col); }

   private:
    M& matrix_;
    size_t row_;
};

template <typename T>
struct MatrixElement {
    using ValueType = T;
    T value;
    size_t row;
    size_t col;

    operator std::tuple<size_t&, size_t&, int&>() { return {row, col, value}; }
};

template <typename T, T default_value>
class Matrix {
   public:
    using ValueType = MatrixElement<T>;
    static constexpr T kDefaultValue = default_value;

    ProxyRow<Matrix> operator[](size_t row) { return ProxyRow<Matrix>{*this, row}; }

    [[nodiscard]] size_t size() const { return rows_.size(); }

    typename std::list<MatrixElement<T>>::iterator begin() { return rows_.begin(); }
    typename std::list<MatrixElement<T>>::iterator end() { return rows_.end(); }

    typename std::list<MatrixElement<T>>::iterator erase(typename std::list<MatrixElement<T>>::const_iterator it) {
        return rows_.erase(it);
    }

    typename std::list<MatrixElement<T>>::iterator insert(typename std::list<MatrixElement<T>>::const_iterator it,
                                                          ValueType val) {
        return rows_.insert(it, val);
    }

   private:
    std::list<MatrixElement<T>> rows_;
};

/*
template <typename T, T default_value>
class Matrix<T, default_value, 1> {
    using ProxyType = EProxy<T, default_value>;

   public:
    [[nodiscard]] size_t size() const { return els_.size(); }

    ProxyType operator[](size_t key) { return {els_, key}; }

    // Здесь не очень честно, потому что при записи элемента по итератору default_value не освободит память
    auto begin() const { return els_.cbegin(); }
    auto end() const { return els_.cend(); }

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
*/