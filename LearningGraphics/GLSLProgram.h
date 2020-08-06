#pragma once
#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	// these strings are never going to change, so const to prevent them from being changed
	// use by reference, so that there isn't much copying going on
	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

	void linkShaders();

	void addAttribute(const std::string attributeName);

	void use();
	void unuse();

private:
	// id that refers to the entire program
	GLuint _programID;

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;

	int _numAttributes;

	void compileShader(const std::string& filePath, GLuint id);
};

