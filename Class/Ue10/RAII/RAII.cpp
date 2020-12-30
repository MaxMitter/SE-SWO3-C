#include <iostream>
#include "RAII.h"

resource_manager get_rm() {
	resource_manager rm{ "X" };
	return rm;
}


int main() {
	resource_manager rm1{ "A" };
	resource_manager rm2{ "B" };
	resource_manager rm3{ std::move(rm2) };
	rm1 = get_rm();

	//resource_manager* p_rm = new resource_manager("Y"); dont use!
}