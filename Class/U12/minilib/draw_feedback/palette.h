#include <cstdlib>
#include <ml5/ml5.h>
#include "shape.h"
#pragma once

struct tool final : shape {
	tool(shape_type t) : shape{ {0,0},*wxBLACK_PEN,*wxWHITE_BRUSH }, type{ t } {}


	shape_type get_shape_type() {
		return type;
	}

private:
	shape_type type;
	void do_draw(context& con) const override {
		con.SetPen(*wxWHITE_PEN);
		if (selected()) {
			con.SetBrush(*wxBLACK_BRUSH);
		}
		else {
			con.SetBrush(*wxWHITE_BRUSH);
		}

		con.DrawRectangle(aabb);

		wxRect r = aabb;
		r.Offset({ 5,5 });
		r.SetBottomRight(r.GetBottomRight() - wxPoint{ 10, 10 });

		if (!selected()) {
			con.SetPen(*wxBLACK_PEN);
		}


		switch (type) {
		case shape_type::arrow:
			con.DrawLine(r.GetBottomLeft(), r.GetTopRight());
			con.DrawLine(r.GetTopRight(), r.GetTopRight() - wxPoint{ 5, 0 });
			con.DrawLine(r.GetTopRight(), r.GetTopRight() - wxPoint{ 0, -5 });
			break;
		case shape_type::line:
			con.DrawLine(r.GetBottomLeft(), r.GetTopRight());
			break;
		case shape_type::rectangle:
			con.DrawRectangle(r);
			break;
		case shape_type::ellipse:
			con.DrawEllipse(r);
		}
	}

	tool* do_copy() override {
		return new tool(*this);
	}
};

struct palette final : shape {
	palette() : shape{ {0,0},*wxBLACK_PEN,*wxWHITE_BRUSH } {}
	~palette() {
		for (const auto& t : tools) {
			delete t;
		}
	}

	void add_tool(tool* t) {
		t->set_height(get_width() - 1);
		t->set_width(get_width() - 1);
		t->set_y(tools.size() * get_width());
		tools.add(t);
	}


	void select_tool(wxPoint pos) {
		for (const auto& t : tools) {
			if (t->contains(pos)) {
				t->select();
			}
			else {
				t->deselect();
			}
		}
	}

	void select_tool(shape_type type) {
		for (const auto& t : tools) {
			if (t->get_shape_type() == type) {
				t->select();
			}
			else {
				t->deselect();
			}
		}
	}

	shape_type get_next_shape() {
		for (const auto& t : tools) {
			if (t->selected()) {
				return t->get_shape_type();
			}
		}
	}

private:
	void do_draw(context& con) const override {
		con.DrawLine(aabb.GetTopRight(), aabb.GetBottomRight());
		for (const auto& t : tools) {
			t->draw(con);
		}
	}

	palette* do_copy() override{
		return new palette(*this);
	}
	ml5::vector<tool*> tools;
};

