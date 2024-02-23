#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "shader.h"


GLint program;


GLchar vertex_shader_src[] = R"(
	attribute vec3 vposition;
	attribute vec3 vcolor;

	varying vec3 color;

	void main() {
		gl_Position = vec4(vposition, 1.0);
		color = vcolor;
	}
)";


GLchar fragment_shader_src[] = R"(
	precision mediump float;
	varying vec3 color;

	void main() {
		gl_FragColor = vec4(color, 1.0);
	}
)";


void experiment_init(int width, int height) {
	static const float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	static const float colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};


	program = program_load(vertex_shader_src, fragment_shader_src);

	GLint position_location = glGetAttribLocation(program, "vposition");
	GLint color_location    = glGetAttribLocation(program, "vcolor");

	glVertexAttribPointer(position_location, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(position_location);
	glVertexAttribPointer(color_location, 3, GL_FLOAT, GL_FALSE, 0, colors);
	glEnableVertexAttribArray(color_location);


	glViewport(0, 0, width, height);
}


void experiment_render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


void experiment_resize(int width, int height) {
	glViewport(0, 0, width, height);
}


int main(int argc, char *argv[]) {
	const int width  = 800;
	const int height = 600;

	if (window_init("hints", width, height) != 0) {
		window_close();
		exit(EXIT_FAILURE);
	}

	experiment_init(width, height);
	window_set_callbacks();

	while (!window_should_close()) {
		experiment_render();

		window_swap_buffers();
		window_poll_events();
	}

	window_close();
	return 0;
}
