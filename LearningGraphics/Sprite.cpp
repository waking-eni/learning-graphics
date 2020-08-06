#include "Sprite.h"



Sprite::Sprite()
{
	_vboID = 0;
}


Sprite::~Sprite()
{
	//whenever the sprite is destroyed, the buffer gets freed
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	// creating vertex buffer
	if (_vboID == 0) {
		// _vboID will change to the id of the buffer
		glGenBuffers(1, &_vboID);
	}

	// making a square
	float vertexData[12];

	/*

	() . . . ()
	.         .
	.         .
	.         .
	() . . . ()

	*/

	/* first triangle */
	// top right corner
	vertexData[0] = x + width;
	vertexData[1] = y + height;
	// top left corner
	vertexData[2] = x;
	vertexData[3] = y + height;
	// bottom left corner
	vertexData[4] = x;
	vertexData[5] = y;

	/* second triangle */
	// bottom left corner
	vertexData[6] = x;
	vertexData[7] = y;
	// bottom right corner
	vertexData[8] = x + width;
	vertexData[9] = y;
	// top right corner
	vertexData[10] = x + width;
	vertexData[11] = y + height;

	// bind the buffer, so it becomes active
	// only one GL buffer can be active at one time
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	// upload vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	// only sending the position information
	glEnableVertexAttribArray(0);

	// pointing openGL to the start of data
	// 2 because we're using x and y coordinates
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// draw the data
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
