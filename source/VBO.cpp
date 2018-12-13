#include "VBO.h"

VBO::VBO()
{
	_shader = render->getShader();
	_vbo = 0;
	_ibo = 0;
	setTexture(0);
	_isUI = true;
	_wf = false;
	_numVertices = 0;
	drawType = GL_QUADS;
}

VBO::VBO(const VBO& v)
{
	_shader = render->getShader();
	_vbo = 0;
	_ibo = 0;
	_numVertices = v._numVertices;

	initVBO();

	for (int i = 0; i < _numVertices; i++)
	{
		vertices[i] = v.vertices[i];
	}

	drawType = GL_QUADS;

	setTexture(v._txr);
	setWireframe(v._wf);
}

VBO& VBO::operator=(const VBO& v)
{
	freeVBO();

	_vbo = 0;
	_ibo = 0;
	_numVertices = v._numVertices;

	initVBO();
	for (int i = 0; i < _numVertices; i++)
	{
		vertices[i] = v.vertices[i];
	}

	setTexture(v._txr);
	setWireframe(v._wf);

	return *this;
}

VBO::~VBO()
{
	freeVBO();
}

void VBO::draw()
{
	if (!_isUI)
	{
		for (int i = 0; i < _numVertices; i++)
		{
			vertices[i].position.x += gameCamera.x;
			vertices[i].position.y += gameCamera.y;
		}
	}

	//Set texture ID
	glBindTexture(GL_TEXTURE_2D, _txr);

	//_shader->enableVertexPointer();
	//_shader->enableTexCoordPointer();

	//Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	//Update vertex buffer data
	glBufferSubData(GL_ARRAY_BUFFER, 0, _numVertices * sizeof(VertexData2D), vertices);

	//Set texture coordinate data
	//glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData2D), (GLvoid*)offsetof(VertexData2D, texCoord));

	//Set vertex data
	//glVertexPointer(2, GL_FLOAT, sizeof(VertexData2D), (GLvoid*)offsetof(VertexData2D, position));

	//Set texture coordinate data
	_shader->setTexCoordPointer(sizeof(VertexData2D), (GLvoid*)offsetof(VertexData2D, texCoord));

	//Set vertex data
	_shader->setVertexPointer(sizeof(VertexData2D), (GLvoid*)offsetof(VertexData2D, position));

	//Set color data
	//glColorPointer(4, GL_FLOAT, sizeof(VertexData2D), (GLvoid*)offsetof(VertexData2D, color));

	_shader->setTextureColor(_color);

	//Draw quad using vertex data and index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	if (_wf)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, _numVertices, GL_UNSIGNED_INT, NULL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else glDrawElements(GL_TRIANGLES, _numVertices, GL_UNSIGNED_INT, NULL);

	//_shader->disableVertexPointer();
	//_shader->disableTexCoordPointer();

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	if (!_isUI)
	{
		for (int i = 0; i < _numVertices; i++)
		{
			vertices[i].position.x -= gameCamera.x;
			vertices[i].position.y -= gameCamera.y;
		}
	}
}

void VBO::drawClipped(fRectangle clip)
{
	draw();
}

void VBO::setNumVertices(int n)
{
	_numVertices = n;
	if (!updateVBO()) initVBO();
}

void VBO::setRGBA(Color c)
{
	_color = c;
}

void VBO::setTexture(GLuint t)
{
	_txr = t;
}

void VBO::setWireframe(bool b)
{
	_wf = b;
}

void VBO::setUI(bool b)
{
	if (_isUI != b)
	{
		_isUI = b;
		if (!_isUI)
		{
			for (int i = 0; i < _numVertices; i++)
			{
				vertices[i].position.x += gameCamera.x;
				vertices[i].position.y += gameCamera.y;
			}
		}
		else
		{
			for (int i = 0; i < _numVertices; i++)
			{
				vertices[i].position.x -= gameCamera.x;
				vertices[i].position.y -= gameCamera.y;
			}
		}
	}
}

void VBO::initVBO()
{
	//If texture is loaded and VBO does not already exist
	if (_vbo == 0)
	{
		//Vertex data
		VertexData2D *vData = new VertexData2D[_numVertices];
		GLuint *iData = new GLuint[_numVertices];

		//Set rendering indices
		for (int i = 0; i < _numVertices; i++)
		{
			iData[i] = i;
		}

		//Create VBO
		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, _numVertices * sizeof(VertexData2D), vData, GL_DYNAMIC_DRAW);

		//Create IBO
		glGenBuffers(1, &_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numVertices * sizeof(GLuint), iData, GL_DYNAMIC_DRAW);

		//Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		delete[] vData;
		delete[] iData;

		vertices = new VertexData2D[_numVertices];
	}
}

void VBO::freeVBO()
{
	//Free VBO and IBO
	if (_vbo != 0)
	{
		glDeleteBuffers(1, &_vbo);
		glDeleteBuffers(1, &_ibo);
		_vbo = 0;
		_ibo = 0;

		delete[] vertices;
	}
}

bool VBO::updateVBO()
{
	if (_vbo != 0)
	{
		//Vertex data
		VertexData2D *vData = new VertexData2D[_numVertices];
		GLuint *iData = new GLuint[_numVertices];

		//Set rendering indices
		for (int i = 0; i < _numVertices; i++)
		{
			iData[i] = i;
		}

		//update VBO
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, _numVertices * sizeof(VertexData2D), vData, GL_DYNAMIC_DRAW);

		//update IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numVertices * sizeof(GLuint), iData, GL_DYNAMIC_DRAW);

		//Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

		delete[] vData;
		delete[] iData;

		delete[] vertices;
		vertices = new VertexData2D[_numVertices];

		return true;
	}
	else return false;
}