#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "Engine/GameEngine.h"
#include "Engine/Shaders/Shader.h"
#include "Engine/Graphics/GL/VAO.h"

enum class FileLoadStatus
{
	Error = 0x0,
	Success = 0x1
};

FileLoadStatus loadFile(std::string file_path, std::string* out) {
	std::ifstream fileStream(file_path, std::ios::in);

	if (fileStream.is_open()) {
		std::stringstream sstr;
		sstr << fileStream.rdbuf();

		*out = sstr.str();

		fileStream.close();
		return FileLoadStatus::Success;
	}

	return FileLoadStatus::Error;
}

ShaderProgram* loadShaders(std::string vertex_file_path, std::string fragment_file_path) {
	std::string vertexShaderCode;
	if (loadFile(vertex_file_path, &vertexShaderCode) == FileLoadStatus::Error) {
		printf("Can't open vertex shared %s.", vertex_file_path.c_str());
		getchar();
	}

	std::string fragmentShaderCode;
	if (loadFile(fragment_file_path, &fragmentShaderCode) == FileLoadStatus::Error) {
		printf("Can't open fragment shared %s.", fragment_file_path.c_str());
		getchar();
	}

	ShaderProgram* program = new ShaderProgram(vertexShaderCode, fragmentShaderCode);
	return program;
}

int main() {
	GameEngine engine;
	Screen screen(480, 620, "Hybrid", NULL);

	engine.changeActiveScreen(&screen);

	// VAO - Vertex Array Object
	VAO vao;
	vao.bind();

	// Array of 3 vectors which represent 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		0.0f, 0.2f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.2f, 0.0f, 0.0f,
	};

	// Create our variable that we will store our buffer in,
	// then generate and store our buffer
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);

	// glBindBuffer tells OpenGL that we want to run the next commands
	// on that buffer.
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our triangle vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	ShaderProgram* shaderProgram = loadShaders("./res/shaders/vertex.shader", "./res/shaders/fragment.shader");
	if (!shaderProgram->link()) {
		fprintf(stderr, "Failed to link shader program: %s", shaderProgram->getError().c_str());
	}

	while (!glfwWindowShouldClose(screen.getWindow())) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram->use();

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(screen.getWindow());
		glfwPollEvents();
	}

	return 0;
}