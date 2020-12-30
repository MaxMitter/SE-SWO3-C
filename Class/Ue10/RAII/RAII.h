#pragma once
#include <string>
#include <iostream>
class resource_manager {

	public:
		resource_manager() = delete;
		explicit resource_manager(std::string name) : m_name{ std::move(name) }, m_allocated{ true } {
			std::cout << "aquired resource '" << m_name << "'\n";
		}

		resource_manager(const resource_manager& other) = delete;

		resource_manager(resource_manager&& tmp) : m_name{ std::move(tmp.m_name) }, m_allocated{ true } {
			tmp.m_allocated = false;
			std::cout << "moved resource '" << m_name << "'\n";
		}
		~resource_manager() {
			if (m_allocated)
				std::cout << "released resource '" << m_name << "'\n";
		}

		resource_manager& operator=(const resource_manager& other) = delete;
		resource_manager& operator=(resource_manager&& tmp) {
			std::swap(m_name, tmp.m_name);
			std::swap(m_allocated, tmp.m_allocated);
			tmp.m_allocated = false;

			std::cout << "moved resource '" << m_name << "'\n";
			return *this;
		}
	private:
		std::string m_name{};
		bool m_allocated{ false };
};