#include <stdio.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <GLFW/glfw3.h>


void log_on_error(int error, const char *description) {
	fprintf(stderr, "GLFW error (code %d): %s\n", error, description);
}


void error_callback(int error, const char* description) {
	fprintf(stderr, "GLFW Error: %s\n", description);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}


void resize_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


#define DEFAULT_WINDOW_HINTS_COUNT 36
const int default_window_hints[DEFAULT_WINDOW_HINTS_COUNT][2] = {
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
	{GLFW_CONTEXT_VERSION_MINOR	, 0				},
	{GLFW_CONTEXT_ROBUSTNESS	, GLFW_NO_ROBUSTNESS		},
	{GLFW_CONTEXT_RELEASE_BEHAVIOR	, GLFW_ANY_RELEASE_BEHAVIOR	},
	{GLFW_OPENGL_FORWARD_COMPAT	, GLFW_FALSE			},
	{GLFW_OPENGL_DEBUG_CONTEXT	, GLFW_FALSE			},
	{GLFW_OPENGL_PROFILE		, GLFW_OPENGL_ANY_PROFILE	}
};


int main() {
	GLFWwindow *window = NULL;
	const int width  = 800;
	const int height = 600;

	// the initialization for any glfw application
	glfwInit();

	// if any glfw error occurs we can catch it with this callback
	glfwSetErrorCallback(log_on_error);

	// giving hints about window creation, the names are self-explanatory
	for (int i = 0; i < DEFAULT_WINDOW_HINTS_COUNT; ++i) {
		glfwWindowHint(default_window_hints[i][0], default_window_hints[i][1]);
	}

	// if any errors occur, it's probably the window hints
	window = glfwCreateWindow(width, height, "hello", NULL, NULL);

	if (window == NULL) {
		glfwTerminate();
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, resize_callback);
	glfwSetKeyCallback(window, key_callback);


	glfwMakeContextCurrent(window);


	glViewport(0, 0, width, height);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
