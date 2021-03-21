#pragma once
#include <ml5/ml5.h>
#include "gb_object.h"
#include "image.h"
#include "bullet.h"

class player : public gb_object, MI5_DERIVE(player, gb_object) {
	MI5_INJECT(player)
	using base = gb_object;
	public:
		player(wxPoint pos) : base(pos, wxSize{ std::max(10, int(pos.x * 0.1)), std::max(10, int(pos.x * 0.1)) }) {
			m_shape = std::make_unique<image>(wxRect{ get_position(), get_position() + m_size }, *wxBLACK_PEN, *wxWHITE_BRUSH, 
				"C:\\Users\\maxmi\\Documents\\FH\\SWO\\c-code\\Class\\U12\\minilib\\asteroids\\src\\img\\player.png", 0.0);
		}

		std::unique_ptr<gb_object> shoot() override {
			auto temp = std::make_unique<bullet>(m_pos, m_size, m_shape->get_rotation());
			temp->set_context_size(get_context_size());
			return temp;
		}

		bool within_spawn_protection(const wxPoint& p) override {
			return m_shape->is_colliding(p, m_spawn_protection_radius);
		}

		void draw(ml5::paint_event::context_t& context) override {
			m_shape->draw_debug()
		}

	private:
		int m_spawn_protection_radius{ 150 };
};