#include <iostream> 
#include <fstream>
#include <iomanip>
#include "freq_table.h" 

namespace huff {
	std::string read_stream_of_file(std::string filename);

// freq_table_entry /////////////////////////////////////////////////////
	freq_table_entry::freq_table_entry() {
		this->m_c = 0;
		this->m_p = 0;
	}

	freq_table_entry::~freq_table_entry() {
	}


// freq_table /////////////////////////////////////////////////////
	freq_table::freq_table() {
	}

	freq_table::~freq_table() {
	}

	void freq_table::insert_entry(const char c, const double p) {
		m_entries[m_size].set_c(c);
		m_entries[m_size].set_p(p);
		m_size++;
	}

	void freq_table::create_freq_table(std::string filename) {
		stream = read_stream_of_file(filename);
		std::cout << "Stream: " <<stream << "\n";
		evaluate_stream(stream);
		insertion_sort();
	}

	void freq_table::evaluate_stream(std::string &stream) {
		for (size_t i = 0; i < stream.length(); i++) {
			char c = stream[i];
			if (!find_freq_table_entry(c)) {
				int count = 0; 
				for (size_t j = 0; j < stream.length(); j++) {
					if (c == stream[j]) count++;
				}
				double p = count * 100.0 / stream.length();
				insert_entry(c, p);
			}
		}
	}

	bool freq_table::find_freq_table_entry(const char c_entry) {
		for (size_t i = 0; i < m_size; i++) {
			if (c_entry == m_entries[i].get_c()) return true;
		}
		return false;
	}

	void freq_table::print_freq_table() const {
		std::cout << "C: P: " << "\n";
		std::cout << "------------" << "\n";
		for (size_t i = 0; i < m_size; i++) {
			std::cout << m_entries[i].get_c() << "  " << std::fixed << std::setprecision(2) << m_entries[i].get_p() << "\n";
		}
	}

	void freq_table::insertion_sort() {
		freq_table_entry key;
		int j;
		for (size_t i = 0; i < m_size; i++) {
			key = m_entries[i];
			j = i - 1;

			while (j >= 0 && m_entries[j].get_p() < key.get_p()) {
				m_entries[j + 1] = m_entries[j];
				j = j - 1;
			}
			m_entries[j + 1] = key;
		}
	}


////other functions//////////////////////////////////////////////
	std::string read_stream_of_file(std::string filename) {
		std::fstream file;
		std::string stream;
		file.open(filename, std::ios::in);
		if (!file)
			std::cout << "ERROR: No such input file";
		else {
			char ch = ' ';
			while (!file.eof()) {
				file >> ch;
				if (toupper(ch) >= 'A' && toupper(ch) <= 'Z') stream += toupper(ch);
				ch = '\0';
			}
			file.close();
		}
		return stream;
	}
}