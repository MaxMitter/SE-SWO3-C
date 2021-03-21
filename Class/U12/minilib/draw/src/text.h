#pragma once
#include "shape.h"

class text : public shape, MI5_DERIVE(text, shape) {
	MI5_INJECT(text)
		using base = shape;
	using context_t = ml5::paint_event::context_t;

public:
	text(const wxRect& box, const wxPen& pen, const wxBrush& brush, const std::string& text) : base(box, pen, brush), m_text{ text } {

	}

protected:
	void do_draw(context_t& context) const override {
		context.DrawText(m_text, m_box.GetPosition());
	}

	void normalise_shape() override {
		// normalising would change this shape
	}

private:
	std::string m_text{};
};