#include "./actor.h"
#include "./sensor.h"

actor::~actor() {
}

actor::actor(const std::string &name) {
}

//void actor::detach_from_all_sensors() {
//	m_detaching = true;
//	for (sensor *s : m_sensors) {
//		s->detach(*this);
//		cout_actor() << "Detached from sensor '" << s->get_name() << "'.\n";
//	}
//	m_sensors.clear();
//	m_detaching = false;
//}
//
//void actor::got_attached_to(sensor &sensor) {
//	if (!util::contains(m_sensors, sensor)) {
//		m_sensors.push_back(&sensor);
//		cout_actor() << "Got attached to Sensor '" << sensor.get_name() << "'\n";
//	}
//}
//
//void actor::got_detached_from(sensor &sensor) {
//	if (!m_detaching && util::erase_if_contained(m_sensors, sensor)) {
//		cout_actor() << "Got detached from Sensor '" << sensor.get_name() << "'\n";
//	}
//}
