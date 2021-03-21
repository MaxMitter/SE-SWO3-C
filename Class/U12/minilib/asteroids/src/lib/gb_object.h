#pragma once
#include <ml5/ml5.h>
#include "shape.h"

class gb_object : public ml5::object, MI5_DERIVE(gb_object, ml5::object) {
	MI5_INJECT(gb_object)
	using context_t = ml5::paint_event::context_t;
public:
	void set_position(wxPoint new_pos) {
		m_pos = new_pos;
		m_shape->move_to(new_pos);
	}

	void set_context_size(wxSize size) {
		m_context_size = size;
	}

	void set_context_size(context_t& context) {
		m_context_size = context.GetSize();
	}

	wxSize get_context_size() {
		return m_context_size;
	}

	void set_speed(double speed) {
		m_speed = speed;
	}

	void rotate_angle(double angle) {
		rotate(angle * (pi / 180));
	}
	
	void rotate(double angle) {
		m_shape->rotate(angle);
	}

	double get_rotation() {
		return m_shape->get_rotation();
	}

	virtual bool shape_out_of_bounds(wxPoint pos, wxSize size) {
		return (pos.x < 0 || pos.y < 0 ||
				pos.x + size.x > m_context_size.x || pos.y + size.y > m_context_size.y);
	}
	
	bool move(wxPoint delta) {
		if (!shape_out_of_bounds(m_pos + delta, m_size)) {
			m_shape->move(delta);
			m_pos += delta;
		} else {
			return false;
		}
	}

	bool move() {
		if (m_speed > 0.1)
			return move(wxPoint{ int(sin(m_shape->get_rotation()) * m_speed) * -1, int(cos(m_shape->get_rotation()) * m_speed) * -1});

		return false;
	}

	wxPoint get_position() {
		return m_pos;
	}

	wxSize get_size() {
		return m_size;
	}

	double get_speed() {
		return m_speed;
	}

	virtual int get_level() {
		return 0;
	}

	virtual void draw(context_t& context) {
		m_shape->draw(context);
	}

	void kill() {
		m_is_alive = false;
	}

	void revive() {
		m_is_alive = true;
	}

	bool is_alive() {
		return m_is_alive;
	}

	int top() {
		return m_shape->top_bound();
	}

	int left() {
		return m_shape->left_bound();
	}

	int bot() {
		return m_shape->bot_bound();
	}

	int right() {
		return m_shape->right_bound();
	}

	virtual std::unique_ptr<gb_object> shoot() {
		return nullptr;
	}

	virtual bool within_spawn_protection(const wxPoint& p) {
		return false;
	}
	
protected:

	gb_object(wxPoint pos, wxSize size)
		: m_pos{ pos }
		, m_size { size } {}

	wxPoint m_pos{};
	wxSize m_size{};
	std::unique_ptr<shape> m_shape{};
	wxSize m_context_size{};

	double m_speed{ 0.0 };
	bool m_is_alive{ true };
};