#include "window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <assert.h>


struct WindowHint {
	int name;
	int value;
};


static const struct WindowHint default_window_hints[] = {
	{GLFW_RESIZABLE			, GLFW_TRUE			},
	{GLFW_VISIBLE			, GLFW_TRUE			},
	{GLFW_DECORATED			, GLFW_TRUE			},
	{GLFW_FOCUSED			, GLFW_TRUE			},
	{GLFW_AUTO_ICONIFY		, GLFW_TRUE			},
	{GLFW_FLOATING			, GLFW_FALSE			},
	{GLFW_MAXIMIZED			, GLFW_FALSE			},
	{GLFW_CENTER_CURSOR		, GLFW_TRUE			},
	{GLFW_TRANSPARENT_FRAMEBUFFER	, GLFW_FALSE			},
	{GLFW_FOCUS_ON_SHOW		, GLFW_TRUE			},
	{GLFW_SCALE_TO_MONITOR		, GLFW_FALSE			},
	{GLFW_RED_BITS			, 8				},
	{GLFW_GREEN_BITS		, 8				},
	{GLFW_BLUE_BITS			, 8				},
	{GLFW_ALPHA_BITS		, 8				},
	{GLFW_DEPTH_BITS		, 24				},
	{GLFW_STENCIL_BITS		, 8				},
	{GLFW_ACCUM_RED_BITS		, 0				},
	{GLFW_ACCUM_GREEN_BITS		, 0				},
	{GLFW_ACCUM_BLUE_BITS		, 0				},
	{GLFW_ACCUM_ALPHA_BITS		, 0				},
	{GLFW_AUX_BUFFERS		, 0				},
	{GLFW_SAMPLES			, 0				},
	{GLFW_REFRESH_RATE		, GLFW_DONT_CARE		},
	{GLFW_STEREO			, GLFW_FALSE			},
	{GLFW_SRGB_CAPABLE		, GLFW_FALSE			},
	{GLFW_DOUBLEBUFFER		, GLFW_TRUE			},
	{GLFW_CLIENT_API		, GLFW_OPENGL_ES_API		},
	{GLFW_CONTEXT_CREATION_API	, GLFW_EGL_CONTEXT_API		},
	{GLFW_CONTEXT_VERSION_MAJOR	, 2				},
	{GLFW_CONTEXT_VERSION_MINOR	, 2				},
	{GLFW_CONTEXT_ROBUSTNESS	, GLFW_NO_ROBUSTNESS		},
	{GLFW_CONTEXT_RELEASE_BEHAVIOR	, GLFW_ANY_RELEASE_BEHAVIOR	},
	{GLFW_OPENGL_FORWARD_COMPAT	, GLFW_FALSE			},
	{GLFW_OPENGL_DEBUG_CONTEXT	, GLFW_FALSE			},
	{GLFW_OPENGL_PROFILE		, GLFW_OPENGL_ANY_PROFILE	}
};


static GLFWwindow *window = NULL;


static void error_callback(int error, const char* description) {
	fprintf(stderr, "GLFW error (code %d): %s\n", error, description);
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	printf("key %d (scancode %d) ", key, scancode);

	switch (action) {
		case GLFW_PRESS  : printf("pressed\n") ; break;
		case GLFW_REPEAT : printf("repeated\n"); break;
		case GLFW_RELEASE: printf("released\n"); break;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}


static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
	switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT  : printf("mouse button left ") ; break;
		case GLFW_MOUSE_BUTTON_RIGHT : printf("mouse button right "); break;
	}

	switch (action) {
		case GLFW_PRESS  : printf("pressed\n") ; break;
		case GLFW_RELEASE: printf("released\n"); break;
	}
}


static void resize_callback(GLFWwindow *window, int width, int height) {
	printf("window resized to (%d, %d)\n", width, height);

	glViewport(0, 0, width, height);
}


int window_init(const char *title, int width, int height) {
	glfwInit();

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (window == NULL) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	return 0;
}


int window_init_with_hints(const char *title, int width, int height) {
	assert(0 && "not yet implemented");
}


void window_set_callbacks() {
	glfwSetKeyCallback            (window, key_callback);
	glfwSetMouseButtonCallback    (window, mouse_button_callback);
	glfwSetFramebufferSizeCallback(window, resize_callback);
}


int window_should_close() {
	return glfwWindowShouldClose(window);
}


void window_swap_buffers() {
	glfwSwapBuffers(window);
}


void window_poll_events() {
	glfwPollEvents();
}


void window_close() {
	glfwTerminate();
}
