#include <stdio.h>
#include <stdlib.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "types.h"
#include "current_block.h"
#include "game_board.h"
#include "game_engine.h"
#include "timer.h"

#define WIDTH  400
#define HEIGHT ((WIDTH * GB_ROWS) / GB_COLS)
#define TIMER_INTERVAL 0.5


static void window_initialized(GLFWwindow *window);
static void render_window(void);


static void window_initialized(GLFWwindow *window) {

}

static void render_window(void) {

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
		glfwWaitEventsTimeout(TIMER_INTERVAL/5); //process all events of the application
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}
