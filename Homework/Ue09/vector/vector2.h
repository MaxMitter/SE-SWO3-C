#pragma once

#include <iostream>
#include <cstddef>
#include <cassert>
#include <exception>
#include <string>

namespace swo {

	template<typename T>
	void copy2(T* dest, const T* source, std::size_t size) {
		for (size_t i = 0; i < size; i++) {
			dest[i] = source[i];
		}
	}

	template<typename T>
	class vector2 {
	public:
		using size_t = std::size_t;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;

		class iterator final {
		public:
			iterator() = delete;

			explicit iterator(pointer pos) : m_pos{ pos } {

			}

			bool operator==(const iterator& other) {
				return m_pos == other.m_pos;
			}

			bool operator!=(const iterator& other) {
				return !operator==(other);
			}

			iterator operator++() {
				++m_pos;
				return *this;
			}

			iterator operator++(int) {
				iterator tmp{ *this };
				++m_pos;
				return tmp;
			}

			reference operator*() {
				return *m_pos;
			}
		private:
			pointer m_pos{ nullptr };
		};

		vector2() = delete;
		vector2(size_t capacity) :
			m_data{ new value_type[capacity] {} },  // durch {} initialisierung des allocierten Speicher, kann hier in diesem Beispiel aber weggelassen werden 
			m_size{ 0 },
			m_capacity{ capacity } {
		}

		vector2(const vector2& other) :
			m_data{ new value_type[other.m_capacity] },
			m_size{ other.m_size },
			m_capacity{ other.m_capacity } {

			swo::copy2(this->m_data, other.m_data, other.m_size);
		}

		vector2(vector2&& other) : m_capacity{ other.m_capacity }, m_data{ other.m_data }, m_size{ other.m_size } {
			other.m_data = nullptr;
		}

		vector2(const std::initializer_list<value_type>& list) : m_capacity{ list.size() }, m_data{ new value_type[list.size()] }, m_size{ list.size() } {
			swo::copy2(m_data, list.begin(), list.size());
		}

		~vector2() {
			delete[] m_data;
		}

		void clear() {
			m_capacity = 0;
			m_size = 0;
			delete[] m_data;
			m_data = nullptr;
		}

		value_type& operator[](size_t index) {
			if (index >= m_size) {
				throw std::out_of_range("index " + std::to_string(index)
					+ " out of range [0, " + std::to_string(m_size - 1) + "]");
			}

			return m_data[index];
		}

		const value_type& operator[](size_t index) const {
			if (index >= m_size) {
				throw std::out_of_range("index " + std::to_string(index)
					+ " out of range [0, " + std::to_string(m_size - 1) + "]");
			}

			return m_data[index];
		}

		void push_back(const value_type& value) {
			if (m_size >= m_capacity) {
				resize(std::max(1U, m_capacity * 2));
			}
			m_data[m_size++] = value;
		}

		void push_back(const value_type&& value) {
			if (m_size >= m_capacity) {
				resize(std::max(1U, m_capacity * 2));
			}
			m_data[m_size++] = std::move(value);
		}

		auto size() const { return m_size; }
		auto capacity() const { return m_capacity; }

		iterator begin() const {
			return iterator(m_data);
		}

		iterator end() const {
			return iterator(m_data + m_size);
		}

	private:
		void resize(size_t new_size) {
			assert(new_size > m_capacity);

			auto new_data = new value_type[new_size];

			for (size_t i = 0; i < m_size; i++) {
				new_data[i] = std::move(m_data[i]);
			}

			m_capacity = new_size;
			delete[] m_data;
			m_data = new_data;

		}

		value_type*		m_data{};
		size_t			m_size{};
		size_t			m_capacity{};
	};


	static std::ostream& print(const swo::vector2<std::string>& v, std::ostream& os = std::cout) {
		os << "[";
		for (std::size_t i = 0; i < v.size(); i++) {
			if (i > 0) os << ", ";
			os << v[i];
		}

		os << "]";

		return os;
	}
} // swo