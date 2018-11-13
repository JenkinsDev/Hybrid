#ifndef __JINX_SHADER_H_
#define __JINX_SHADER_H_

#include <vector>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
	GLuint m_id;
	GLenum m_type;
public:
	Shader(std::string shaderSource, GLenum shaderType);
	~Shader();

	bool compile();
	bool isCompiled();
	std::string getError();
	GLuint getShaderId() { return m_id; };
protected:
	std::string m_source;
	void updateSource(std::string updatedSource);
	void deleteShader();
};

class ShaderProgram
{
	GLuint m_id;
	Shader* m_vertex;
	Shader* m_fragment;
public:
	ShaderProgram(Shader* vertexShader, Shader* fragmentShader);
	~ShaderProgram();

	void use();
	bool link();
	bool isLinked();
	std::string getError();
};

#endif