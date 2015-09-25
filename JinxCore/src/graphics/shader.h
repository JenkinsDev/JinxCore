#ifndef __JINX_GRAPHICS_SHADER_H
#define __JINX_GRAPHICS_SHADER_H

#include <iostream>
#include <GL\glew.h>
#include "../utils/logging.h"
#include "../utils/io.h"


namespace jinx { namespace graphics {

	class Shader
	{
	private:
		static GLuint vertex_array_objects;
		static GLuint vertex_buffer_objects;
	public:
		static void init();
		static GLint createShaderFromSource(GLuint shaderType, const GLchar shaderSource[]);
		static GLint createShaderFromFile(GLuint shaderType, GLchar shaderSource[]);
		static GLint Shader::createProgramFromShaders(GLint shader);
		static GLint Shader::createProgramFromShaders(GLint vertexShader, GLint fragmentShader);
		static void drawTriangle(GLfloat vertices[], GLuint verticesLength);
		static void drawTriangle(GLfloat vertices[], GLuint verticesLength, GLfloat rbga[4]);
		static void drawTriangle(GLfloat vertices[], GLuint verticesLength, std::string texturePath);
	private:
		static GLboolean didShaderCompile(GLuint shader);
		static void drawVerticesOntoScreen(GLfloat vertices[], GLuint verticesLength);
		static void drawVerticesOntoScreen(GLfloat vertices[], GLuint verticesLength, GLfloat rgba[4]);
		static void drawVerticesOntoScreen(GLfloat vertices[], GLuint verticesLength, std::string texturePath);
	};

} }

#endif