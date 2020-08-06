#pragma once
#include <GL/glew.h>
class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height);
	void draw();

private:
	float _x;
	float _y;
	float _width;
	float _height;
	// vertex buffer object id
	// GLuint is guranateed to be 32 bits
	// openGL expects 32 bit unsigned int to be used with VBO
	GLuint _vboID;
};

