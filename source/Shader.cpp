#include "Shader.h"

Shader::Shader()
{
	mProgramID = NULL;

	mVertexPos2DLocation = -1;
	mTexCoordLocation = -1;

	mProjectionMatrixLocation = -1;
	mModelViewMatrixLocation = -1;
	mTextureColorLocation = -1;
	mTextureUnitLocation = -1;
}

Shader::~Shader()
{
	glDeleteProgram(mProgramID);
}

bool Shader::loadProgram()
{
	//Generate program
	mProgramID = glCreateProgram();

	//Load vertex shader
	GLuint vertexShader = loadShaderFromFile("shaders/shader.glvs", GL_VERTEX_SHADER);

	//Check for errors
	if (vertexShader == 0)
	{
		glDeleteProgram(mProgramID);
		mProgramID = 0;
		return false;
	}

	//Attach vertex shader to program
	glAttachShader(mProgramID, vertexShader);


	//Create fragment shader
	GLuint fragmentShader = loadShaderFromFile("shaders/shader.glfs", GL_FRAGMENT_SHADER);

	//Check for errors
	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		glDeleteProgram(mProgramID);
		mProgramID = 0;
		return false;
	}

	//Attach fragment shader to program
	glAttachShader(mProgramID, fragmentShader);

	//Link program
	glLinkProgram(mProgramID);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(mProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		printf("Error linking program %d!\n", mProgramID);
		printProgramLog(mProgramID);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(mProgramID);
		mProgramID = 0;
		return false;
	}

	//Clean up excess shader references
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	mProjectionMatrixLocation = glGetUniformLocation(mProgramID, "LProjectionMatrix");
	if (mProjectionMatrixLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LProjectionMatrix");
	}

	mModelViewMatrixLocation = glGetUniformLocation(mProgramID, "LModelViewMatrix");
	if (mModelViewMatrixLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LModelViewMatrix");
	}

	/*mRotationLocation = glGetUniformLocation(mProgramID, "rotation");
	if (mRotationLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "rotation");
	}*/

	//Get variable locations
	mVertexPos2DLocation = glGetAttribLocation(mProgramID, "LVertexPos2D");
	if (mVertexPos2DLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LVertexPos2D");
	}

	mTexCoordLocation = glGetAttribLocation(mProgramID, "LTexCoord");
	if (mTexCoordLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LTexCoord");
	}

	mTextureColorLocation = glGetUniformLocation(mProgramID, "LTextureColor");
	if (mTextureColorLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LTextureColor");
	}

	mTextureUnitLocation = glGetUniformLocation(mProgramID, "LTextureUnit");
	if (mTextureUnitLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LTextureUnit");
	}

	return true;
}

void Shader::setVertexPointer(GLsizei stride, const GLvoid* data)
{
	glVertexAttribPointer(mVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void Shader::setTexCoordPointer(GLsizei stride, const GLvoid* data)
{
	glVertexAttribPointer(mTexCoordLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void Shader::enableVertexPointer()
{
	glEnableVertexAttribArray(mVertexPos2DLocation);
}

void Shader::disableVertexPointer()
{
	glDisableVertexAttribArray(mVertexPos2DLocation);
}

void Shader::enableTexCoordPointer()
{
	glEnableVertexAttribArray(mTexCoordLocation);
}

void Shader::disableTexCoordPointer()
{
	glDisableVertexAttribArray(mTexCoordLocation);
}

void Shader::setProjection(glm::mat4 matrix)
{
	mProjectionMatrix = matrix;
}

void Shader::setModelView(glm::mat4 matrix)
{
	mModelViewMatrix = matrix;
}

void Shader::leftMultProjection(glm::mat4 matrix)
{
	mProjectionMatrix = matrix * mProjectionMatrix;
}

void Shader::leftMultModelView(glm::mat4 matrix)
{
	mModelViewMatrix = matrix * mModelViewMatrix;
}

void Shader::updateProjection()
{
	glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
}

void Shader::updateModelView()
{
	glUniformMatrix4fv(mModelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(mModelViewMatrix));
}

void Shader::setTextureColor(Color color)
{
	glUniform4fv(mTextureColorLocation, 1, (const GLfloat*)&color.get());
}

void Shader::setTextureUnit(GLuint unit)
{
	glUniform1i(mTextureUnitLocation, unit);
}

GLuint Shader::loadShaderFromFile(std::string path, GLenum shaderType)
{
	//Open file
	GLuint shaderID = 0;
	std::string shaderString;
	std::ifstream sourceFile(path.c_str());

	//Source file loaded
	if (sourceFile)
	{
		//Get shader source
		shaderString.assign((std::istreambuf_iterator< char >(sourceFile)), std::istreambuf_iterator< char >());
		//Create shader ID
		shaderID = glCreateShader(shaderType);

		//Set shader source
		const GLchar* shaderSource = shaderString.c_str();
		glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

		//Compile shader source
		glCompileShader(shaderID);

		//Check shader for errors
		GLint shaderCompiled = GL_FALSE;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
		if (shaderCompiled != GL_TRUE)
		{
			printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, shaderSource);
			printShaderLog(shaderID);
			glDeleteShader(shaderID);
			shaderID = 0;
		}
	}
	else
	{
		printf("Unable to open file %s\n", path.c_str());
	}

	return shaderID;
}

bool Shader::bind()
{
	//Use shaderm
	glUseProgram(mProgramID);

	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error binding shader! %s\n", gluErrorString(error));
		printProgramLog(mProgramID);
		return false;
	}

	return true;
}

void Shader::unbind()
{
	//Use default program
	glUseProgram(NULL);
}

GLuint Shader::getProgramID()
{
	return mProgramID;
}

void Shader::printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}

void Shader::printShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}