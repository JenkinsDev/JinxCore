#include "shader.h"

namespace jinx { namespace graphics {

	using namespace jinx::utils;
	
	GLuint Shader::vertex_array_objects;
	GLuint Shader::vertex_buffer_objects;

	void Shader::init() {
		// Initialize our VAO
		glGenVertexArrays(1, &Shader::vertex_array_objects);
		glBindVertexArray(Shader::vertex_array_objects);

		// Initialize our VBO
		glGenBuffers(1, &Shader::vertex_buffer_objects);
		glBindBuffer(GL_ARRAY_BUFFER, Shader::vertex_buffer_objects);
	}

	GLint Shader::createShaderFromSource(GLuint shaderType, const GLchar shaderSource[]) {
		GLuint shader = glCreateShader(shaderType);

		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);

		if (!Shader::didShaderCompile(shader)) {
			char compileBuffer[512];
			glGetShaderInfoLog(shader, 512, NULL, compileBuffer);

			Logging::warning("Shader Failed To Compile.  Error:");
			Logging::warning(compileBuffer);

			return -1;
		}

		return shader;
	}

	/// Retrieves the source code from the supplied shader file and passes it to Shader::createShaderFromSource();
	///
	/// @param shaderType Describes what type of shader we are creating; Examples are: GL_VERTEX_SHADER,
	///                   GL_FRAGMENT_SHADER, etc.
	/// @param shaderFilePath Path to the shader file.
	///
	/// @return -1 if the shader failed to compile or an integer-based ID for the newly created, and stored,
	///         shader.
	GLint Shader::createShaderFromFile(GLuint shaderType, GLchar shaderFilePath[]) {
		return Shader::createShaderFromSource(shaderType, getFileContents(shaderFilePath).c_str());
	}

	GLint Shader::createProgramFromShaders(GLint shader) {
		// TODO: Implement
		return 1;
	}

	GLint Shader::createProgramFromShaders(GLint vertexShader, GLint fragmentShader) {
		// Link vertex and fragment shader into a single shader program.
		GLuint shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		glUseProgram(shaderProgram);

		return shaderProgram;
	}

	void Shader::drawTriangle(GLfloat vertices[], GLuint verticesLength) {
		Shader::drawVerticesOntoScreen(vertices, verticesLength);
	}

	void Shader::drawTriangle(GLfloat vertices[], GLuint verticesLength, GLfloat rgba[4]) {
		Shader::drawVerticesOntoScreen(vertices, verticesLength, rgba);
	}

	void Shader::drawTriangle(GLfloat vertices[], GLuint verticesLength, std::string texturePath) {
		Shader::drawVerticesOntoScreen(vertices, verticesLength, texturePath);
	}

	GLboolean Shader::didShaderCompile(GLuint shader) {
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		return status == GL_TRUE;
	}

	void Shader::drawVerticesOntoScreen(GLfloat vertices[], GLuint verticesLength) {
		glBufferData(GL_ARRAY_BUFFER, verticesLength, vertices, GL_STATIC_DRAW);
	}

	void Shader::drawVerticesOntoScreen(GLfloat vertices[], GLuint verticesLength, GLfloat rgba[4]) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}
	
	void Shader::drawVerticesOntoScreen(GLfloat vertices[], GLuint verticesLength, std::string texturePath) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}

} }