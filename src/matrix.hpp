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
class EProxy {
   public:
    EProxy(std::map<size_t, T>& map, size_t idx)
        : map_{map}, idx_{idx}, v_{map_.contains(idx) ? map_[idx] : default_value} {
        // std::cout << "EPROXY CTOR" << std::endl;
    }

    EProxy(const EProxy& o) = delete;
    EProxy& operator=(const EProxy& o) = delete;

    ~EProxy() {
        // std::cout << "EPROXY DTOR" << std::endl;
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

    ProxyType operator[](size_t idx) { return {els_, idx}; }

    // const T& operator[](size_t idx) const { return els_.contains(idx) ? els_.find(idx)->second : default_value; }

   private:
    std::map<size_t, T> els_{};  // matrix elements container
};
