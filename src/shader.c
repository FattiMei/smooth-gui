#include "shader.h"


#define MAX_LOG_LENGTH 1024
static char log[MAX_LOG_LENGTH];


struct Shader shader_create(GLenum type) {
	return (struct Shader) {
		  glCreateShader(type)
		, type
	};
}


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

	glShaderSource(S->id, 1, string, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {
		fprintf(stderr, "Compile error:\n");

		GLint info_len = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);

		if (info_len < ) {
			glGetShaderInfoLog(shader, info_len, NULL, log);

			fprintf(stderr, "%s\n", log);
			glDeleteShader(shader);
		}
	}

	return shader;
}
