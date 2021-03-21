//       $Id: deque.h 2709 2021-01-10 11:19:47Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/sw/swo3/trunk/Aufgaben/WS20/VZ/deque/deque.h $
// $Revision: 2709 $
//     $Date: 2021-01-10 12:19:47 +0100 (So., 10 Jän 2021) $
//   $Author: p20068 $
//   Creator: Peter Kulczycki
//  Creation: January 10, 2021
// Copyright: (c) 2021 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg.
//            It is distributed under the Boost Software License (see
//            https://www.boost.org/users/license.html).

#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <iostream>
#include <cassert>

namespace swo {

	using std::ostream;

template <typename T> class deque final {
   public:
      using const_reference = T const &;
      using reference       = T &;
      using size_type       = std::size_t;
      using value_type      = T;

      friend bool operator == (deque const & lhs, deque const & rhs) noexcept {
	      if (lhs.m_elements == rhs.m_elements) {
			  iterator left_it = lhs.begin();
			  iterator right_it = rhs.begin();
	      	  while (left_it <= lhs.end()) {
		      	  if ((*left_it) != (*right_it)) {
					  return false;
		      	  }
				  ++left_it;
				  ++right_it;
	      	  }
			  return true;
	      } else {
			  return false;
	      }
      }
      friend bool operator != (deque const & lhs, deque const & rhs) noexcept {
		  return !(operator==(lhs, rhs));
      }
      friend bool operator <  (deque const & lhs, deque const & rhs) noexcept {
		  iterator left_it = lhs.begin();
		  iterator right_it = rhs.begin();
      	  while (left_it <= lhs.end() && right_it <= rhs.end()) {
			  if (*left_it < *right_it) return true;
			  if (*left_it > *right_it) return false;
			  ++left_it;
			  ++right_it;
      	  }

		  return ((left_it == lhs.end()) && (right_it != rhs.end()));
      }
      friend bool operator <= (deque const & lhs, deque const & rhs) noexcept {
		  iterator left_it = lhs.begin();
		  iterator right_it = rhs.begin();
		  while (left_it <= lhs.end() && right_it <= rhs.end()) {
			  if (*left_it <= *right_it) return true;
			  if (*left_it > *right_it) return false;
			  ++left_it;
			  ++right_it;
		  }
		  return true;
      }
      friend bool operator >  (deque const & lhs, deque const & rhs) noexcept {
		  iterator left_it = lhs.begin();
		  iterator right_it = rhs.begin();
		  while (left_it <= lhs.end() && right_it <= rhs.end()) {
			  if (*left_it > *right_it) return true;
			  if (*left_it < *right_it) return false;
			  ++left_it;
			  ++right_it;
		  }

		  return ((left_it == lhs.end()) && (right_it != rhs.end()));
      }
      friend bool operator >= (deque const & lhs, deque const & rhs) noexcept {
		  iterator left_it = lhs.begin();
		  iterator right_it = rhs.begin();
		  while (left_it <= lhs.end() && right_it <= rhs.end()) {
			  if (*left_it >= *right_it) return true;
			  if (*left_it < *right_it) return false;
			  ++left_it;
			  ++right_it;
		  }

		  return true;
      }

      friend void swap (deque <T> & a, deque <T> & b) noexcept {
         a.swap (b);
      }

      class iterator final {
         public:
            using difference_type   = std::ptrdiff_t;
            using iterator_category = std::random_access_iterator_tag;
            using pointer           = T *;
            using reference         = T &;
            using value_type        = T;

            friend bool operator == (iterator const & lhs, iterator const & rhs) noexcept {
				return (lhs.m_data == rhs.m_data);
            }
            friend bool operator != (iterator const & lhs, iterator const & rhs) noexcept {
				return (lhs.m_data != rhs.m_data);
            }
            friend bool operator <  (iterator const & lhs, iterator const & rhs) noexcept {
				return (lhs.m_data < rhs.m_data);
            }
            friend bool operator <= (iterator const & lhs, iterator const & rhs) noexcept {
				return (lhs.m_data <= rhs.m_data);
            }
            friend bool operator >  (iterator const & lhs, iterator const & rhs) noexcept {
				return (lhs.m_data > rhs.m_data);
            }
            friend bool operator >= (iterator const & lhs, iterator const & rhs) noexcept {
				return (lhs.m_data >= rhs.m_data);
            }

            friend iterator operator + (iterator itor, difference_type offset) noexcept {
               return itor += offset;
            }

            friend iterator operator - (iterator itor, difference_type offset) noexcept {
               return itor -= offset;
            }

            iterator ();
            iterator (iterator const & src);

           ~iterator ();

            iterator & operator = (iterator const & src);

            reference operator *  ();
            pointer   operator -> ();

            reference operator [] (difference_type offset);

            iterator & operator ++ () noexcept;
            iterator   operator ++ (int) noexcept;
            iterator & operator -- () noexcept;
            iterator   operator -- (int) noexcept;

            iterator & operator += (difference_type offset) noexcept;
            iterator & operator -= (difference_type offset) noexcept;
		private:
			friend deque<T>;
			iterator(value_type* dec);
      	
			value_type* m_data;
      };

      deque ();
      explicit deque (size_type count);
      deque (size_type count, T const & value);

      deque (deque const & src);
      deque (deque && src) noexcept;
      deque (std::initializer_list <T> init);

      ~deque ();

      deque & operator = (deque const & src);
      deque & operator = (deque && src) noexcept;
      deque & operator = (std::initializer_list <T> init);

      const_reference operator [] (size_type pos) const {
          if (valid_position(pos)) {
              return m_data[pos];
          }
      }
      reference operator [] (size_type pos) {
          if (valid_position(pos)) {
              return m_data[pos];
          }
      }

      const_reference at(size_type pos) const {
          if (valid_position(pos)) {
              return m_data[pos];
          }
      }
      reference       at(size_type pos) {
          if (valid_position(pos)) {
              return m_data[pos];
          }
      }
      const_reference back() const {
          if (m_back != 0) {
              return m_data[inc_deque_pointer(m_back)];
          }
      }
      reference       back() {
          if (m_back != 0) {
              return m_data[inc_deque_pointer(m_back)];
          }
      }
      const_reference front() const {
          if (m_front != 0) {
              return m_data[dec_deque_pointer(m_front)];
          }
      }
      reference       front() {
          if (m_front != 0) {
              return m_data[dec_deque_pointer(m_front)];
          }
      }

      iterator begin () noexcept;
      iterator end   () noexcept;

      bool      empty() const noexcept {
          return m_elements == 0;
      }
      size_type size() const noexcept {
          return m_size;
      }

      void clear () noexcept;

      void push_back (T const & value);
      void push_back (T && value);
      void pop_back  ();

      void push_front (T const & value);
      void push_front (T && value);
      void pop_front  ();

      void resize (size_type count);
      void resize (size_type count, T const & value);

      void swap (deque & other) noexcept;


      void print();
	  friend ostream& operator<< (ostream& os, deque deq) {
		  deq.print();
		  return os;
	  }


      private:
          bool full();
          size_type inc_deque_pointer(size_type* pointer);
		  size_type inc_deque_pointer(size_type pointer) const {
			  return (pointer == m_size - 1) ? 0 : ++pointer;
          }
          size_type dec_deque_pointer(size_type* pointer);
          size_type dec_deque_pointer(size_type pointer) const {
              return (pointer == 0) ? m_size - 1 : --pointer;
          }

		  bool valid_position(size_type const pos) const {
			  return (pos < m_front || pos > m_back);
          }
          bool valid_position(size_type const pos) {
              return (pos < m_front || pos > m_back);
          }

		  iterator begin() const noexcept;
		  iterator end() const noexcept;

          size_type m_size{};
          size_type m_front{};
          size_type m_back{};
          size_type m_elements{};
          value_type* m_data{};
};

	template<typename T>
	using const_reference = T const&;
	template<typename T>
	using reference = T&;
	using size_type = std::size_t;
	template<typename T>
	using value_type = T;
	
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

		std::cout << "====================================" << std::endl;
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
	    : m_size{ count }
	    , m_data{ new T[m_size] }
	    , m_front{ 0 }
	    , m_back{ 0 }
	    , m_elements{ 0 } {
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

	    // special case if data was only pushed to the front
	    if (m_front == 0 && m_back != 0) {
	        m_front = m_size;
	    }

	    auto* new_data = new value_type[count];
	    for (size_type i = 0; i < m_size; i++) {
	        if (i >= m_front) {
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
	    resize(count);

	    for (size_type i = 0; i < offset; i++) {
	        push_front(value);
	    }
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
	    m_data[dec_deque_pointer(&m_back)] = value;
	    m_elements++;
	}

	template <typename T>
	void deque<T>::push_back(T&& value) {
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
	

	//##### pop functions #####//

	template <typename T>
	void deque<T>::pop_back() {
		if (m_elements > 0) {
			inc_deque_pointer(&m_back);
			m_elements--;
		}
	}

	template <typename T>
	void deque<T>::pop_front() {
		if (m_elements > 0) {
			dec_deque_pointer(&m_front);
			m_elements--;
		}
	}

	template <typename T>
	void deque<T>::clear() noexcept {
		m_elements = 0;
		m_back = 0;
		m_front = 0;
	}

	//##### pop functions #####//
	
	
	//##### operator functions #####//

	template <typename T>
	deque<T>& deque<T>::operator = (deque const& src) {
		if (&src != this) {
			delete[] m_data;
			
			m_size = src.m_size;
			m_elements = src.m_elements;
			m_front = src.m_front;
			m_back = src.m_back;
			m_data = new T[m_size];
			swo::copy(m_data, src.m_data, m_size);
		}
		return *this;
	}
	
	template <typename T>
	deque<T>& deque<T>::operator = (deque&& src) noexcept {
		if (&src != this) {
			delete[] m_data;

			m_size = src.m_size;
			m_elements = src.m_elements;
			m_front = src.m_front;
			m_back = src.m_back;
			m_data = src.m_data;

			src.m_size = 0;
			src.m_elements = 0;
			src.m_front = 0;
			src.m_back = 0;
			src.m_data = nullptr;
		}
		return *this;
	}

	template <typename T>
	deque<T>& deque<T>::operator = (std::initializer_list <T> init) {
		if (init.size() > m_size) {
			delete[] m_data;
			m_size = init.size() * 2;
			m_data = new T[m_size];
		}
		
		m_elements = init.size();
		m_front = 0;
		m_back = 0;

		for (T item : init) {
			push_front(item);
		}
	}
	
	//##### operator functions #####//


	//##### other functions #####//

	template <typename T>
	void deque<T>::swap(deque& other) noexcept {
		std::swap(this->m_back, other.m_back);
		std::swap(this->m_front, other.m_front);
		std::swap(this->m_size, other.m_size);
		std::swap(this->m_elements, other.m_elements);
		std::swap(this->m_data, other.m_data);
	}

	template <typename T>
	typename deque<T>::iterator deque<T>::begin() noexcept {
		return iterator(&m_data[inc_deque_pointer(m_back)]);
	}

	template <typename T>
	typename deque<T>::iterator deque<T>::end() noexcept {
		return iterator(&m_data[(m_elements + m_back) % m_size]);
	}

	template <typename T>
	typename deque<T>::iterator deque<T>::begin() const noexcept {
		return iterator(&m_data[inc_deque_pointer(m_back)]);
	}

	template <typename T>
	typename deque<T>::iterator deque<T>::end() const noexcept {
		return iterator(&m_data[(m_elements + m_back) % m_size]);
	}

	//##### other functions #####//
	
	//##### iterator functions #####//

	template <typename T>
	deque<T>::iterator::iterator()
		: m_data { nullptr }
	{ }

	template <typename T>
	deque<T>::iterator::iterator(iterator const & src)
		: m_data{ src.m_data }
	{ }

	template <typename T>
	deque<T>::iterator::iterator(value_type* dec)
		: m_data{ dec }
	{ }

	template <typename T>
	deque<T>::iterator::~iterator() { }

	template <typename T>
	typename deque<T>::iterator& deque<T>::iterator::operator=(iterator const& src) {
		m_data = src.m_data;
		return *this;
	}

	template <typename T>
	typename deque<T>::iterator::reference deque<T>::iterator::operator*() {
		return *m_data;
	}

	template <typename T>
	typename deque<T>::iterator::pointer deque<T>::iterator::operator->() {
		return m_data;
	}

	template <typename T>
	typename deque<T>::iterator::reference deque<T>::iterator::operator[](difference_type offset) {
		return m_data[offset];
	}

	template <typename T>
	typename deque<T>::iterator& deque<T>::iterator::operator++() noexcept {
		++m_data;
		return *this;
	}

	template <typename T>
	typename deque<T>::iterator deque<T>::iterator::operator++(int) noexcept {
		iterator tmp{ *this };
		++m_data;
		return tmp;
	}

	template <typename T>
	typename deque<T>::iterator& deque<T>::iterator::operator--() noexcept {
		--m_data;
		return *this;
	}

	template <typename T>
	typename deque<T>::iterator deque<T>::iterator::operator--(int) noexcept {
		iterator tmp{ *this };
		--m_data;
		return tmp;
	}

	template <typename T>
	typename deque<T>::iterator& deque<T>::iterator::operator+=(difference_type offset) noexcept {
		m_data += offset;
		return *this;
	}

	template <typename T>
	typename deque<T>::iterator& deque<T>::iterator::operator-=(difference_type offset) noexcept {
		m_data -= offset;
		return *this;
	}

	template <typename T>
	bool operator!=(typename deque<T>::iterator const& lhs, typename deque<T>::iterator const& rhs) noexcept {
		return !(operator==(lhs, rhs));
	}
	
	//##### iterator functions #####//


	
}   // namespace swo