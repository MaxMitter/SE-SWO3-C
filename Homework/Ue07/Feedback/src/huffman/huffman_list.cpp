#include <iostream> 
#include "huffman_list.h"

namespace huff {

// huffman_list //////////////////////////////////////////////
	huffman_list::huffman_list() {
	}

	huffman_list::~huffman_list() {
	}


	void huffman_list::prepend_node(const char& c, const double& p) {
		huffman_list_node* m = new huffman_list_node(c, p);
		if (list_size == 0) {
			m->set_next(nullptr);
			head = m;
		}
		else {
			m->set_next(head);
			head = m;
		}
		list_size++;
	}

	void huffman_list::create_huffman_list(freq_table& freq_table) {
		for (size_t i = 0; i < freq_table.get_m_size(); i++) {
			prepend_node(freq_table.get_m_entries(i).get_c(), freq_table.get_m_entries(i).get_p());
		}
	}

	void huffman_list::print_huffman_list() const {
		huffman_list_node n = *head;
		for (size_t i = 0; i < list_size; i++) {
			n.get_tree().print_huffman_tree();
			if (i < list_size - 1) n = n.get_next();
		}
	}

	void huffman_list::create_huffman_tree() {
		while (list_size > 1) {
			huffman_list_node* n = new huffman_list_node;
			huffman_tree_node* t = new huffman_tree_node;
			huffman_tree* new_tree = new huffman_tree;
			t->set_left(head->get_tree().get_head());
			t->set_right(head->get_next().get_tree().get_head());
			t->set_c('-');
			t->set_p(head->get_tree().get_head()->get_p() + head->get_next().get_tree().get_head()->get_p());
			new_tree->set_head(*t);
			n->set_tree(*new_tree);

			huffman_list_node* curr = new huffman_list_node;
			curr = head;
			for (size_t i = 0; i < list_size - 1; i++) {
				if (curr->get_next().get_tree().get_head()->get_p() > n->get_tree().get_head()->get_p()) {
					break;
				}
				curr = &curr->get_next();
			}

			n->set_next(&curr->get_next());
			curr->set_next(n);

			head = &head->get_next().get_next();
			list_size--;
		}
	}

	void create_bit_code(coding_table &cod_tab, huffman_tree_node tree, std::string bit_code) {
		if (&tree != nullptr) {
			if (tree.get_c() != '-') {
				cod_tab.insert_entry(tree.get_c(), bit_code);
			}
			if (tree.get_left() != nullptr) {
				create_bit_code(cod_tab, *tree.get_left(), bit_code + '0');
			}
			if (tree.get_right() != nullptr) {
				create_bit_code(cod_tab, *tree.get_right(), bit_code + '1');
			}
		}
	}

	coding_table huffman_list::create_coding_table() {
		coding_table cod_tab;
		create_bit_code(cod_tab, *head->get_tree().get_head(), "");
		return cod_tab;
	}

// huffman_list_node ///////////////////////////////////////////////////////////////////////////
	huffman_list_node::huffman_list_node() {
	}

	huffman_list_node::huffman_list_node(char letter, double perc)
		: next{ nullptr },
		  tree{ letter, perc } {
	}

	huffman_list_node::~huffman_list_node() {
	}

} 