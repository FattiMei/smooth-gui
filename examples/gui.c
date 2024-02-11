#include <stdio.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "slider.h"


#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600


int window_width = DEFAULT_WINDOW_WIDTH;
int window_height = DEFAULT_WINDOW_HEIGHT;


#define SLIDER_MARGIN 5
#define SLIDER_HEIGHT 20


struct Slider sliders[] = {
	{SLIDER_MARGIN, SLIDER_MARGIN, DEFAULT_WINDOW_WIDTH - 2 * SLIDER_MARGIN, SLIDER_HEIGHT},
	{SLIDER_MARGIN, SLIDER_MARGIN * 2 + SLIDER_HEIGHT, DEFAULT_WINDOW_WIDTH - 2 * SLIDER_MARGIN, SLIDER_HEIGHT},
	{SLIDER_MARGIN, SLIDER_MARGIN * 3 + 2 * SLIDER_HEIGHT, DEFAULT_WINDOW_WIDTH - 2 * SLIDER_MARGIN, SLIDER_HEIGHT}
};


void error_callback(int error, const char* description) {
	fprintf(stderr, "GLFW Error: %s\n", description);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}


void resize_callback(GLFWwindow *window, int width, int height) {
	window_width = width;
	window_height = height;


	for (int i = 0; i < 3; ++i) {
		sliders[i].w = width - 2 * SLIDER_MARGIN;
	}


	glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow *window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			// point-rect collision
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);


			// mouse coordinate system is different than viewport coordinate system
			ypos = window_height - ypos;


			for (int i = 0; i < 3; ++i) {
				if (
						(xpos >= sliders[i].x)
						&& (xpos <= sliders[i].x + sliders[i].w)
						&& (ypos >= sliders[i].y)
						&& (ypos <= sliders[i].y + sliders[i].h)) {

					slider_update(&sliders[i], xpos);
					slider_render(&sliders[i]);

					sliders[i].focused = true;
					break;
				}
			}
		}
		else if (action == GLFW_RELEASE) {
			for (int i = 0; i < 3; ++i) {
				sliders[i].focused = false;
			}
		}
	}
}


int main(int argc, char *argv[]) {
	const GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
	};

	glfwInit();

	// find the possible window hints at www.glfw.org/docs/latest/window.html
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);

	GLFWwindow* window = glfwCreateWindow(
		  window_width
		, window_height
		, "slider example"
		, NULL
		, NULL
	);

	if (window == NULL) {
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	glfwSetErrorCallback(error_callback);
	glfwSetFramebufferSizeCallback(window, resize_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);

	glfwMakeContextCurrent(window);

	glViewport(0, 0, window_width, window_height);
	glfwSwapInterval(1);


	slider_init();


	double xpos, ypos;


	while (!glfwWindowShouldClose(window)) {
		glClearColor(sliders[0].state, sliders[1].state, sliders[2].state, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (int i = 0; i < 3; ++i) {
			if (sliders[i].focused) {
				glfwGetCursorPos(window, &xpos, &ypos);
				slider_update(&sliders[i], xpos);
			}

			slider_render(&sliders[i]);
		}


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
