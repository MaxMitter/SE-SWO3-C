#pragma once
#include <ml5/ml5.h>
#include <cstdlib>
#include "player.h"
#include "asteroid.h"
#include "text.h"

constexpr int TICK_INTERVAL = 10;
constexpr double TURN_ANGLE = 45.0;
constexpr int ASTEROID_SPAWN_COOLDOWN = 600;
constexpr int MAX_ASTEROID_SIZE = 7;
constexpr int BASE_SCORE_INC = 10;

class ast_window : public ml5::window, MI5_DERIVE(ast_window, ml5::window) {
	MI5_INJECT(ast_window)
		using context_t = ml5::paint_event::context_t;
	
	public:
		void on_init() override {
			this->get_frame().SetSize(1280, 720);
			std::cout << "on_init" << std::endl;
			set_prop_background_brush(*wxBLACK_BRUSH);

			add_menu("Game Controls", {
				{"Restart", "Restart the game"},
			});
			
			init_game();
			
			start_timer(std::chrono::milliseconds{ TICK_INTERVAL });
		}

		void on_menu(ml5::menu_event const& event) override {
			if (event.get_title_and_item() == "Game Controls/Restart") {
				stop_timer();
				init_game();
				start_timer(std::chrono::milliseconds{ TICK_INTERVAL });
			}
		}

		void on_size(ml5::size_event const& event) override {
			if (m_player != nullptr) {
				m_player->set_context_size(this->get_frame().GetSize());
			}

			for (auto& ast : m_asteroids) {
				ast->set_context_size(this->get_frame().GetSize());
			}

			for (auto& bul : m_bullets) {
				bul->set_context_size(this->get_frame().GetSize());
			}
		}

		void init_game() {

			m_score = 0;
			m_asteroid_cooldown_tick = ASTEROID_SPAWN_COOLDOWN;
			
			if (m_player == nullptr) {
				m_player = std::make_unique<player>(wxPoint{ get_width() / 2, get_height() / 2 });
				m_player->set_context_size(this->get_frame().GetSize());
			} else {
				m_player->set_position(wxPoint{ get_width() / 2, get_height() / 2 });
				m_player->set_speed(0.0);
				m_player->revive();
			}

			if (m_end_screen == nullptr) {
				m_end_screen = std::make_unique<image>(get_size() / 2, *wxTRANSPARENT_PEN, *wxTRANSPARENT_BRUSH,
				"C:\\Users\\maxmi\\Documents\\FH\\SWO\\c-code\\Class\\U12\\minilib\\asteroids\\src\\img\\game_over.png", 0.0);
				m_end_screen->center_in_context(get_size());
			}

			m_bullets.clear();
			m_asteroids.clear();
			
			m_scoreboard = std::make_unique<text>(wxRect{ 0, 0, 200, 50 }, "");
			update_scoreboard();
		}

		void update_scoreboard() {
			m_scoreboard->set_text("Current Score: " + std::to_string(m_score));
		}

		void on_mouse_left_down(ml5::mouse_event const& event) override {
			if (m_player->within_spawn_protection(event.get_position())) {
				std::cout << "Too close to player!" << std::endl;
			}
		}

		void on_key(ml5::key_event const& event) override {
			//std::cout << "Key: " << event.get_key_code() << std::endl;
			switch(event.get_key_code()) {
				// W
				case 87:
				case 119:
					m_player->set_speed(std::min(m_player->get_speed() + 0.5, 10.0));
					break;
				// S
				case 115:
					m_player->set_speed(std::max(m_player->get_speed() - 0.5, 0.0));
					break;
				// A
				case 97:
					m_player->rotate_angle(TURN_ANGLE);
					break;
				// D
				case 100:
					m_player->rotate_angle((-TURN_ANGLE));
					break;
				// SPACE
				case 32:
					m_bullets.push_back(m_player->shoot());
					break;
				case 102:
					move_board();
					break;
				default:
					break;
			}
		}
	
		void on_paint(ml5::paint_event const& event) override {
			
			context_t& context = event.get_context();

			//std::cout << "Items alive: " << m_asteroids.size() + m_bullets.size() + 1 << std::endl;
			
			if (m_player->is_alive()) {
				m_player->set_context_size(context.GetSize());
				m_player->draw(context);

				for (auto it = m_asteroids.begin(); it != m_asteroids.end();) {
					if (!it->get()->is_alive()) {
						it = m_asteroids.erase(it);
					}
					else {
						it->get()->set_context_size(context);
						it->get()->draw(context);
						++it;
					}
				}

				for (auto it = m_bullets.begin(); it != m_bullets.end();) {
					if (!it->get()->is_alive()) {
						it = m_bullets.erase(it);
					}
					else {
						it->get()->draw(context);
						++it;
					}
				}
			} else {
				m_end_screen->draw(context);
			}
			m_scoreboard->draw(context);
			
		}

		void move_board() {
			m_player->move();

			for (auto& asteroid : m_asteroids) {
				if (!asteroid->move()) {
					asteroid->kill();
				} else {
					if (shapes_collide(asteroid, m_player)) {
						m_player->kill();
					}
				}
			}

			for (auto& bullet : m_bullets) {
				if (!bullet->move()) {
					bullet->kill();
				}
				
				for (auto& asteroid : m_asteroids) {
					if (shapes_collide(bullet, asteroid)) {
						asteroid->kill();
						bullet->kill();
						m_score += BASE_SCORE_INC * (MAX_ASTEROID_SIZE - asteroid->get_level());
						update_scoreboard();
						break;
					}
				}

				explode_asteroid();
			}

			refresh();
		}
	
		void on_timer(ml5::timer_event const& event) override {
			if (m_asteroid_cooldown_tick > ASTEROID_SPAWN_COOLDOWN) {
				spawn_asteroid();
				m_asteroid_cooldown_tick = 0;
			} else {
				++m_asteroid_cooldown_tick;
			}

			if (m_player->is_alive()) {
				move_board();
			} else {
				stop_timer();
			}
		}

		void spawn_asteroid() {
			std::cout << "Spawning asteroid..." << std::endl;
			std::random_device seeder;
			std::mt19937 generator(seeder());
			std::uniform_int_distribution<int> distrx(0, this->get_size().GetX());
			std::uniform_int_distribution<int> distry(0, this->get_size().GetY());
			std::uniform_int_distribution<int> level(2, MAX_ASTEROID_SIZE);
			
			auto temp = std::make_unique<asteroid>(wxPoint{ distrx(generator), distry(generator) }, level(generator));
			m_asteroids.push_back(std::move(temp));
		}
	
		void explode_asteroid() {
			for (auto& asteroid : m_asteroids) {
				if (!asteroid->is_alive()) {
					explode_asteroid(asteroid);
					break;
				}
			}
		}

		void explode_asteroid(std::unique_ptr<gb_object>& ast) {
			
			if (ast->get_level() > 2) {
				std::random_device seeder;
				std::mt19937 generator(seeder());
				std::uniform_int_distribution<int> distr(0, 360);
				
				auto temp1 = std::make_unique<asteroid>(ast->get_position(), ast->get_level() - 1, distr(generator) % 120);
				auto temp2 = std::make_unique<asteroid>(ast->get_position(), ast->get_level() - 1, distr(generator) % 120 + 120);
				auto temp3 = std::make_unique<asteroid>(ast->get_position(), ast->get_level() - 1, distr(generator) % 120 + 240);

				m_asteroids.push_back(std::move(temp1));
				m_asteroids.push_back(std::move(temp2));
				m_asteroids.push_back(std::move(temp3));
			}
		}

		bool shapes_collide (std::unique_ptr<gb_object>& a, std::unique_ptr<gb_object>& b) {
			return (a->left() < b->right() && a->right() > b->left() &&
				a->top() < b->bot() && a->bot() > b->top());
		}

	private:

		std::unique_ptr<gb_object> m_player{ nullptr };
		std::unique_ptr<text> m_scoreboard{ nullptr };
		std::unique_ptr<image> m_end_screen{ nullptr };
	
		std::vector<std::unique_ptr<gb_object>> m_asteroids{};
		std::vector<std::unique_ptr<gb_object>> m_bullets{};
	
		int m_score{ 0 };
		int m_asteroid_cooldown_tick{ ASTEROID_SPAWN_COOLDOWN };
};