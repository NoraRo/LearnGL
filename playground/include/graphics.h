#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>

namespace graphics
{
	GLuint
	gen_vao();

	void
	bind_buffer(GLuint vbo,
				void* data, size_t size,
				int element_count,
				GLenum data_type,
				bool normalized,
				int location);

	GLuint
	gen_shader(GLenum shader_type, const char* shader_content);

	GLuint
	gen_program(GLuint vert_shader, GLuint frag_shader);
}
