#include <iostream>
#include <fstream>
#include <string>
#include <new>
#include "huffman_list.h"
#include "frequency_table.h"
#include "huffman_tree.h"
using namespace std;

int main(int argc, char const* argv[]) {
	auto e1 = new huffman_tree_node('A', 33);
	auto e2 = new huffman_tree_node('N', 8);
	auto e3 = new huffman_tree_node('R', 15);
	auto e4 = new huffman_tree_node('C', 32);
	auto e5 = new huffman_tree_node('D', 12);

	auto ht1 = new huffman_tree();

	ht1->insert_node(e1);
	ht1->insert_node(e2);
	ht1->insert_node(e3);
	ht1->insert_node(e4);
	ht1->insert_node(e5);

	ht1->print();

	/*auto e1 = new huffman_list_entry('A', 33);
	auto e2 = new huffman_list_entry('N', 8);
	auto e3 = new huffman_list_entry('R', 15);
	auto e4 = new huffman_list_entry('C', 32);
	auto e5 = new huffman_list_entry('D', 12);

	auto hl1 = new huffman_list();

	hl1->add_entry(e1);
	hl1->add_entry(e2);
	hl1->add_entry(e3);
	hl1->add_entry(e4);
	hl1->add_entry(e5);

	hl1->print();*/

	//frequency_table* table = new frequency_table();
	//string line;
	/*ifstream file(argv[1]);
	if (file.is_open()) {
		while (getline(file, line)) {
			for (int i = 0; i < line.length(); i++) {
				table->add_character(line[i]);
			}
		}

		file.close();
	}*/

	//string line = "AACCCNNDDDAACCCCCRRAACCCCNNNADDDDDCCCAAACCNAAAAACCDDDDRRAAAANCCCRRAAAAARRRCCCCAARRAAAAAAACCCRRRRNCCC";
	//for (int i = 0; i < line.length(); i++) {
	//	table->add_character(line[i]);
	//}
	//
	//table->update_table();
	//table->print();
	//
	//huffman_list* list = new huffman_list(*table);
	//
	//list->print();

	return 0;
}