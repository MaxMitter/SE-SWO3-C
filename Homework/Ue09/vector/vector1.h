#pragma once
#include <iostream>
#include <cstddef>
#include <cassert>
#include <exception>
#include <string>

namespace swo {

	template<typename T>
	void copy1(T* dest, T* source, std::size_t size) {
		for (size_t i = 0; i < size; i++) {
			dest[i] = source[i];
		}
	}

	template<typename T>
	class vector1 {
	public:
		using size_t = std::size_t;
		using value_type = T;

		vector1() = delete;
		vector1(size_t capacity) :
			m_data{ new value_type[capacity] {} },  // durch {} initialisierung des allocierten Speicher, kann hier in diesem Beispiel aber weggelassen werden 
			m_size{ 0 },
			m_capacity{ capacity } {
		}

		vector1(const vector1& other) :
			m_data{ new value_type[other.m_capacity] },
			m_size{ other.m_size },
			m_capacity{ other.m_capacity } {

			swo::copy1(this->m_data, other.m_data, other.m_size);
		}

		vector1(vector1&& other) : m_capacity{ other.m_capacity }, m_data{ other.m_data }, m_size{ other.m_size } {
			other.m_data = nullptr;
		}

		~vector1() {
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

		value_type* m_data{};
		size_t			m_size{};
		size_t			m_capacity{};
	};


	static std::ostream& print(const swo::vector1<std::string>& v, std::ostream& os = std::cout) {
		os << "[";
		for (std::size_t i = 0; i < v.size(); i++) {
			if (i > 0) os << ", ";
			os << v[i];
		}

		os << "]";

		return os;
	}
} // swo