#include "./actor.h"
#include "./sensor.h"
#include "./station.h"

#include <thread>

namespace util {

	void sleep_for_a_while(std::chrono::milliseconds const duration) {
		std::this_thread::sleep_for(duration);
	}

} // namespace util
