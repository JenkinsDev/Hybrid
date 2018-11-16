#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <array>
#include <iterator>
#include "Engine/IO/Input.h"
#include "Engine/IO/File.h"
#include "Engine/GameEngine.h"
#include "Engine/Graphics/Shaders/Shader.h"
#include "Engine/Graphics/GL/VAO.h"

template <size_t N>
void adjustVertexData(std::array<GLfloat, N> vertexPos, GLint vbo, float xOffset, float yOffset) {
	std::array<GLfloat, N> newPos;
	std::copy(vertexPos.begin(), vertexPos.end(), &newPos[0]);

	for (int i = 0; i < N; i += 3) {
		newPos[i] += xOffset;
		newPos[i + 1] += yOffset;
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPos), &newPos[0]);
}

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
	std::array<GLfloat, 12> g_vertex_buffer_data = {
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), &g_vertex_buffer_data[0], GL_STREAM_DRAW);

	std::unique_ptr<ShaderProgram> shaderProgram = loadShaders("./res/shaders/vertex.shader", "./res/shaders/fragment.shader");
	if (!shaderProgram->link()) {
		fprintf(stderr, "Failed to link shader program: %s", shaderProgram->getError().c_str());
		return 1;
	}

	float xOffset = 0;
	float yOffset = 0;

	while (engine.isRunning()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram->use();

		if (isKeyDown(Key::W)) {
			yOffset += 0.01f;
		}
		else if (isKeyDown(Key::S)) {
			yOffset -= 0.01f;
		}

		if (isKeyDown(Key::D)) {
			xOffset += 0.01f;
		}
		else if (isKeyDown(Key::A)) {
			xOffset -= 0.01f;
		}

		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		adjustVertexData(g_vertex_buffer_data, vertexbuffer, xOffset, yOffset);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

		glDrawArrays(GL_LINE_LOOP, 0, 4);

		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glfwSwapBuffers(screen.getWindow());
		glfwPollEvents();
	}

	return 0;
}