#pragma once
#include <string>

namespace huff {
	#define MAX_SIZE 100

	class freq_table_entry {
	public:
		freq_table_entry();
		~freq_table_entry(); 

		char get_c() const { return m_c; }
		double get_p() const { return m_p; }
		void set_c(const char c) { m_c = c; }
		void set_p(const double p) { m_p = p; }
		
	private:
		char m_c{ 0 };
		double m_p{ 0.0 };
	};

	class freq_table {
	public:
		freq_table();
		~freq_table();

		freq_table_entry get_m_entries(size_t i) { return m_entries [i]; }
		size_t get_m_size() const { return m_size; }
		std::string get_stream() { return stream; }

		void insert_entry(const char c, const double p);
		void create_freq_table(std::string filename);
		void print_freq_table() const;

	private:
		bool find_freq_table_entry(const char c_entry);
		void insertion_sort();
		void evaluate_stream(std::string& stream);

		freq_table_entry m_entries [MAX_SIZE];
		size_t m_size{ 0 };
		std::string stream;
	};
}