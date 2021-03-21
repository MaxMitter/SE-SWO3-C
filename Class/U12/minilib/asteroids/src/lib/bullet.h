#pragma once
#include <ml5/ml5.h>
#include "gb_object.h"
#include "image.h"

class bullet : public gb_object, MI5_DERIVE(bullet, gb_object) {
	MI5_INJECT(bullet)
		using base = gb_object;
public:
	bullet(wxPoint pos, wxSize player_size, double rotation) : base(wxPoint{ pos.x, pos.y }, 
																wxSize{ std::max(5, int(player_size.x * 0.2)),
																		std::max(10, int(player_size.x * 0.4)) }) {
		m_shape = std::make_unique<image>(wxRect{ get_position(), get_position() + m_size }, *wxBLACK_PEN, *wxWHITE_BRUSH,
			"C:\\Users\\maxmi\\Documents\\FH\\SWO\\c-code\\Class\\U12\\minilib\\asteroids\\src\\img\\bullet.png", 0.0);
		m_speed = 5.0;
		m_shape->rotate(rotation);
		move();
	}

	bool shape_out_of_bounds(wxPoint pos, wxSize size) override {
		return (pos.x + size.x < 0 || pos.y + size.y < 0 ||
			m_pos.x > m_context_size.x || m_pos.y > m_context_size.y);
	}

private:
};