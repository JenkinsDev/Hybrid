// Copyright 2018 David Jenkins <djenkinsdev@gmail.com>
#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &m_id);
}

VAO::~VAO() {
	glDeleteVertexArrays(1, &m_id);
}

void VAO::bind() {
	glBindVertexArray(m_id);
}

void VAO::unbind() {
	glBindVertexArray(0);
}
