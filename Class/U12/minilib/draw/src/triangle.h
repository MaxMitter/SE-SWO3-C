#pragma once
#include "shape.h"

class triangle : public shape, MI5_DERIVE(triangle, shape) {
	MI5_INJECT(triangle)
		using base = shape;
	using context_t = ml5::paint_event::context_t;

public:
	triangle(const wxRect& box, const wxPen& pen, const wxBrush& brush) : base(box, pen, brush) {

	}

protected:
	void do_draw(context_t& context) const override {
		//context.DrawRectangle(m_box);
		wxPointList list{};
		wxPoint p1{ m_box.GetTopRight() };
		wxPoint p2{ m_box.GetTopLeft().x, m_box.GetTopLeft().y + ((m_box.GetBottomLeft().y - m_box.GetTopLeft().y) / 2) };
		wxPoint p3{ m_box.GetBottomLeft().x + ((m_box.GetBottomRight().x - m_box.GetBottomLeft().x) / 2), m_box.GetBottomLeft().y };
		list.Append(&p1);
		list.Append(&p2);
		list.Append(&p3);

		context.DrawPolygon(&list);
	}

	void normalise_shape() override {
		// normalising would change this shape
	}
	
private:

};