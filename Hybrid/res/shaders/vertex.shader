#version 330 core

// layout(location = 0) tells our shader which number attribute
// we should pull our data from. In this case we send it via
// glVertexAttribPointer with a location of 0, so we access it
// as location = 0 with layout.
layout(location = 0) in vec3 vertexPos_modelspace;

void main() {
	gl_Position.xyz = vertexPos_modelspace;
	gl_Position.w = 1.0;
}