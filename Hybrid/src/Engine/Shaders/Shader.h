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

	bool compile();
	bool isCompiled();
	void deleteShader();
	std::string getError();
	GLuint getShaderId() { return m_id; };
private:
	std::string m_source;
	void updateSource(std::string updatedSource);
};

class ShaderProgram
{
	GLuint m_id;
	std::shared_ptr<Shader> m_vertex;
	std::shared_ptr<Shader> m_fragment;
public:
	ShaderProgram(std::string vertexSource, std::string fragmentSource);
	~ShaderProgram();

	void deleteProgram();
	void use();
	bool link();
	bool isLinked();
	std::string getError();
};

#endif