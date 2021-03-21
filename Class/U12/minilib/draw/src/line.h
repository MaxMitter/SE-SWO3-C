#pragma once

#include "shape.h"

class line : public shape, MI5_DERIVE(line, shape) {
	MI5_INJECT(line)
	using base = shape;
	using context_t = ml5::paint_event::context_t;

public:
	line(const wxRect& box, const wxPen& pen, const wxBrush& brush) : base(box, pen, brush) {

	}

	protected:
		void do_draw(context_t& context) const override {
			context.DrawLine(m_box.GetTopLeft(), m_box.GetBottomRight());
		}

		// normalising would change this shape
		void normalise_shape() override{}


private:

};