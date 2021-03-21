#pragma once

#include "shape.h"

class rectangle : public shape, MI5_DERIVE(rectangle, shape) {
	MI5_INJECT(rectangle)
	using base = shape;
	using context_t = ml5::paint_event::context_t;

	public:
		rectangle(const wxRect& box, const wxPen& pen, const wxBrush& brush) : base(box, pen, brush) {
			
		}

	protected:
		void do_draw(context_t &context) const override {
			context.DrawRectangle(m_box);
		}

	private:
	
};