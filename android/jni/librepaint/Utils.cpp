/// @file	Utils.cpp
/// @brief	Utility functions
/// @author	Baguette Apps - Rémi Chaignon
/// @date	29/04/2011
///

#include "Utils.h"


/// OPENGL WRAPPER ////////////////////////////////////////////////////////////

// Create and compile shader
//
//	param:	shaderType		- Type of the shader (vertex or fragment)
//	param:	shaderSource	- Code source of the shader
//	retrn:	GLuint			- Id of the loaded shader
//
GLuint glwLoadShader(GLenum shaderType, const char *shaderSource)
{
	LOGV("[Utils::glwLoadShader]");

	GLuint shaderId = glCreateShader(shaderType); GL();

	if(shaderId)
	{
		glShaderSource(shaderId, 1, &shaderSource, NULL); GL();
		glCompileShader(shaderId); GL();

		GLint compiled = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled); GL();

		if(!compiled)
		{
			GLint infoLength = 0;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLength); GL();

			if(infoLength)
			{
				char *buffer = (char *)malloc(infoLength);
				if(buffer)
				{
					glGetShaderInfoLog(shaderId, infoLength, NULL, buffer); GL();

					LOGE("[Utils::glwLoadShader] Could not compile shader %d:\n%s\n", shaderType, buffer);
					free(buffer);
				}
				glDeleteShader(shaderId); GL();

				shaderId = 0;
			}
		}
	}

	return shaderId;
}


// Create program and attach shaders
//
//	param:	vertexShaderSource		- Code source of the vertex shader
//	param:	fragmentShaderSource	- Code source of the fragment shader
//	retrn:	GLuint					- Id of the created shader program
//
GLuint glwCreateProgram(const char *vertexShaderSource, const char *fragmentShaderSource)
{
	LOGV("[Utils::glwCreateProgram]");

	GLuint vertexShaderId = glwLoadShader(GL_VERTEX_SHADER, vertexShaderSource);
	if(!vertexShaderId)
	{
		LOGE("[Utils::glwCreateProgram] Could not load vertex shader");
		return 0;
	}

	GLuint fragmentShaderId = glwLoadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	if(!fragmentShaderId)
	{
		LOGE("[Utils::glwCreateProgram] Could not load fragment shader");
		return 0;
	}

	GLuint programId = glCreateProgram(); GL();

	if(programId)
	{
		glAttachShader(programId, vertexShaderId); GL();

		glAttachShader(programId, fragmentShaderId); GL();

		return programId;
	}

	return 0;
}


// Link program
//
//	param:	_uProgramId	- Id of the shader program to link
//
void glwLinkProgram(GLuint programId)
{
	LOGV("[Utils::glwLinkProgram]");

	glLinkProgram(programId); GL();

	GLint linkStatus = GL_FALSE;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus); GL();

	if(linkStatus != GL_TRUE)
	{
		GLint bufferLength = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &bufferLength); GL();

		if(bufferLength)
		{
			char *buffer = (char *)malloc(bufferLength);
			if(buffer)
			{
				glGetProgramInfoLog(programId, bufferLength, NULL, buffer); GL();

				LOGE("[Utils::glwLinkProgram] Could not link program:\n%s\n", buffer);
				free(buffer);
			}
		}
		glDeleteProgram(programId); GL();

		programId = 0;
	}
}

