#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <cstdlib>
#include <cassert>
#include <stdexcept>

namespace swo {

    template <typename T>
    class deque final {
    private:
        T* arr{nullptr};
        size_t cap{10}, cnt{0}, first{0};
        void resize_cap(size_t count) {
            assert(count > 0);
            if (count > cap) {
                T* tmp{new T[count]};
                for (size_t i{0}; i < cnt; i++) {
                    tmp[i] = std::move(arr[(i + first) % cap]);
                }
                cap = count;
                first = 0;
                delete[] arr;
                arr = tmp;
            }
        }
    public:
        using const_reference = T const &;
        using reference       = T &;
        using size_type       = std::size_t;
        using value_type      = T;

        friend bool operator==(deque const & lhs, deque const & rhs) noexcept {
            if (lhs.size() != rhs.size()) {
                return false;
            }
            for (size_t i{0}; i < lhs.cnt; i++) {
                if (lhs[(lhs.first + i) % lhs.cap] == rhs[(rhs.first + i) % rhs.cap]) {
                    return false;
                }
            }
            return true;
        }
        friend
        auto operator!=(deque const & lhs, deque const & rhs) noexcept -> bool {
            return !(lhs == rhs);
        }
        friend
        auto operator<(deque const & lhs, deque const & rhs) noexcept -> bool {
            size_t min_size{lhs.cnt > rhs.cnt ? rhs.cnt : lhs.cnt};
            for (size_t i{0}; i < min_size; i++) {
                if (lhs.arr[(lhs.first + i) % lhs.cap] != rhs.arr[(rhs.first + i) % rhs.cap]) {
                    return lhs.arr[(lhs.first + i) % lhs.cap] < rhs.arr[(rhs.first + i) % rhs.cap];
                }
            }
            return (lhs.cnt < rhs.cnt) && (lhs != rhs);
        }
        friend
        auto operator<=(deque const & lhs, deque const & rhs) noexcept -> bool {
            return lhs == rhs || lhs < rhs;
        }
        friend
        auto operator>(deque const & lhs, deque const & rhs) noexcept -> bool {
            return (!(lhs < rhs)) && (lhs != rhs);
        }
        friend
        auto operator>=(deque const & lhs, deque const & rhs) noexcept -> bool {
            return lhs == rhs || lhs > rhs;
        }

        friend
        void swap(deque <T> & a, deque <T> & b) noexcept {
            a.swap(b);
        }

        class iterator final {
        public:
            using difference_type   = std::ptrdiff_t;
            using iterator_category = std::random_access_iterator_tag;
            using pointer           = T *;
            using reference         = T &;
            using value_type        = T;

            friend
            auto operator==(iterator const & lhs, iterator const & rhs) noexcept -> bool {
                return lhs.ptr == rhs.ptr;
            }
            friend
            auto operator!=(iterator const & lhs, iterator const & rhs) noexcept -> bool {
                return !(lhs == rhs);
            }
            friend
            auto operator<(iterator const & lhs, iterator const & rhs) noexcept -> bool {
                size_t idx_lhs{lhs.ptr - lhs.arr};
                size_t idx_lin_lhs{idx_lhs < lhs.first? lhs.cap - lhs.first + idx_lhs : idx_lhs - lhs.first};
                size_t idx_rhs{rhs.ptr - rhs.arr};
                size_t idx_rhs_rhs{idx_rhs < rhs.first? rhs.cap - rhs.first + idx_rhs : idx_rhs - rhs.first};
                return (idx_lin_lhs < idx_lin_lhs) && (idx_lin_lhs != idx_rhs_rhs);
            }
            friend
            auto operator<=(iterator const & lhs, iterator const & rhs) noexcept -> bool {
                return (lhs < rhs) || (lhs == rhs);
            }
            friend
            auto operator>(iterator const & lhs, iterator const & rhs) noexcept -> bool {
                return !(lhs < rhs) && (lhs != rhs);
            }
            friend
            auto operator>=(iterator const & lhs, iterator const & rhs) noexcept -> bool {
                return (lhs > rhs) || (lhs == rhs);
            }

            friend
            auto operator+(iterator itor, difference_type offset) noexcept -> iterator {
               return itor += offset;
            }

            friend
            auto operator-(iterator itor, difference_type offset) noexcept -> iterator {
               return itor -= offset;
            }

            iterator() = default;
            iterator(iterator const & src) {
                ptr = src.ptr;
                arr = src.arr;
                first = src.first;
                cnt = src.cnt;
                cap = src.cap;
            }

            ~iterator() = default;

            auto operator=(iterator const & src) -> iterator& {
                ptr = src.ptr;
                arr = src.arr;
                first = src.first;
                cnt = src.cnt;
                cap = src.cap;
                return *this;
            };

            auto operator*() -> reference {
                return *ptr;
            }
            auto operator->() -> pointer {
                return ptr;
            }

            auto operator[](difference_type offset) -> reference {
                if (offset >= 0) {
                    if (ptr + offset > arr + cap - 1) {
                        return ptr[arr + (offset - (arr + cap - ptr))];
                    } else {
                        return ptr[offset];
                    }
                } else {
                    if (ptr - offset < arr) {
                        return ptr[arr + cap - 1 - (offset - (arr - ptr))];
                    } else {
                        return ptr[offset];
                    }
                }
            }

            auto operator++() noexcept ->  iterator& {
                ptr = ptr == arr + cap - 1 ? arr : ptr + 1;
                return *this;
            }
            auto operator++(int) noexcept -> iterator {
                iterator tmp{*this};
                ptr = ptr == arr + cap - 1 ? arr : ptr + 1;
                return tmp;
            }
            auto operator--() noexcept -> iterator& {
                ptr = ptr == arr ? arr + cap - 1 : ptr - 1;
                return *this;
            }
            auto operator--(int) noexcept -> iterator {
                iterator tmp{*this};
                ptr = ptr == arr ? arr + cap - 1 : ptr - 1;
                return tmp;
            }

            auto operator+=(difference_type offset) noexcept -> iterator& {
                if (ptr + offset > arr + cap - 1) {
                    ptr = arr + (offset - (arr + cap - ptr));
                } else {
                    ptr += offset;
                }
                return *this;
            }
            auto operator-=(difference_type offset) noexcept -> iterator& {
                if (ptr - offset < arr) {
                    ptr = arr + cap - 1 - (offset - (arr - ptr));
                } else {
                    ptr -= offset;
                }
                return *this;
            }

        private:
            pointer ptr{nullptr};
            pointer arr{nullptr};
            size_t first, cnt, cap;
            iterator(pointer ptr, size_t first, size_t cnt, size_t cap, pointer arr) : ptr{ptr}, first{first}, cnt{cnt}, cap{cap}, arr{arr} {};
            friend deque;
        };

        deque() {
            arr = new T[cap + 1];
        }
        explicit deque(size_type count) : cap{count + 1}, cnt{count} {
            assert(count > 0);
            arr = new T[cap + 1];
            T val{};
            for (size_t i{0}; i < count; i++) {
                arr[i] = val;
            }
        }
        deque(size_type count, T const & value) : cap{count + 1} {
            assert(count > 0);
            arr = new T[cap];
            cnt = count;
            for (std::size_t i{0}; i < cnt; i++) {
                arr[i] = value;
            }
        }
        deque(deque const & src) {
            assert(src.size() > 0);
            cap = src.cap;
            cnt = src.cnt;
            arr = new T[cap];
            first = src.first;
            if (src.empty()) {
                return;
            }
            size_t i{0};
            while (i < cnt) {
                arr[(first + i) % cap] = src[(first + i) % cap];
                i++;
            }
        }
        deque(deque && src) noexcept {
            swap(*this, src);
        }
        deque(std::initializer_list <T> init) {
            if (init.size() + 1 > cap) {
                cap = init.size() + 1;
            }
            arr = new T[cap];
            for(auto& value : init) {
                push_back(value);
            }
        }

        ~deque () {
            delete[] arr;
        }

        auto operator=(deque const & src) -> deque& {
            reserve(src.cap);
            cnt = src.cnt;
            first = src.cnt;
            for (std::size_t i{0}; i < cnt; i++) {
                arr[i] = src.arr[(i + first) % src.cap];
            }
            return *this;
        }
        auto operator=(deque && src) noexcept -> deque& {
            swap(src);
            return *this;
        }
        auto operator=(std::initializer_list <T> init) -> deque& {
            if (init.size() + 1 > cap) {
                resize_cap(init.size() + 1);
            }
            this->clear();
            for(auto& value : init) {
                push_back(value);
            }
        }

        auto operator[](size_type pos) const -> const_reference {
            if (pos >= cnt) {
                throw std::out_of_range("deque<Type>::[] : index is out of range");
            }
            return arr[(first + pos) % cap];
        }
        auto operator[](size_type pos) -> reference {
            if (pos >= cnt) {
                throw std::out_of_range("deque<Type>::[] : index is out of range");
            }
            return arr[(first + pos) % cap];
        }

        auto at(size_type pos) const -> const_reference  {
            if (pos >= cnt) {
                throw std::out_of_range("deque<Type>::at : index is out of range");
            }
            return arr[(first + pos) % cap];
        }
        auto at(size_type pos) -> const_reference  {
            if (pos >= cnt) {
                throw std::out_of_range("deque<Type>::at : index is out of range");
            }
            return arr[(first + pos) % cap];
        }
        auto back() const -> const_reference {
            assert(!empty());
            return arr[(first + cnt - 1) %cap];
        }
        auto back() -> reference {
            assert(!empty());
            return arr[(first + cnt - 1) %cap];
        }
        auto front() const -> const_reference {
            assert(!empty());
            return arr[first];
        }
        auto front () -> reference {
            assert(!empty());
            return arr[first];
        }

        auto begin() noexcept -> iterator {
            iterator it = {arr + first, first, cnt, cap, arr};
            return it;
        }
        auto end() noexcept -> iterator {
            iterator it = {arr + ((first + cnt) % cap), first, cnt, cap, arr};
            return it;
        }

        auto empty() const noexcept -> bool {
            return cnt == 0;
        }
        auto size() const noexcept -> size_type {
            return cnt;
        }

        void clear() noexcept {
            first = 0;
            cnt = 0;
        }

        void push_back(T const & value) {
            if (cnt + 1 >= cap) {
                resize_cap(2 * cap);
            }
            arr[(first + cnt) % cap] = value;
            cnt++;
        }
        void push_back(T && value) {
            if (cnt + 1 >= cap) {
                resize_cap(2 * cap);
            }
            arr[(first + cnt) % cap] = std::move(value);
            cnt++;
        }
        void pop_back() {
            assert(cnt > 0);
            cnt--;
        }

        void push_front(T const & value) {
            if (cnt + 1 >= cap) {
                resize_cap(2 * cap);
            }
            size_t next_first = first == 0 ? cap - 1 : first - 1;
            arr[next_first] = value;
            first = next_first;
            cnt++;
        }
        void push_front(T && value) {
            if (cnt + 1 >= cap) {
                resize_cap(2 * cap);
            }
            size_t next_first = (first == 0 ? cap - 1 : first - 1);
            arr[next_first] = std::move(value);
            first = next_first;
            cnt++;
        }
        void pop_front() {
            if (first == cap - 1) {
                first = 0;
            } else {
                first++;
            }
            cnt--;
        }

        void resize(size_type count) {
            assert(count > 0);
            T val{};
            resize(count, val);
        }
        void resize(size_type count, T const & value) {
            assert(count > 0);
            if (count == cnt) {
                return;
            }

            if (count > cnt) {
                if (count + 1 > cap) {
                    resize_cap(count + 1);
                }
                for (size_t i{cnt}; i < count; i++) {
                    arr[i] = value;
                    cnt++;
                }
            } else {
                cnt = count;
            }
        }

        void swap (deque & other) noexcept {
            std::swap(first, other.first);
            std::swap(cnt, other.cnt);
            std::swap(cap, other.cap);
            std::swap(arr, other.arr);
        }
    };
}   // namespace swo
