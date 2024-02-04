#ifndef __SHADER_H__
#define __SHADER_H__


#include <glad/glad.h>
#include <GLFW/glfw3.h>


GLint shader_load(
	  GLenum type
	, const GLchar* string
	, const GLint *length
);


GLint shader_load_from_file(GLenum type, const char *filename);

GLint program_load(GLint vertex_shader, GLint fragment_shader);

#endif
