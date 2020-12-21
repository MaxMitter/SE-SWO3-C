#include "./sensor.h"
#include "./actor.h"
#include "./station.h"
#include "./measurement.h"

#include <cassert>

sensor::~sensor() {
}

sensor::sensor(const std::string &name) {
}

sensor::sensor(const std::string &name, station &station) {
}

//void sensor::attach(actor &actor) {
//	if (!util::contains(m_actors, actor)) {
//		m_actors.push_back(&actor);
//		cout_sensor() << "Actor '" << actor.get_name() << "' attached.\n";
//		actor.got_attached_to(*this);
//	}
//}
//
//void sensor::detach(actor &actor) {
//	if (util::erase_if_contained(m_actors, actor)) {
//		actor.got_detached_from(*this);
//		cout_sensor() << "Actor '" << actor.get_name() << "' detached.\n";
//	}
//}
//
//void sensor::detach_all_actors() {
//	for (actor *a : m_actors) {
//		detach(*a);
//		a->got_detached_from(*this);
//	}
//
//	m_actors.clear();
//}
