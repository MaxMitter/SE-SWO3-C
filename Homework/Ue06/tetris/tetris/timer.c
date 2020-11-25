#include <assert.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include "timer.h"

static double interval = 1.0;
static timer_func callback = NULL;
static bool timer_is_running = false;

static void reset_time(void);

void timer_start(double intvl, timer_func* on_tick) {
	assert(on_tick != NULL);
	assert(intvl > 0);
	
	interval = intvl;
	callback = on_tick;
	timer_is_running = true;

	reset_time();
}

void timer_fire(void) {
	if (!timer_is_running)
		return;

	if (glfwGetTime() >= interval) {
		callback();
		reset_time();
	}
}

void timer_stop(void) {
	timer_is_running = false;
}

static void reset_time(void) {
	glfwSetTime(0.0);
}