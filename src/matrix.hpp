#include "my_allocator.hpp"

#include <cstddef>
#include <map>
#include <memory>

template <typename T>
class ElementAllocator;

template <typename T>
class ElementAllocator<std::pair<size_t, T>> {
   public:
    using value_type = std::pair<size_t, T>;
};

template <typename T, T default_value, size_t order = 2>
class Matrix {
   public:
   private:
    Matrix<T, default_value, order - 1> rows;
};

template <typename T, T default_value>
class EProxy {
   public:
    EProxy(std::map<size_t, T>& map, size_t idx)
        : map_{map}, idx_{idx}, v_{map_.contains(idx) ? map_[idx] : default_value} {
        std::cout << "EPROXY CTOR" << std::endl;
    }

    ~EProxy() {
        std::cout << "EPROXY DTOR" << std::endl;
        if (default_value == v_) {
            std::cout << "erase" << std::endl;
            map_.erase(idx_);
        } else {
            std::cout << "set:" << v_ << std::endl;
            map_[idx_] = v_;
        }
    }

    operator int&() { return v_; }

    EProxy<T, default_value>& operator=(int o) {
        v_ = o;
        return *this;
    }

   private:
    std::map<size_t, T>& map_;
    const size_t idx_;
    int v_;
};

template <typename T, T default_value>
class Matrix<T, default_value, 1> {
    using ProxyType = EProxy<T, default_value>;

   public:
    [[nodiscard]] size_t size() const { return els_.size(); }

    ProxyType operator[](size_t idx) { return ProxyType{els_, idx}; }

    T operator[](size_t idx) const { return els_.contains(idx) ? els_[idx] : default_value; }

   private:
    // using alloc = my_allocator<std::pair<const size_t, T>>;
    std::map<size_t, T> els_{};  // matrix elements container
};
