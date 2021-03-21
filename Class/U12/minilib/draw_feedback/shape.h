#include <cstdlib>
#include <ml5/ml5.h>
#pragma once

enum class shape_type { line, rectangle, ellipse, arrow };

struct shape : ml5::object {
	using context = ml5::paint_event::context_t;

	shape(wxPoint point, const wxPen& pen, const wxBrush& brush) : aabb{ point, point }, pen{ pen }, brush{ brush } {}
	shape(const shape& s) : aabb{ s.aabb }, pen{ s.pen }, brush{ s.brush } {}
	shape(shape&& s) = default;
	~shape() {};

	void draw(context& con) const {
		con.SetPen(pen);
		con.SetBrush(brush);
		do_draw(con);
	}

	auto empty() const noexcept -> bool { return !aabb.GetHeight() && !aabb.GetWidth(); }

	auto contains(wxPoint pos) const noexcept -> bool { return aabb.Contains(pos); }

	void set_left_top(wxPoint pos) { aabb.SetLeftTop(pos); }
	void set_right_bottom(wxPoint pos) {
		if ((pos.x > aabb.GetTopLeft().x) &&
			(pos.y > aabb.GetTopLeft().y)) {
			aabb.SetRightBottom(pos);
		}
	}

	void move(wxPoint offset) { aabb.Offset(offset); }

	std::unique_ptr<shape> copy() {
		std::unique_ptr<shape> s{do_copy()};
		return s;
	}

	void select() { is_selected = true; }
	void deselect() { is_selected = false; }
	bool selected() const { return is_selected; }

	int get_height() { return aabb.GetHeight(); }
	int get_width() { return aabb.GetWidth(); }
	void set_height(int height) { aabb.height = height; }
	void set_width(int width) { aabb.width = width; }
	void set_x(int x) { aabb.x = x; }
	void set_y(int y) { aabb.y = y; }

protected:
	wxRect aabb;
	virtual void do_draw(context& con) const {
		if (selected()) {
			con.SetPen(*wxBLACK_PEN);
			con.SetBrush(*wxBLACK_BRUSH);
			con.DrawRectangle(aabb.GetLeftTop() - wxPoint(2, 2), wxSize(4, 4));
			con.DrawRectangle(aabb.GetRightTop() - wxPoint(2, 2), wxSize(4, 4));
			con.DrawRectangle(aabb.GetLeftBottom() - wxPoint(2, 2), wxSize(4, 4));
			con.DrawRectangle(aabb.GetRightBottom() - wxPoint(2, 2), wxSize(4, 4));
			con.SetPen(pen);
			con.SetBrush(brush);
		}
	}

	virtual shape* do_copy() = 0;

private:
	const wxPen pen;
	const wxBrush brush;
	bool is_selected{ false };
};

struct line final : shape {
	using shape::shape; // inherit ctor from shape
private:
	void do_draw(context& con) const override {
		con.DrawLine(aabb.GetLeftTop(), aabb.GetRightBottom());
		if (selected()) {
			con.SetPen(*wxBLACK_PEN);
			con.SetBrush(*wxBLACK_BRUSH);
			con.DrawRectangle(wxRect(aabb.GetLeftTop() - wxPoint{ 2,2 }, wxSize{ 4,4 }));
			con.DrawRectangle(wxRect(aabb.GetRightBottom() - wxPoint{ 2,2 }, wxSize{ 4,4 }));
		}
	}

	line* do_copy() override {
		return new line(*this);
	}
};

struct ellipse final : shape {
	using shape::shape; // inherit ctor from shape
private:
	void do_draw(context& con) const override {
		con.DrawEllipse(aabb);
		shape::do_draw(con);
	}

	ellipse* do_copy() override {
		return new ellipse(*this);
	}
};

struct rectangle final : shape {
	using shape::shape; // inherit ctor from shape
private:
	void do_draw(context& con) const override {
		con.DrawRectangle(aabb);
		shape::do_draw(con);
	}

	rectangle* do_copy() override{
		return new rectangle(*this);
	}
};