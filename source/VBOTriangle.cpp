#include "VBOTriangle.h"

VBOTriangle::VBOTriangle()
{
	_vbo = 0;
	_ibo = 0;
	_txr = 0;
	_isUI = true;
	_wf = false;
	_numVertices = 3;
	initVBO();

	for (int i = 0; i < _numVertices; i++)
	{
		vertices[i].position.x = i / 64.f;
		vertices[i].position.y = i / 64.f;

		vertices[i].texCoord.s = 0.f;
		vertices[i].texCoord.t = 0.f;
	}

	setRGBA(Color(1.f, 1.f, 1.f, 1.f));
}

VBOTriangle::VBOTriangle(const VBOTriangle& v)
{
	_vbo = 0;
	_ibo = 0;
	_txr = 0;
	_numVertices = 3;
	initVBO();

	for (int i = 0; i < _numVertices; i++)
	{
		vertices[i] = v.vertices[i];
	}

	setWireframe(v._wf);
	setUI(v._isUI);
}

VBOTriangle& VBOTriangle::operator=(const VBOTriangle& v)
{
	for (int i = 0; i < _numVertices; i++)
	{
		vertices[i] = v.vertices[i];
	}

	setWireframe(v._wf);
	_isUI = v._isUI;

	return *this;
}

VBOTriangle::~VBOTriangle()
{
	freeVBO();
}

void VBOTriangle::draw()
{
	
}

void VBOTriangle::drawClipped(fRectangle clip)
{
	draw();
}

void VBOTriangle::setRGBA(Color c)
{
	
}

void VBOTriangle::setWireframe(bool b)
{
	_wf = b;
}

void VBOTriangle::setUI(bool b)
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

void VBOTriangle::initVBO()
{
	//If texture is loaded and VBO does not already exist
	if (_vbo == 0)
	{
		//Vertex data
		VertexData2D *vData = new VertexData2D[_numVertices];
		GLuint *iData = new GLuint[_numVertices];

		//Set rendering indices
		iData[0] = 0;
		iData[1] = 1;
		iData[2] = 2;
		iData[3] = 3;

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
	}
}

void VBOTriangle::freeVBO()
{
	//Free VBO and IBO
	if (_vbo != 0)
	{
		glDeleteBuffers(1, &_vbo);
		glDeleteBuffers(1, &_ibo);
		_vbo = 0;
		_ibo = 0;
	}
}

void VBOTriangle::setTriangle(Vertex a, Vertex b, Vertex c)
{
	vertices[0].position = a;
	vertices[1].position = b;
	vertices[2].position = c;
}