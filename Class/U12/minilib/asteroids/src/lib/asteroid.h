#pragma once
#include <ml5/ml5.h>
#include <random>
#include "gb_object.h"
#include "image.h"

class asteroid : public gb_object, MI5_DERIVE(asteroid, gb_object) {
	MI5_INJECT(asteroid)
	using base = gb_object;
	using context_t = ml5::paint_event::context_t;
public:

	asteroid(wxPoint pos) : base(pos, wxSize{ 10, 10 }) {
		m_shape = std::make_unique<image>(wxRect{ get_position(), get_position() + m_size }, *wxBLACK_PEN, *wxWHITE_BRUSH,
			"C:\\Users\\maxmi\\Documents\\FH\\SWO\\c-code\\Class\\U12\\minilib\\asteroids\\src\\img\\asteroid.png", 0.0);
	}

	asteroid(wxPoint pos, int level) : base(pos, wxSize{ 10 * level, 10 * level }), m_level{ level } {
		m_shape = std::make_unique<image>(wxRect{ get_position(), get_position() + m_size }, *wxBLACK_PEN, *wxWHITE_BRUSH,
			"C:\\Users\\maxmi\\Documents\\FH\\SWO\\c-code\\Class\\U12\\minilib\\asteroids\\src\\img\\asteroid.png", 0.0);
		m_speed = 1.5;
		rotate_random_angle();
	}

	asteroid(wxPoint pos, int level, int rotation) : base(pos, wxSize{ 10 * level, 10 * level }), m_level{ level } {
		m_shape = std::make_unique<image>(wxRect{ get_position(), get_position() + m_size }, *wxBLACK_PEN, *wxWHITE_BRUSH,
			"C:\\Users\\maxmi\\Documents\\FH\\SWO\\c-code\\Class\\U12\\minilib\\asteroids\\src\\img\\asteroid.png", 0.0);
		m_speed = 1.5;
		rotate_angle(rotation);
	}

	void rotate_random_angle() {
		std::random_device seeder;
		std::mt19937 generator(seeder());
		std::uniform_int_distribution<int> distr(0, 360);
		rotate_angle(distr(generator));
	}

	void draw(context_t& context) override {
		m_shape->draw(context);
	}

	bool shape_out_of_bounds(wxPoint pos, wxSize size) override {
		if (m_context_size.x == 0 && m_context_size.y == 0) {
			return false;
		}
		return (pos.x + size.x < 0 || pos.y + size.y < 0 ||
			m_pos.x > m_context_size.x || m_pos.y > m_context_size.y);
	}

	int get_level() override {
		return m_level;
	}
	
private:
	int m_level{ 5 };
};