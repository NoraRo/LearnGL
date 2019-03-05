#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>

namespace graphics
{
	GLuint
	gen_vao();

	void
	bind_buffer(GLuint vao, GLenum buffer_type,
				void* data, size_t size,
				int element_count,
				int stride,
				int offset_elements,
				GLenum data_type,
				bool normalized,
				int location);

	GLuint
	gen_shader(GLenum shader_type, const char* shader_content);

	GLuint
	gen_program(GLuint vert_shader, GLuint frag_shader);

	void
	set_uniform_bool(GLuint program_ID, const char* name, bool value);

	void
	set_uniform_int(GLuint program_ID, const char* name, int value);

	void
	set_uniform_float(GLuint program_ID, const char* name, float value);
}
