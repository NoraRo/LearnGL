#include "graphics.h"

#include <iostream>

namespace graphics
{
	using namespace std;

	int
	get_vertex_size(GLenum type)
	{
		switch(type)
		{
			case GL_FLOAT:
				return sizeof(float);

			case GL_INT:
				return sizeof(int);

			case GL_BYTE:
				return sizeof(byte);

			case GL_UNSIGNED_INT:
				return sizeof(unsigned int);
			default:
				cout<<"get_vertex_size, Unknown type\n";
				return 0;
		}
	}

	GLuint
	gen_vao()
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);
		return vao;
	}

	void
	bind_buffer(GLuint vao, GLenum buffer_type,
				void* data, size_t size,
				int element_count,
				int stride,
				int offset_elements,
				GLenum data_type,
				bool normalized,
				int location)
	{
		
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);
		//Bind
		glBindBuffer(buffer_type, vbo);
		glBufferData(buffer_type, size, data, GL_STATIC_DRAW);

		if(buffer_type == GL_ARRAY_BUFFER)
		{
			GLenum normlize = normalized? GL_TRUE : GL_FALSE;
			int stride_offset = stride * get_vertex_size(data_type);
			int offset = offset_elements * get_vertex_size(data_type);
			glVertexAttribPointer(location, element_count, data_type, normlize,
								  stride_offset, (void*)offset);
			glEnableVertexAttribArray(location);
		}
		//unbind
		//Order differ take care!
		glBindVertexArray(0);
		glBindBuffer(buffer_type, 0);
	}

	GLuint
	gen_shader(GLenum shader_type, const char* shader_content)
	{
		GLuint shader = glCreateShader(shader_type);
		glShaderSource(shader, 1, &shader_content, NULL);
		glCompileShader(shader);

		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if(!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			cout<< "Shader Compilation failed\n"<< infoLog << std::endl;
		}
		return shader;
	}

	GLuint
	gen_program(GLuint vert_shader, GLuint frag_shader)
	{
		GLuint prog = glCreateProgram();
		glAttachShader(prog, vert_shader);
		glAttachShader(prog, frag_shader);
		glLinkProgram(prog);

		int success;
		char infoLog[512];

		glGetProgramiv(prog, GL_LINK_STATUS, &success);
		if(!success)
		{
			glGetProgramInfoLog(prog, 512, NULL, infoLog);
			cout<< "Program Linker failed\n"<< infoLog << std::endl;
		}

		glUseProgram(prog);

		glDeleteShader(vert_shader);
		glDeleteShader(frag_shader);

		return prog;
	}

	void
	set_uniform_bool(GLuint program_ID, const char* name, bool value)
	{
		glUniform1i(glGetUniformLocation(program_ID, name), (int)value);
	}

	void
	set_uniform_int(GLuint program_ID, const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(program_ID, name), value);
	}

	void
	set_uniform_float(GLuint program_ID, const char* name, float value)
	{
		glUniform1i(glGetUniformLocation(program_ID, name), value);
	}


}
