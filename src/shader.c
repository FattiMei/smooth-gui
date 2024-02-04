#include "shader.h"
#include <stdio.h>


#define MAX_LOG_LENGTH 1024
static char log[MAX_LOG_LENGTH];


GLint shader_load(
	  GLenum type
	, const GLchar* const *string
	, const GLint *length
) {
	GLuint shader = glCreateShader(type);
	GLint compiled;

	if (shader == 0) {
		fprintf(stderr, "Could not create shader\n");
		return -1;
	}

	glShaderSource(shader, 1, string, length);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {
		fprintf(stderr, "Compile error:\n");

		GLint info_len = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);

		if (info_len < MAX_LOG_LENGTH) {
			glGetShaderInfoLog(shader, info_len, NULL, log);

			fprintf(stderr, "%s\n", log);
			glDeleteShader(shader);
		}
	}

	return shader;
}


GLint shader_load_from_file(GLenum type, const char *filename) {
	GLuint shader;
	FILE *fp = fopen(filename, "r");

	if (fp == NULL) {
		fprintf(stderr, "Error when opening file %s\n", filename);
		return -1;
	}

	{
		long numbytes = 0;
		char *buffer = NULL;

		// hack for finding the dimension of a file
		fseek(fp, 0L, SEEK_END);
		numbytes = ftell(fp);
		fseek(fp, 0L, SEEK_SET);

		buffer = (char *) malloc(numbytes);
		fread(buffer, sizeof(char), numbytes, fp);

		shader = shader_load(type, buffer, &numbytes);

		free(buffer);
		fclose(fp);
	}

	return shader;
}
