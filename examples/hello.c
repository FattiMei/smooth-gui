#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void resize_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


int main() {
	const int width  = 800;
	const int height = 600;


	glfwInit();

	// @TODO: look at all the possible hints
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);

	// @TODO: find documentation for all glfw functions
	GLFWwindow* window = glfwCreateWindow(
		  width
		, height
		, "hello"
		, NULL
		, NULL
	);

	if (window == NULL) {
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLES2Loader((GLADloadproc) glfwGetProcAddress)) {
		fprintf(stderr, "Failed to initialize GLAD\n");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, resize_callback);
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
