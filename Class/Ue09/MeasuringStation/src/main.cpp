#include "./station.h"
#include "./pressure_sensor.h"
#include "./temperature_sensor.h"
#include "./broadcast_actor.h"
#include "./print_actor.h"
#include "./threshold_filter.h"

static void simulate() {
	std::cout
		<< "---------- creating stations --------------------------------\n\n";

	std::cout
		<< "\n---------- creating sensors, actors, and filters ------------\n\n";

	std::cout
		<< "\n---------- wiring sensors, actors, and filters --------------\n\n";

	std::cout
		<< "\n---------- driving the application --------------------------\n";

	std::cout
		<< "\n---------- deleting stations --------------------------------\n\n";

	std::cout
		<< "\n---------- terminating the application ----------------------\n\n";
}

int main() {
	simulate();
}
