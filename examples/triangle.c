#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"


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


int main(int argc, char *argv[]) {
	const int width  = 800;
	const int height = 600;

	float vertices[] =  {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

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


	GLint vertex_shader   = shader_load_from_file(GL_VERTEX_SHADER, argv[1]);
	GLint fragment_shader = shader_load_from_file(GL_FRAGMENT_SHADER, argv[2]);
	GLint program         = program_load(vertex_shader, fragment_shader);


	glBindAttribLocation(program, 0, "vPosition");


	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}
