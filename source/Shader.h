#pragma once
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <cstdio>
#include <string>
#include <fstream>
#include "Color.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "fRectangle.h"

class Shader
{
public:
	Shader();
	~Shader();
	bool loadProgram();
	void setVertexPointer(GLsizei stride, const GLvoid* data);
	void setTexCoordPointer(GLsizei stride, const GLvoid* data);
	void enableVertexPointer();
	void disableVertexPointer();
	void enableTexCoordPointer();
	void disableTexCoordPointer();
	void setProjection(glm::mat4 matrix);
	void setModelView(glm::mat4 matrix);
	void leftMultProjection(glm::mat4 matrix);
	void leftMultModelView(glm::mat4 matrix);
	void updateProjection();
	void updateModelView();
	void setTextureColor(Color color);
	void setTextureUnit(GLuint unit);
	GLuint loadShaderFromFile(std::string path, GLenum shaderType);
	bool bind();
	void unbind();
	GLuint getProgramID();

protected:
	void printProgramLog(GLuint program);
	void printShaderLog(GLuint shader);

	//Attribute locations
	GLint mVertexPos2DLocation;
	GLint mTexCoordLocation;

	//Coloring location
	GLint mTextureColorLocation;

	//Texture unit location
	GLint mTextureUnitLocation;

	//Projection matrix
	glm::mat4 mProjectionMatrix;
	GLint mProjectionMatrixLocation;

	//Modelview matrix
	glm::mat4 mModelViewMatrix;
	GLint mModelViewMatrixLocation;
	
	GLuint mProgramID;
};

