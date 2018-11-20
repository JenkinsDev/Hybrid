#include <array>
#include "Engine/IO/Input.h"
#include "Engine/IO/File.h"
#include "Engine/GameEngine.h"
#include "Engine/Graphics/Shaders/Shader.h"
#include "Engine/Graphics/GL/VAO.h"
#include "Game.h"
#include "Components.h"

void InputSystem::tick(float dt, Entity* entity) {
	VelocityComponent* vel = entity->getComponent<VelocityComponent>();
	PlayerComponent* playerComponent = entity->getComponent<PlayerComponent>();
	
	if (vel == nullptr || playerComponent == nullptr) return;

	if (isKeyDown(Key::W)) {
		vel->setYVelocity(0.1f);
	}
	else if (isKeyDown(Key::S)) {
		vel->setYVelocity(-0.1f);
	}
	else {
		vel->setYVelocity(0.0f);
	}

	if (isKeyDown(Key::A)) {
		vel->setXVelocity(0.1f);

	}
	else if (isKeyDown(Key::D)) {
		vel->setXVelocity(-0.1f);
	}
	else {
		vel->setXVelocity(0.0f);
	}
}

void MoveSystem::tick(float dt, Entity* entity) {
	PositionComponent* pos = entity->getComponent<PositionComponent>();
	VelocityComponent* vel = entity->getComponent<VelocityComponent>();

	// Entity doesn't have either a PositionComponent, VelocityComponent or neither.
	if (pos == nullptr || vel == nullptr) return;

	float newX = pos->getX() + vel->getXVelocity();
	float newY = pos->getY() + vel->getYVelocity();

	printf("New Position: (%f, %f)", newX, newY);

	pos->setPosition(newX, newY);
}

PlayerEntity::PlayerEntity() {
	registerComponent<PlayerComponent>(std::make_unique<PlayerComponent>());
	registerComponent<PositionComponent>(std::make_unique<PositionComponent>());
	registerComponent<VelocityComponent>(std::make_unique<VelocityComponent>());
}

template <size_t N>
void adjustVertexData(std::array<GLfloat, N> vertexPos, float xOffset, float yOffset) {
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

	return std::make_unique<ShaderProgram>(vertexShaderCode, fragmentShaderCode);
}

int main() {
	GameEngine engine;
	Screen screen(480, 620, "Hybrid", NULL);

	engine.changeActiveScreen(&screen);

	// VAO - Vertex Array Object
	VAO vao;
	vao.bind();

	engine.addSystem(std::make_shared<InputSystem>());
	engine.addSystem(std::make_shared<MoveSystem>());

	engine.addEntity(std::make_unique<PlayerEntity>());

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

	while (engine.isRunning()) {
		engine.tick();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram->use();
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glfwSwapBuffers(screen.getWindow());
		glfwPollEvents();
	}

	return 0;
}