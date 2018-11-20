#include <array>
#include "Engine/IO/Input.h"
#include "Engine/IO/File.h"
#include "Engine/GameEngine.h"
#include "Engine/Graphics/Shaders/Shader.h"
#include "Engine/Graphics/GL/VAO.h"
#include "Game.h"
#include "Components.h"

void RendererSystem::tick(float dt, Entity* entity) {
	// We'll start with a very naive approach to rendering
	PositionComponent* pos = entity->getComponent<PositionComponent>();
	RectangleDrawableComponent* draw = entity->getComponent<RectangleDrawableComponent>();

	if (pos == nullptr || draw == nullptr) return;

	float xPos = pos->getX();
	float yPos = pos->getY();

	float width = draw->getWidth();
	float height = draw->getHeight();

	// Array of vec3's which represent 4 vertices
	std::array<GLfloat, 12> g_vertex_buffer_data = {
		xPos, yPos, 0.0f,
		xPos+width, yPos, 0.0f,
		xPos+width, yPos+height, 0.0f,
		xPos, yPos+height, 0.0f,
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), &g_vertex_buffer_data[0], GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glDisableVertexAttribArray(0);
}

void InputSystem::tick(float dt, Entity* entity) {
	VelocityComponent* vel = entity->getComponent<VelocityComponent>();
	PlayerComponent* playerComponent = entity->getComponent<PlayerComponent>();
	
	if (vel == nullptr || playerComponent == nullptr) return;

	if (isKeyDown(Key::W)) {
		vel->setYVelocity(0.01f);
	}
	else if (isKeyDown(Key::S)) {
		vel->setYVelocity(-0.01f);
	}
	else {
		vel->setYVelocity(0.0f);
	}

	if (isKeyDown(Key::D)) {
		vel->setXVelocity(0.01f);

	}
	else if (isKeyDown(Key::A)) {
		vel->setXVelocity(-0.01f);
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
	registerComponent<RectangleDrawableComponent>(std::make_unique<RectangleDrawableComponent>());
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
	engine.addSystem(std::make_shared<RendererSystem>());

	engine.addEntity(std::make_unique<PlayerEntity>());

	// Create our variable that we will store our buffer in,
	// then generate and store our buffer
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	std::unique_ptr<ShaderProgram> shaderProgram = loadShaders("./res/shaders/vertex.shader", "./res/shaders/fragment.shader");
	if (!shaderProgram->link()) {
		fprintf(stderr, "Failed to link shader program: %s", shaderProgram->getError().c_str());
		return 1;
	}
	shaderProgram->use();

	while (engine.isRunning()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		engine.tick();

		glfwSwapBuffers(screen.getWindow());
		glfwPollEvents();
	}

	return 0;
}