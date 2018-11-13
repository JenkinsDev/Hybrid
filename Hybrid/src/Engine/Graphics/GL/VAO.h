#ifndef __JINX_VAO_H_
#define __JINX_VAO_H_

#include <GL/glew.h>

/**
 * Vertex Array Object
 *
 * Create, Delete, Bind & Unbind vertex array objects.
 *
 * An application can create up to GL_MAX_VERTEX_ATTRIBS VAOs, indexed at 0.
 *
 * OpenGL Specification Usage:
 * VAOs are an GL object that store the state need to supply vertex
 * data to vertex shaders. It's used to store:
 *   * The format of the vertex data 
 *   * Buffer Objects (VBOs) providing the vertex data
 *
 * A VAO cannot be shared between GL contexts
 */
class VAO {
public:
	VAO();
	~VAO();

	/** Bind the VAO to our active context. **/
	void bind();

	/**
	 * Unbind the VAO from our active context. This will unbind all VAOs
	 * because GL only allows a single bound at a time.
	 */
	void unbind();

private:
	GLuint m_id = 0;
};

#endif