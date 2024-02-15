#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <GLFW/glfw3.h>
#include "window.h"


int main() {
	int width = 800;
	int height = 600;

	if (window_init("hints", width, height) != 0) {
		window_close();
		exit(EXIT_FAILURE);
	}

	window_set_callbacks();

	while (!window_should_close()) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window_swap_buffers();
		window_poll_events();
	}

	window_close();
	return 0;
}
