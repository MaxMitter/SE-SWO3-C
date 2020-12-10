#include <stdio.h>
#include <stdlib.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "types.h"
#include "block.h"
#include "game_board.h"
#include "game_engine.h"
#include "timer.h"
#include "figures.h"

#define WIDTH  400
#define HEIGHT ((WIDTH * GB_ROWS) / GB_COLS)
#define INITIAL_TIMER_INTERVAL 0.5

static double timer_interval;
static bool is_paused = false;

static void window_initialized(GLFWwindow *window);
static void render_window(void);
static void on_key(GLFWwindow* window, int key, int scancode, int action, int mods);
static void on_tick(void);


static void window_initialized(GLFWwindow *window) {
	glfwSetKeyCallback(window, on_key);
	gb_init_game_board();
	fg_new_figure();
	timer_interval = INITIAL_TIMER_INTERVAL;
	gb_set_interval(INITIAL_TIMER_INTERVAL);
	is_paused = false;
	timer_start(timer_interval, on_tick);
}

static void render_window(void) {
	timer_fire();
	gb_render();
	fg_render();
}

static void on_tick(void) {
	on_key(NULL, GLFW_KEY_DOWN, 0, GLFW_PRESS, 0);
}

void on_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	int dx = 0;
	int dy = 0;
	int turn = 0;
	switch (key) {
	case GLFW_KEY_DOWN:
		dy = -1;
		break;
	case GLFW_KEY_LEFT:
		dx = -1;
		break;
	case GLFW_KEY_RIGHT:
		dx = 1;
		break;
	case GLFW_KEY_UP:
		turn = 1;
		break;
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_P) {
			if (is_paused) {
				timer_start(timer_interval, on_tick);
				printf("Game resumed.\n");
			}
			else {
				timer_stop();
				printf("Game paused.\n");
			}
			is_paused = !is_paused;
		}
		else if (key == GLFW_KEY_R) {
			timer_stop();
			int score = gb_get_score();
			printf("Congratulations, you managed to clear %d rows! Final speed: %1.2f s/tick\n", score, timer_interval);
			printf("Game restarting...\n");
			ge_restart();
			window_initialized(window);
		}
		else {
			if (!is_paused) {
				if (!ge_handle_move(dx, dy, turn)) {
					timer_stop();
					int score = gb_get_score();
					is_paused = true;
					printf("Congratulations, you managed to clear %d rows! Final speed: %1.2f s/tick\n", score, timer_interval);
				}
				else {
					double new_interval = gb_get_interval();

					if (new_interval < timer_interval) {
						timer_interval = new_interval;
						timer_stop();
						timer_start(timer_interval, on_tick);
					}
				}
			}
		}
	}
}

int main() {
	if(!glfwInit()) {
		fprintf(stderr, "could not initialize GLFW\n");
		return EXIT_FAILURE;
	}

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Tetris", NULL, NULL);
	if(!window) {
		glfwTerminate();
		fprintf(stderr, "could not open window\n");
		return EXIT_FAILURE;
	}

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetWindowAspectRatio(window, width, height); //enforce correct aspect ratio
	glfwMakeContextCurrent(window);

	window_initialized(window);

	while(!glfwWindowShouldClose(window)) {
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT); //clear frame buffer
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, width, 0, height); //orthogonal projection - origin is in lower-left corner
		glScalef((float)width / (float)GB_COLS, (float)height / (float)GB_ROWS, 1); //scale logical pixel to screen pixels

		render_window();

		const GLenum error = glGetError();
		if(error != GL_NO_ERROR) fprintf(stderr, "ERROR: %s\n", gluErrorString(error));

		glfwSwapBuffers(window);//push image to display
		// glfwPollEvents();
		glfwWaitEventsTimeout(timer_interval/5); //process all events of the application
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}
