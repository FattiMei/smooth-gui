#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


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


int main() {
	const int width  = 800;
	const int height = 600;

	glfwInit();

	// find the possible window hints at www.glfw.org/docs/latest/window.html
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);

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


	glfwSetErrorCallback(error_callback);
	glfwSetFramebufferSizeCallback(window, resize_callback);
	glfwSetKeyCallback(window, key_callback);


	glfwMakeContextCurrent(window);

	if (!gladLoadGLES2Loader((GLADloadproc) glfwGetProcAddress)) {
		fprintf(stderr, "Failed to initialize GLAD\n");
		glfwTerminate();
		return -1;
	}

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
