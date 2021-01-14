#include "deque.h"

namespace swo {

    using size_type = std::size_t;
    //##### helper functions #####//

    template<typename T>
    bool deque<T>::full() {
        return m_elements >= m_size;
    }

    template<typename T>
    size_type deque<T>::inc_deque_pointer(size_type* pointer) {
        size_type old_value = *pointer;
        if (*pointer == m_size - 1)
            *pointer = 0;
        else
            (*pointer)++;

        return old_value;
    }

    template<typename T>
    size_type deque<T>::dec_deque_pointer(size_type* pointer) {
        size_type old_value = *pointer;
        if (*pointer == 0)
            *pointer = m_size - 1;
        else
            (*pointer)--;
        return old_value;
    }

    template<typename T>
    void copy(T* dest, T* source, size_t size) {
        for (size_t i = 0; i < size; i++) {
            dest[i] = source[i];
        }
    }

    //##### helper functions #####//

    template <typename T>
    void deque<T>::print() {
        std::cout << "Size: " << m_size << " | Elements: " << m_elements << std::endl;
        std::cout << "m_back: " << m_back << " | m_front: " << m_front << std::endl;
        for (size_type i = m_back + 1; i <= (m_elements + m_back); i++) {
            size_type index = i % m_size;
            std::cout << m_data[index] << ", ";
        }
        std::cout << std::endl;
    }

    template <typename T>
    void deque<T>::set_at(size_type at, T value) {
        if (at >= 0 && at < m_size) {
            m_data[at] = value;
        }
    }

    //##### constructors #####//

    template <typename T>
    deque<T>::deque() : deque<T>(10) { }

    template <typename T>
    deque<T>::deque(size_type count)
        : deque <T>(count, T{})
    { }

    template <typename T>
    deque<T>::deque(size_type count, T const& value)
        : m_size{ count * 2 }
        , m_data{ new T[m_size] }
        , m_front{ 0 }
        , m_back{ 0 }
        , m_elements{ 0 }
    {
        for (int i = 0; i < count; i++) {
            if (value != T{}) {
                push_front(value);
            }
        }
    }

    template <typename T>
    deque<T>::deque(deque const& src)
        : m_size{ src.m_size }
        , m_front{ src.m_front }
        , m_back{ src.m_back }
        , m_elements{ src.m_elements }
        , m_data{ new T[m_size] } {

        swo::copy(this->m_data, src.m_data, src.m_size);
    }

    template <typename T>
    deque<T>::deque(deque&& src) noexcept
        : m_size{ src.m_size }
        , m_front{ src.m_front }
        , m_back{ src.m_back }
        , m_elements{ src.m_elements }
        , m_data{ src.m_data } {
        src.m_size = 0;
        src.m_front = 0;
        src.m_back = 0;
        src.m_elements = 0;
        src.m_data = nullptr;
    }

    template <typename T>
    deque<T>::deque(std::initializer_list <T> init)
        : deque<T>(init.size())
    {
        for (auto& e : init) {
            push_front(e);
        }
    }

    //##### constructors #####//

    //##### destructors #####//

    template <typename T>
    deque<T>::~deque() {
        delete[] m_data;
    }

    //##### destructors #####//

    //##### resize functions #####//

    template <typename T>
    void deque<T>::resize(size_type count) {
        size_type offset = count - m_size;
        assert(count > m_size);

        auto new_data = new value_type[count];
        for (size_type i = 0; i < m_size; i++) {
            if (i > m_front) {
                new_data[i + offset] = std::move(m_data[i]);
            }
            else {
                new_data[i] = std::move(m_data[i]);
            }
        }

        m_back = (m_back == 0) ? 0 : m_back + offset;
        m_size = count;
        delete[] m_data;
        m_data = new_data;
    }

    template <typename T>
    void deque<T>::resize(size_type count, T const& value) {
        size_type offset = count - m_size;
        assert(offset > 0);

        auto new_data = new value_type[count];
        for (size_type i = 0; i < m_size; i++) {
            if (i > m_front) {
                new_data[i + offset] = std::move(m_data[i]);
            }
            else {
                new_data[i] = std::move(m_data[i]);
            }
        }

        m_back = (m_back == 0) ? 0 : m_back + offset;
        m_size = count;
        delete[] m_data;
        m_data = new_data;
    }

    //##### push functions #####//

    template <typename T>
    void deque<T>::push_front(T const& value) {
        if (full()) {
            resize(std::max(1U, m_size * 2));
        }

        if (m_back == 0 && m_front == 0) {
            dec_deque_pointer(&m_back);
        }
        m_data[inc_deque_pointer(&m_front)] = value;
        m_elements++;
    }

    template <typename T>
    void deque<T>::push_front(T&& value) {
        if (full()) {
            resize(std::max(1U, m_size * 2));
        }

        if (m_back == 0 && m_front == 0) {
            dec_deque_pointer(&m_back);
        }
        m_data[inc_deque_pointer(&m_front)] = std::move(value);
        m_elements++;
    }

    template <typename T>
    void deque<T>::push_back(T const& value) {
        if (full()) {
            resize(std::max(1U, m_size * 2));
        }

        if (m_back == 0 && m_front == 0) {
            inc_deque_pointer(&m_front);
        }
        m_data[dec_deque_pointer(&m_back)] = std::move(value);
        m_elements++;
    }
    

    //##### push functions #####//
}