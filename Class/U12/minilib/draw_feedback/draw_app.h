#include <cstdlib>
#include <ml5/ml5.h>
#include "shape.h"
#include "palette.h"
#pragma once

struct draw_app final : ml5::application {

	std::unique_ptr<ml5::window> make_window() const override {
		return std::make_unique<draw_win>();
	}

private:
	struct draw_win final : ml5::window {
		draw_win() : ml5::window("ML5.Draw") {}
	private:
		shape_type next_shape{ shape_type::line };
		enum class operation { none, moving, dragging };
		operation current_operation{ operation::none };

		void on_init() override {
			add_menu("&Shape", {
				{ "&Line", "The next shape will be a line." },
				{ "&Rectangle", "The next shape will be a rectangle." },
				{ "&Ellipse", "The next shape will be a ellipse." }
				});

			add_menu("&Edit", {
				{ "Cu&t", "Cut the currently selected shape" },
				{ "&Copy", "Copy the currently selected shape" },
				{ "&Paste", "Paste the currently selected shape" }
				});

			add_menu("&Brush", {
				{ "Blac&k", "The next shape will be drawn with a black brush."},
				{ "&Blue", "The next shape will be drawn with a blue brush."},
				{ "&Green", "The next shape will be drawn with a green brush."},
				{ "&Red", "The next shape will be drawn with a red brush."},
				{ "&White", "The next shape will be drawn with a white brush."},
				{ "&Light Gray", "The next shape will be drawn with a light gray brush."},
				});

			add_menu("&Pen", {
				{ "Blac&k", "" },
				{ "&Blue", "" },
				{ "&Green", "" },
				{ "&Red", "" },
				{ "&White", "" }
				});

			add_menu("Back&ground", {
				{ "Blac&k", "" },
				{ "&Blue", "" },
				{ "&Green", "" },
				{ "&Red", "" },
				{ "&Light Gray", "" },
				{ "&White", "" }
				});

			set_status_text("Use the mouse to draw or move a shape.");

			tool_palette = std::make_unique<palette>();
			tool_palette->set_right_bottom({ 30,this->get_height()});
			tool_palette->add_tool(new tool(shape_type::arrow));
			tool_palette->add_tool(new tool(shape_type::line));
			tool_palette->add_tool(new tool(shape_type::rectangle));
			tool_palette->add_tool(new tool(shape_type::ellipse));
		}

		void on_menu(const ml5::menu_event& event) override {
			const auto item{ event.get_title_and_item() };

			if (item == "Shape/Line") {
				next_shape = shape_type::line;
			}
			else if (item == "Shape/Rectangle") {
				next_shape = shape_type::rectangle;
			}
			else if (item == "Shape/Ellipse") {
				next_shape = shape_type::ellipse;
			}
			tool_palette->select_tool(next_shape);
			refresh();

			if (item == "Edit/Cut" || item == "Edit/Copy") {
				std::unique_ptr<shape>* tmp{ nullptr };
				for (auto& s : shapes) {
					if (s->selected()) {
						s->deselect();
						selected_shape = nullptr;
						tmp = &s;
					}
				}
				if (tmp) {
					clip = std::move((*tmp)->copy());

					if (item == "Edit/Cut") {
						shapes.remove(*tmp);
					}
				}
			}
			else if (item == "Edit/Paste") {
				if (clip) {
					clip->move({ 10,10 });
					shapes.add(std::move(clip->copy()));
				}
			}

			if (item == "Brush/Black") brush = *wxBLACK_BRUSH;
			if (item == "Brush/Blue") brush = *wxBLUE_BRUSH;
			if (item == "Brush/Green") brush = *wxGREEN_BRUSH;
			if (item == "Brush/Red") brush = *wxRED_BRUSH;
			if (item == "Brush/White") brush = *wxWHITE_BRUSH;
			if (item == "Brush/Light Gray") brush = *wxLIGHT_GREY_BRUSH;

			if (item == "Pen/Black") pen = *wxBLACK_PEN;
			if (item == "Pen/Blue") pen = *wxBLUE_PEN;
			if (item == "Pen/Green") pen = *wxGREEN_PEN;
			if (item == "Pen/Red") pen = *wxRED_PEN;
			if (item == "Pen/White") pen = *wxWHITE_PEN;

			if (event.get_title() == "Background") {
				if (item == "Background/Black") set_prop_background_brush(*wxBLACK_BRUSH);
				if (item == "Background/Blue") set_prop_background_brush(*wxBLUE_BRUSH);
				if (item == "Background/Green") set_prop_background_brush(*wxGREEN_BRUSH);
				if (item == "Background/Red") set_prop_background_brush(*wxRED_BRUSH);
				if (item == "Background/White") set_prop_background_brush(*wxWHITE_BRUSH);
				if (item == "Background/Light Gray") set_prop_background_brush(*wxLIGHT_GREY_BRUSH);
				refresh();
			}
		}

		auto make_shape(wxPoint pos) const -> std::unique_ptr<shape> {
			switch (next_shape) {
			case shape_type::line: return std::make_unique<line>(pos, pen, brush);
			case shape_type::rectangle: return std::make_unique<rectangle>(pos, pen, brush);
			case shape_type::ellipse: return std::make_unique<ellipse>(pos, pen, brush);
			default: throw std::logic_error("unknown shape_type");
			}
		}

		void on_paint(const ml5::paint_event& event) override {
			auto& con{ event.get_context() };
			tool_palette->set_right_bottom({ 30, this->get_height() });
			tool_palette->draw(con);
			for (const auto& s : shapes) s->draw(con);
			if (new_shape) new_shape->draw(con);
		}

		auto get_topmost_shape(wxPoint pos) -> std::unique_ptr<shape> {
			std::unique_ptr<shape>* tmp{ nullptr };
			for (auto& s : shapes) {
				if (s->contains(pos)) {
					tmp = &s; // save address of shape
				}
			}
			if (!tmp) return {};

			std::unique_ptr<shape> result{ std::move(*tmp) };
			shapes.remove(*tmp);
			return result;
		}

		wxPoint last_move_pos;

		void on_mouse_left_down(const ml5::mouse_event& event) override {
			assert(current_operation == operation::none);
			const auto pos{ event.get_position() };
			if (tool_palette->contains(pos)) {
				tool_palette->select_tool(pos);
				next_shape = tool_palette->get_next_shape();
				switch (next_shape) {
				case shape_type::line: set_status_text("The next shape will be a line.");
					break;
				case shape_type::rectangle: set_status_text("The next shape will be a rectangle.");
					break;
				case shape_type::ellipse: set_status_text("The next shape will be an ellipse.");
					break;
				case shape_type::arrow: set_status_text("Select a shape");
					break;
				}

				refresh();
				return;
			}

			if (next_shape != shape_type::arrow) {
				new_shape = make_shape(pos);
				current_operation = operation::dragging;
				refresh();
				return;
			}

			if (selected_shape) {
				selected_shape->deselect();
			}

			new_shape = get_topmost_shape(pos);
			if (new_shape) {
				last_move_pos = pos;
				current_operation = operation::moving;
				selected_shape = new_shape.get();
				selected_shape->select();
			}
			refresh(); // force redraw of window
		}

		void on_mouse_left_up(const ml5::mouse_event& event) override {
			if (!new_shape) return;
			if (new_shape->empty()) new_shape.reset();
			else shapes.add(std::move(new_shape));
			current_operation = operation::none;
			refresh(); // force redraw of window
		}

		void on_mouse_move(const ml5::mouse_event& event) override {
			if (!new_shape) return;
			const auto pos{ event.get_position() };
			switch (current_operation) {
			case operation::moving: {
				const auto offset{ pos - last_move_pos };
				last_move_pos = pos;
				new_shape->move(offset);
				break;
			} case operation::dragging: {
				new_shape->set_right_bottom(pos);
				break;
			}
			}
			refresh(); // force redraw of window
		}

		wxBrush brush{ *wxGREEN_BRUSH };
		wxPen pen{ *wxBLACK_PEN };

		ml5::vector<std::unique_ptr<shape>> shapes;
		std::unique_ptr<shape> new_shape;
		std::unique_ptr<palette> tool_palette;
		std::unique_ptr<shape> clip{ nullptr };
		shape* selected_shape{ nullptr };
	};
};
