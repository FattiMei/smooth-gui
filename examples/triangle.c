#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "shader.h"


GLint program;


GLchar vertex_shader_src[] = R"(
	attribute vec4 position;

	void main() {
		gl_Position = position;
	}
)";


GLchar fragment_shader_src[] = R"(
	precision mediump float;
	uniform float time;

	void main() {
		vec3 color = vec3(0.2, 0.5, 0.7);
		float m = (1.0 + sin(time)) / 2.0;

		gl_FragColor = vec4(m * color, 1.0);
	}
)";


void experiment_init(int width, int height) {
	static const float vertices[] =  {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glViewport(0, 0, width, height);

	GLint vertex_shader   = shader_load(GL_VERTEX_SHADER, vertex_shader_src, NULL);
	GLint fragment_shader = shader_load(GL_FRAGMENT_SHADER, fragment_shader_src, NULL);
	program               = program_load(vertex_shader, fragment_shader);

	glBindAttribLocation(program, 0, "position");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);
}


void experiment_render() {
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
