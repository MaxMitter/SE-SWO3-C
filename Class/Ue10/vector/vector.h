#pragma once
#include <cassert>

template<typename T>
class vector {

	public:

		using value_type = T;
		vector() = delete;
		vector(int capacity) :
			m_data{ new T[capacity] },
			m_size{ 0 },
			m_capacity{ capacity }
			{}
		
		~vector() {
			delete[] m_data;
		}

		void push_back(const value_type& value) {
			if (m_size >= m_capacity) {
				resize(std::max(1U, m_capacity * 2))
			}

			m_data[m_size++] = value;
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
		}

		T* m_data{};
		size_t m_size{};
		size_t m_capacity{};

};
