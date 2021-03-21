#pragma once

#include <ml5/ml5.h>

class shape : public ml5::object, MI5_DERIVE(shape, ml5::object) {
	MI5_INJECT(shape)
	using context_t = ml5::paint_event::context_t;
	public:
		explicit shape(const wxRect &box, const wxPen &pen, const wxBrush &brush)
			: m_brush{ brush }
			, m_pen{ pen }
			, m_box{ box }
		{}

		void draw(context_t &context) {
			context.SetBrush(m_brush);
			context.SetPen(m_pen);
			do_draw(context);
		}

		void set_bottom_right(const wxPoint &end) {
			m_box.SetBottomRight(end);
		}

		bool is_colliding(const wxPoint &point) const {
			wxPoint top_left = m_box.GetTopLeft();
			wxPoint bot_right = m_box.GetBottomRight();
			
			int x1 = std::max(top_left.x, bot_right.x);
			int x2 = x1 == top_left.x ? bot_right.x : top_left.x;
			int y1 = std::max(top_left.y, bot_right.y);
			int y2 = y1 == top_left.y ? bot_right.y : top_left.y;

			return (point.x < x1&& point.x > x2) && (point.y < y1&& point.y > y2);
		}

		void move(const wxPoint &delta) {
			move_to(m_box.GetPosition() + (delta));
		}

		void move_to(const wxPoint &delta) {
			m_box.SetPosition(delta);
		}

		int left_bound() {
			return m_box.GetLeft();
		}

		int right_bound() {
			return m_box.GetRight();
		}

		int top_bound() {
			return m_box.GetTop();
		}

		int bot_bound() {
			return m_box.GetBottom();
		}

		virtual void normalise_shape() {
			wxPoint const new_tl{ std::min({m_box.GetTopLeft().x, m_box.GetTopRight().x, m_box.GetBottomLeft().x, m_box.GetBottomRight().x}),
							std::min({m_box.GetTopLeft().y, m_box.GetTopRight().y, m_box.GetBottomLeft().y, m_box.GetBottomRight().y})};
			
			wxPoint const new_tr{std::max({m_box.GetTopLeft().x, m_box.GetTopRight().x, m_box.GetBottomLeft().x, m_box.GetBottomRight().x}),
								std::min({m_box.GetTopLeft().y, m_box.GetTopRight().y, m_box.GetBottomLeft().y, m_box.GetBottomRight().y}) };
			
			wxPoint const new_bl{ std::min({m_box.GetTopLeft().x, m_box.GetTopRight().x, m_box.GetBottomLeft().x, m_box.GetBottomRight().x}),
								std::max({m_box.GetTopLeft().y, m_box.GetTopRight().y, m_box.GetBottomLeft().y, m_box.GetBottomRight().y}) };
			
			wxPoint const new_br{ std::max({m_box.GetTopLeft().x, m_box.GetTopRight().x, m_box.GetBottomLeft().x, m_box.GetBottomRight().x}),
							std::max({m_box.GetTopLeft().y, m_box.GetTopRight().y, m_box.GetBottomLeft().y, m_box.GetBottomRight().y}) };

			m_box.SetTopLeft(new_tl);
			m_box.SetTopRight(new_tr);
			m_box.SetBottomLeft(new_bl);
			m_box.SetBottomRight(new_br);
		}

	protected:
		virtual void do_draw(context_t& context) const = 0;
		
		wxBrush m_brush{};
		wxPen m_pen{};
		wxRect m_box{};
};