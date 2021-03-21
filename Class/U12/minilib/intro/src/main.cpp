#include <ml5/ml5.h>

using std::cout;
using std::endl;

using namespace std::string_literals;

static void test_containers() {
	ml5::vector<ml5::string> cont;
	//ml5::container<ml5::string>& cont = v;

	cont.add("Linz"s);
	cont.add("Hagenberg"s);
	cont.add("Salzburg"s);
	cont.add("New York"s);
	cont.add("Wien"s);

	cont.remove("New York"s);

	cout << "------------------------ operator[] -----------------------" << endl;
	for (size_t i = 0; i < cont.size(); i++) {
		cout << cont[i] << endl;
	}

	std::unique_ptr<ml5::iterator<ml5::string>> it1 = cont.make_iterator();

	cout << "------------------------ iterator(while) -----------------------" << endl;
	while(it1->not_at_end()) {

		cout << it1->get_current() << endl;

		it1->to_next();
	}

	cout << "------------------------ iterator(for) -----------------------" << endl;
	for (auto it2 = cont.make_iterator(); it2->not_at_end(); it2->to_next()) {
		cout << it2->get_current() << endl;
	}

	cout << "------------------------ iterator(for 2) -----------------------" << endl;
	for (auto it3 = cont.begin(); it3 != cont.end(); ++it3) {
		cout << *it3 << endl;
	}

	cout << "------------------------ iterator(range based for) -----------------------" << endl;
	for (auto city : cont) {
		cout << city << endl;
	}
}

class my_class : public ml5::object, MI5_DERIVE(my_class, ml5::object) {
	MI5_INJECT(my_class)
	public:
		my_class() = default;
		~my_class() = default;
};

static void test_metadata() {
	ml5::string str{ "Hello" };

	cout << "------------------------------------- is_a -------------------------------------" << endl;
	cout << std::boolalpha;
	cout << "str.is_a<ml5::string>() -> " << str.is_a<ml5::string>() << endl;
	cout << "str.is_a<ml5::object>() -> " << str.is_a<ml5::object>() << endl;
	cout << "str.is_a<ml5::vector<int>>() -> " << str.is_a<ml5::vector<int>>() << endl;

	cout << "------------------------------------- meta_info(1) -------------------------------------" << endl;
	ml5::object* obj1 = new my_class();
	const auto &meta_inf1 = obj1->get_metainfo();
	cout << "class_name -> " << meta_inf1.name() << endl;
	cout << "class.bases() -> " << endl;
	for (const auto &mi : meta_inf1.bases()) {
		cout << mi->get().name() << " ";
	}
	cout << endl;

	cout << "------------------------------------- meta_info(2) -------------------------------------" << endl;
	const auto& meta_inf2 = ml5::get_metainfo<my_class>();
	cout << "class_name -> " << meta_inf2.name() << endl;
	cout << "class.bases() -> " << endl;
	for (const auto& mi : meta_inf2.bases()) {
		cout << mi->get().name() << " ";
	}
	cout << endl;



	
	delete obj1;
};

int main () {
	std::cout << "detected os:       " << ml5::util::detected_os_as_string () << "\n"
			  "detected compiler: " << ml5::util::detected_compiler_as_string () << "\n"
			  "MiniLib version:   " << ml5::version << "\n" << std::endl;


	ml5::string s{ "Hello ML5" };

	cout << s << endl;

	cout << "============================== test_containers ====================================" << endl;
	test_containers();

	cout << "============================== test_metadata ====================================" << endl;
	test_metadata();
	
}
