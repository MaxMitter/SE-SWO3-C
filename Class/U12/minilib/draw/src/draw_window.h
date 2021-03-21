#pragma once
#include <ml5/ml5.h>
#include "shape.h"
#include "line.h"
#include "rectangle.h"
#include "ellipse.h"
#include "triangle.h"
#include "text.h"

#define COOLDOWN 5

class draw_window : public ml5::window, MI5_DERIVE(draw_window, ml5::window) {
	MI5_INJECT(draw_window)

		enum class shape_t{ select, line, rectangle, ellipse, triangle, text };
	
	public:
		void on_init() override {
			add_menu("Shape", {
				{"Select", "Select an existing Object"},
				{"Line", "Draw a line"},
				{"Rectangle", "Draw a rectangle"},
				{"Ellipse", "Draw an ellipse"},
				{"Triangle", "Draw a triangle"}
				});
			
			add_menu("Width", {
					{"1px", "Change Width to 1px" },
					{"2px", "Change Width to 2px" },
					{"5px", "Change Width to 5px" },
					{"10px", "Change Width to 10px" },
					{"15px", "Change Width to 15px" },
					{"20px", "Change Width to 20px" } });

			add_menu("BorderColor", {
					{"Red", "Change Border Color to red."},
					{"Green", "Change Border Color to green."},
					{"Blue", "Change Border Color to blue."},
					{"Yellow", "Change Border Color to yellow."},
					{"Orange", "Change Border Color to orange."},
					{"Purple", "Change Border Color to purple."},
					{"Black", "Change Border Color to black."},
					{"White", "Change Border Color to white."} });
			
			add_menu("FillColor", {
					{"Red", "Change Fill Color to red."},
					{"Green", "Change Fill Color to green."},
					{"Blue", "Change Fill Color to blue."},
					{"Yellow", "Change Fill Color to yellow."},
					{"Orange", "Change Fill Color to orange."},
					{"Purple", "Change Fill Color to purple."},
					{"Black", "Change Fill Color to black."},
					{"White", "Change Fill Color to white."} });
		}
	
		void on_menu(ml5::menu_event const& event) override {
			std::string menu_title{event.get_title()};

			if (menu_title == "Shape") {
				change_shape(event.get_item());
			} else if (menu_title == "Width") {
				change_width(event.get_item());
			} else if (menu_title == "BorderColor") {
				change_border_color(event.get_item());
			} else if (menu_title == "FillColor") {
				change_fill_color(event.get_item());
			}
		}
	
		void on_mouse_left_down(ml5::mouse_event const& event) override {
			wxPoint const point{ event.get_position() };

			if (check_sidebar_collision(point))
				return;
			
			if (m_current_shape == shape_t::line)
				m_p_shape = std::make_unique<line>(wxRect{ point, point }, m_pen, m_brush);
			else if (m_current_shape == shape_t::rectangle)
				m_p_shape = std::make_unique<rectangle>(wxRect{ point, point }, m_pen, m_brush);
			else if (m_current_shape == shape_t::ellipse)
				m_p_shape = std::make_unique<ellipse>(wxRect{ point, point }, m_pen, m_brush);
			else if (m_current_shape == shape_t::select) {
				check_shape_collision(point);
			} else if (m_current_shape == shape_t::triangle) {
				m_p_shape = std::make_unique<triangle>(wxRect{ point, point }, m_pen, m_brush);
			}
		}

		void on_mouse_left_up(ml5::mouse_event const& event) override {
			if (m_current_shape == shape_t::select) {
				if (m_move_shape != nullptr) {
					m_move_shape = nullptr;
				}
			}
			if (m_p_shape != nullptr) {
				m_p_shape->normalise_shape();
				m_shapes.add(std::move(m_p_shape));
			}
				
			m_p_shape = nullptr;
		}
	
		void on_mouse_move(ml5::mouse_event const& event) override {
			if (m_current_shape == shape_t::select) {
				if (m_move_shape != nullptr) {
					if (m_move_cooldown < COOLDOWN) {
						m_move_cooldown++;
					}
					else {
						m_move_cooldown = 0;

						wxPoint delta = event.get_position() - m_move_start;
						if ((*m_move_shape)->left_bound() + delta.x >= 0 && (*m_move_shape)->right_bound() + delta.x <= this->get_size().x &&
							(*m_move_shape)->top_bound() + delta.y >= 0 && (*m_move_shape)->bot_bound() + delta.y <= this->get_size().y)
							(*m_move_shape)->move(delta);

						m_move_start = event.get_position();
					}
				}
			} else {
				if (m_p_shape != nullptr)
					m_p_shape->set_bottom_right(event.get_position());
			}

			refresh();
		}

		void on_paint(ml5::paint_event const& event) override {
			//std::cout << "on_paint\n";

			for (auto &shape : m_shapes) {
				shape->draw(event.get_context());
			}

			for (auto &shape: m_sidebar) {
				shape->draw(event.get_context());
			}
			
			if (m_p_shape != nullptr)
				m_p_shape->draw(event.get_context());
		}

		void on_size(ml5::size_event const& event) override {
			init_sidebar();
		}

		void init_sidebar() {
			for (auto& shape : m_sidebar) {
				m_sidebar.remove(shape);
			}

			wxPen const default_pen{ wxColor{ "black" }, 5 };
			wxBrush const default_brush{ wxColor{ "black" } };
			
			wxPoint const bar{ std::max(int(this->get_size().x * 0.05), 50), this->get_size().y };
			auto temp = std::make_unique<line>(wxRect{ {bar.x, 0}, bar }, default_pen, default_brush);

			m_sidebar.add(std::move(temp));

			//select selector
			//scaling text with window size doesn't work :(
			wxPoint const select_tl{ 10, 10 };
			wxPoint select_br{ std::max(int(this->get_size().x * 0.05) - 10, 40), 0 };
			select_br.y = select_tl.y + (select_br.x - select_tl.x);

			std::unique_ptr<text> text_selector;
			if (m_current_shape == shape_t::select)
				text_selector = std::make_unique<text>(wxRect{ select_tl, select_br }, m_pen, m_brush, "Select");
			else
				text_selector = std::make_unique<text>(wxRect{ select_tl, select_br }, default_pen, default_brush, "Select");
			
			//line selector
			wxPoint const line_tl{10, text_selector->bot_bound() + 10};
			wxPoint line_br{ std::max(int(this->get_size().x * 0.05) - 10, 40), 0};
			line_br.y = line_tl.y + (line_br.x - line_tl.x);

			std::unique_ptr<line> line_selector;
			if (m_current_shape == shape_t::line)
				line_selector = std::make_unique<line>(wxRect{ line_tl, line_br }, m_pen, m_brush);
			else
				line_selector = std::make_unique<line>(wxRect{ line_tl, line_br }, default_pen, default_brush);
			
			//rectangle selector
			wxPoint const rect_tl{ 10, line_selector->bot_bound() + 10 };
			wxPoint rect_br{ std::max(int(this->get_size().x * 0.05) - 10, 40), 0 };
			rect_br.y = rect_tl.y + (rect_br.x - rect_tl.x);

			std::unique_ptr<rectangle> rect_selector;
			
			if (m_current_shape == shape_t::rectangle)
				rect_selector = std::make_unique<rectangle>(wxRect{ rect_tl, rect_br }, m_pen, m_brush);
			else
				rect_selector = std::make_unique<rectangle>(wxRect{ rect_tl, rect_br }, default_pen, default_brush);

			//ellipse selector
			wxPoint const ellipse_tl{ 10, rect_selector->bot_bound() + 10 };
			wxPoint ellipse_br{ std::max(int(this->get_size().x * 0.05) - 10, 40), 0 };
			ellipse_br.y = ellipse_tl.y + (ellipse_br.x - ellipse_tl.x);

			std::unique_ptr<ellipse> ellipse_selector;

			if (m_current_shape == shape_t::ellipse)
				ellipse_selector = std::make_unique<ellipse>(wxRect{ ellipse_tl, ellipse_br }, m_pen, m_brush);
			else
				ellipse_selector = std::make_unique<ellipse>(wxRect{ ellipse_tl, ellipse_br }, default_pen, default_brush);

			//triangle selector
			wxPoint const triangle_tl{ 10, ellipse_selector->bot_bound() + 10 };
			wxPoint triangle_br{ std::max(int(this->get_size().x * 0.05) - 10, 40), 0 };
			triangle_br.y = triangle_tl.y + (triangle_br.x - triangle_tl.x);

			std::unique_ptr<triangle> triangle_selector;
			if (m_current_shape == shape_t::triangle)
				triangle_selector = std::make_unique<triangle>(wxRect{ triangle_tl, triangle_br }, m_pen, m_brush);
			else
				triangle_selector = std::make_unique<triangle>(wxRect{ triangle_tl, triangle_br }, default_pen, default_brush);

			//add selectors
			m_sidebar.add(std::move(text_selector));
			m_sidebar.add(std::move(line_selector));
			m_sidebar.add(std::move(rect_selector));
			m_sidebar.add(std::move(ellipse_selector));
			m_sidebar.add(std::move(triangle_selector));
		}

		void change_shape(std::string const &menu_item) {
			if (menu_item == "Line") {
				m_current_shape = shape_t::line;
			} else if (menu_item == "Rectangle") {
				m_current_shape = shape_t::rectangle;
			} else if (menu_item == "Ellipse") {
				m_current_shape = shape_t::ellipse;
			} else if (menu_item == "Select") {
				m_current_shape = shape_t::select;
			} else if (menu_item == "Triangle") {
				m_current_shape = shape_t::triangle;
			}
			init_sidebar();
		}

		void change_width(std::string const &menu_item) {
			if (menu_item == "1px") {
				m_pen.SetWidth(1);
			} else if (menu_item == "2px") {
				m_pen.SetWidth(2);
			} else if (menu_item == "5px") {
				m_pen.SetWidth(5);
			} else if (menu_item == "10px") {
				m_pen.SetWidth(10);
			} else if (menu_item == "15px") {
				m_pen.SetWidth(15);
			} else if (menu_item == "20px") {
				m_pen.SetWidth(20);
			}

			init_sidebar();
		}

		void change_border_color(std::string const &menu_item) {
			if (menu_item == "Red") {
				m_pen.SetColour({ "red" });
			} else if (menu_item == "Green") {
				m_pen.SetColour({ "green" });
			} else if (menu_item == "Blue") {
				m_pen.SetColour({ "blue" });
			} else if (menu_item == "Yellow") {
				m_pen.SetColour({ "yellow" });
			} else if (menu_item == "Orange") {
				m_pen.SetColour({ "orange" });
			} else if (menu_item == "Purple") {
				m_pen.SetColour({ "purple" });
			} else if (menu_item == "Black") {
				m_pen.SetColour({ "black" });
			} else if (menu_item == "White") {
				m_pen.SetColour({ "white" });
			}

			init_sidebar();
		}

		void change_fill_color(std::string const &menu_item) {
			if (menu_item == "Red") {
				m_brush.SetColour({ "red" });
			} else if (menu_item == "Green") {
				m_brush.SetColour({ "green" });
			} else if (menu_item == "Blue") {
				m_brush.SetColour({ "blue" });
			} else if (menu_item == "Yellow") {
				m_brush.SetColour({ "yellow" });
			} else if (menu_item == "Orange") {
				m_brush.SetColour({ "orange" });
			} else if (menu_item == "Purple") {
				m_brush.SetColour({ "purple" });
			} else if (menu_item == "Black") {
				m_brush.SetColour({ "black" });
			} else if (menu_item == "White") {
				m_brush.SetColour({ "white" });
			}

			init_sidebar();
		}

		bool check_sidebar_collision(const wxPoint &point) {
			for (auto& shape : m_sidebar) {
				if (shape->is_colliding(point)) {
					if (shape->is_a("text")) {
						change_shape("Select");
						return true;
					} else if (shape->is_a("rectangle")) {
						change_shape("Rectangle");
						return true;
					} else if (shape->is_a("line")) {
						change_shape("Line");
						return true;
					} else if (shape->is_a("ellipse")) {
						change_shape("Ellipse");
						return true;
					} else if (shape->is_a("triangle")) {
						change_shape("Triangle");
						return true;
					}
				}
			}

			return false;
		}
	
		void check_shape_collision(const wxPoint &point) {			
			for (auto &shape : m_shapes) {
				if (shape->is_colliding(point)) {
					m_move_shape = &shape;
					m_move_cooldown = 0;
				}
			}
			if (m_move_shape != nullptr)
				m_move_start = point;
		}

	private:
		std::unique_ptr<shape>* m_move_shape{ nullptr };
		wxPoint m_move_start{ 0, 0 };
		int m_move_cooldown{ 0 };
	
		std::unique_ptr<shape> m_p_shape{ nullptr };
		ml5::vector<std::unique_ptr<shape>> m_shapes{};
		ml5::vector<std::unique_ptr<shape>> m_sidebar{};
		shape_t m_current_shape{ shape_t::select };

		wxBrush m_brush{ *wxBLUE_BRUSH };
		wxPen m_pen{ *wxRED_PEN };
};