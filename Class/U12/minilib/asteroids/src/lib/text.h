#pragma once
#include "shape.h"

class text : public shape, MI5_DERIVE(text, shape) {
	MI5_INJECT(text)
		using base = shape;
	using context_t = ml5::paint_event::context_t;

public:
	text(const wxRect& box, const std::string& text) : base(box), m_text{ text } {

	}

	void set_text(std::string text) {
		m_text = text;
	}

protected:
	void do_draw(context_t& context) const override {
		context.SetFont(m_font);
		context.SetTextForeground(m_color);
		context.DrawText(m_text, m_box.GetPosition());
		context.SetBrush(*wxTRANSPARENT_BRUSH);
		context.SetPen(*wxWHITE_PEN);
		context.DrawRectangle(m_box);
	}

	void normalise_shape() override {
		// normalising would change this shape
		
	}

private:
	std::string m_text{};
	int m_font_size{ 10 };
	wxColor m_color{ "white" };
	wxFont m_font{m_font_size, wxMODERN, wxNORMAL, wxNORMAL, false, "monospace" };
};