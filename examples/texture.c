#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "window.h"


#define TEXTURE_WIDTH 100
#define TEXTURE_HEIGHT 100


GLuint texture;
GLint program;
GLint u_texture;


GLchar vertex_shader_src[] = R"(
	attribute vec4 position;
	attribute vec2 atexCoord;

	varying vec2 texCoord;

	void main() {
		gl_Position = position;
		texCoord = atexCoord;
	}
)";


GLchar fragment_shader_src[] = R"(
	precision mediump float;

	varying vec2 texCoord;
	uniform sampler2D tex;

	void main() {
		// gl_FragColor = texture2D(tex, texCoord);
		// gl_FragColor = vec4(texCoord.x, texCoord.y, 0.2, 1.0);
		gl_FragColor = vec4(0.2, 0.2, 0.2, 1.0);
	}
)";


void experiment_init(int width, int height) {
	unsigned char buffer[TEXTURE_WIDTH][TEXTURE_HEIGHT][3];
	float vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f
	};

	(void) buffer;


	program = program_load(vertex_shader_src, fragment_shader_src);


	glBindAttribLocation(program, 0, "position");
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), vertices);


// 	glBindAttribLocation(program, 1, "atexCoord");
// 	glEnableVertexAttribArray(1);
// 	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), vertices + 3);
// 
// 	glGenTextures(1, &texture);
// 	glBindTexture(GL_TEXTURE_2D, texture);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 
// 
// 	for (int row = 0; row < TEXTURE_WIDTH; ++row) {
// 		for (int col = 0; col < TEXTURE_HEIGHT; ++col) {
// 			const unsigned char x = 100;
// 
// 			buffer[row][col][0] = x;
// 			buffer[row][col][1] = x;
// 			buffer[row][col][2] = x;
// 		}
// 	}
// 
// 	glTexImage2D(
// 		  GL_TEXTURE_2D
// 		, 0
// 		, GL_RGB
// 		, TEXTURE_WIDTH
// 		, TEXTURE_HEIGHT
// 		, 0
// 		, GL_RGB
// 		, GL_UNSIGNED_BYTE
// 		, buffer
// 	);


	glViewport(0, 0, width, height);
}


void experiment_render() {
	glClear(GL_COLOR_BUFFER_BIT);

	// glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D, texture);
	// glUniform1i(glGetUniformLocation(program, "tex"), 0);

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
