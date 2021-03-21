#pragma once

#include "shape.h"
#include <string>
#include <ml5/ml5.h>

class image : public shape, MI5_DERIVE(image, shape) {
	MI5_INJECT(image)
		using base = shape;
	using context_t = ml5::paint_event::context_t;

public:
	image(const wxRect& box, const wxPen& pen, const wxBrush& brush, const std::string& path, const double rotation)
	: base(box, pen, brush)
	, m_img_src{ path }
	, m_rotation{ rotation }{
		m_source_img.LoadFile(m_img_src, wxBITMAP_TYPE_PNG);
		m_source_img.Rescale(m_box.width, m_box.height);
		rotate_angle(rotation);
	}

	void rotate_angle(const double angle) {
		rotate(angle * (pi / 180));
	}
	
	void rotate (const double angle) override {
		m_rotation += angle;

		set_rot_center();
		m_render_img = m_source_img.Rotate(m_rotation, m_rot_center);
	}

	void set_rot_center() {
		wxPoint img_center{ m_box.width / 2, m_box.height / 2 };
		m_rot_center = wxPoint{ m_box.GetTopLeft().x + img_center.x, m_box.GetTopLeft().y + img_center.y };
	}

	double get_rotation() override {
		return m_rotation;
	}

	void draw_debug(context_t& context, wxColor col, int rad) {
		context.SetBrush(wxBrush{ col });
		context.DrawRectangle(m_box);
		set_rot_center();
		do_draw(context);
	}

	void draw(context_t& context) override {
		set_rot_center();
		do_draw(context);
	}

	void center_in_context(wxSize context) {
		m_box.SetPosition(wxPoint{ context.GetX() / 2 - m_box.GetSize().x / 2, context.GetY() / 2 - m_box.GetSize().y / 2 });
	}
	
protected:
	
	void do_draw(context_t& context) const override {
		//std::cout << "Position: " << m_box.GetPosition() << " | m_rot_center: " << m_rot_center << std::endl;
		context.DrawBitmap(m_render_img, m_rot_center.x - m_render_img.GetWidth() / 2, m_rot_center.y - m_render_img.GetHeight() / 2);
	}

	

private:
	std::string m_img_src{};
	wxPoint m_rot_center{};
	wxImage m_source_img{};
	wxImage m_render_img{};
	double m_rotation{};
};