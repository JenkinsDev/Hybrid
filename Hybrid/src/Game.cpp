#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Engine/IO/Input.h"
#include "Engine/IO/File.h"
#include "Engine/GameEngine.h"
#include "Engine/Graphics/Shaders/Shader.h"
#include "Engine/Graphics/GL/VAO.h"

std::unique_ptr<ShaderProgram> loadShaders(std::string vertex_file_path, std::string fragment_file_path) {
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

	std::unique_ptr<ShaderProgram> program;
	program.reset(new ShaderProgram(vertexShaderCode, fragmentShaderCode));

	return program;
}

int main() {
	GameEngine engine;
	Screen screen(480, 620, "Hybrid", NULL);

	engine.changeActiveScreen(&screen);

	// VAO - Vertex Array Object
	VAO vao;
	vao.bind();

	// Array of vec3's which represent 4 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		0.0f, 0.2f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.2f, 0.0f, 0.0f,
		0.2f, 0.2f, 0.0f,
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

	std::unique_ptr<ShaderProgram> shaderProgram = loadShaders("./res/shaders/vertex.shader", "./res/shaders/fragment.shader");
	if (!shaderProgram->link()) {
		fprintf(stderr, "Failed to link shader program: %s", shaderProgram->getError().c_str());
		return 1;
	}

	while (engine.isRunning()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram->use();

		if (isKeyDown(Key::W)) {
			printf("Left Key Down");
		}

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

		glDrawArrays(GL_LINE_LOOP, 0, 4);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(screen.getWindow());
		glfwPollEvents();
	}

	return 0;
}