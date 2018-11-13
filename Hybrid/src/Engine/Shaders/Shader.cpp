#include "Shader.h"

ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader)
	: m_vertex(vertexShader), m_fragment(fragmentShader)
{
	m_id = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
	delete m_vertex;
	delete m_fragment;

	glDeleteProgram(m_id);
}

void ShaderProgram::use() {
	glUseProgram(m_id);
}

bool ShaderProgram::link() {
	if (!m_vertex->isCompiled()) {
		if (!m_vertex->compile()) {
			printf("ERROR: Failed to compile vertex shader. %s\n", m_vertex->getError().c_str());
		}
	}

	if (!m_fragment->isCompiled()) {
		if (!m_fragment->compile()) {
			printf("ERROR: Failed to compile fragment shader. %s\n", m_fragment->getError().c_str());
		}
	}

	glAttachShader(m_id, m_vertex->getShaderId());
	glAttachShader(m_id, m_fragment->getShaderId());

	glLinkProgram(m_id);

	glDetachShader(m_id, m_vertex->getShaderId());
	glDetachShader(m_id, m_fragment->getShaderId());

	return isLinked();
}

bool ShaderProgram::isLinked() {
	GLint result = GL_FALSE;
	glGetProgramiv(m_id, GL_LINK_STATUS, &result);
	return result == GL_TRUE;
}

std::string ShaderProgram::getError() {
	if (isLinked()) return "";

	GLint infoLogLength;
	glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength <= 0) {
		return "";
	}

	std::vector<char> errMessage(infoLogLength);
	glGetProgramInfoLog(m_id, infoLogLength, NULL, &errMessage[0]);

	std::string str(errMessage.begin(), errMessage.end());
	return str;
}

Shader::Shader(std::string shaderSource, GLenum type)
	: m_type(type)
{
	if (m_type != GL_VERTEX_SHADER && m_type != GL_FRAGMENT_SHADER) {
		// Throw exception - invalid parameter value
		throw "";
	}

	m_id = glCreateShader(m_type);
	updateSource(shaderSource);
}

Shader::~Shader() {
	deleteShader();
}

void Shader::deleteShader() {
	GLint deletePending;
	glGetShaderiv(m_id, GL_DELETE_STATUS, &deletePending);

	if (deletePending == GL_FALSE) {
		glDeleteShader(m_id);
	}
}

void Shader::updateSource(std::string source) {
	m_source = source;
	char const* cStrSource = m_source.c_str();
	glShaderSource(m_id, 1, &cStrSource, NULL);
	compile();
}

bool Shader::compile() {
	if (!isCompiled()) {
		glCompileShader(m_id);
		return isCompiled();
	}
	
	return true;
}

bool Shader::isCompiled() {
	GLint result = GL_FALSE;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &result);
	return result == GL_TRUE;
}

std::string Shader::getError() {
	if (isCompiled()) return "";

	GLint infoLogLength;
	glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

	bool isShader = glIsShader(m_id);

	if (infoLogLength > 0) {
		std::vector<char> errMessage(infoLogLength);
		glGetShaderInfoLog(m_id, infoLogLength, NULL, &errMessage[0]);

		std::string out(errMessage.begin(), errMessage.end());
		return out;
	}

	return "Did not compile, but couldn't retrieve error log.";
}
