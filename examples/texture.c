#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "window.h"
#include <string.h>


#define TEXTURE_WIDTH  100
#define TEXTURE_HEIGHT 100


GLuint texture;
GLint program;


const float vertices[] = {
	-1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f
};


const float texture_vertices[] = {
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
};


unsigned char texture_buffer[TEXTURE_WIDTH][TEXTURE_HEIGHT][3];


GLchar vertex_shader_src[] = R"(
	attribute vec3 position;
	attribute vec2 atexCoord;

	varying vec2 texCoord;

	void main() {
		gl_Position = vec4(position, 1.0);
		texCoord = atexCoord;
	}
)";


GLchar fragment_shader_src[] = R"(
	precision mediump float;

	varying vec2 texCoord;
	uniform sampler2D tex;

	void main() {
		gl_FragColor = texture2D(tex, texCoord);
	}
)";


void experiment_init(int width, int height) {
	program = program_load(vertex_shader_src, fragment_shader_src);

	glBindAttribLocation(program, 0, "position");
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);

	glBindAttribLocation(program, 1, "atexCoord");
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, texture_vertices);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// texture generation
	for (int i = 0; i < TEXTURE_HEIGHT; ++i) {
		for (int j = 0; j < TEXTURE_WIDTH; ++j) {
			const char p = (char) (rand() % 256);

			texture_buffer[i][j][0] = p;
			texture_buffer[i][j][1] = p;
			texture_buffer[i][j][2] = p;
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);


	glViewport(0, 0, width, height);
}


void experiment_render() {
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


void experiment_resize(int width, int height) {
	glViewport(0, 0, width, height);
}


int main(int argc, char *argv[]) {
	const int width  = 800;
	const int height = 600;

	if (window_init("textures", width, height) != 0) {
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
