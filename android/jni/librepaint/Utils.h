/// @file	Utils.h
/// @brief	Utility functions
/// @author	Baguette Apps - Rémi Chaignon
/// @date	29/04/2011
///

#ifndef __UTILS_H__
#define __UTILS_H__


#include <jni.h>

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>


#ifdef __cplusplus
extern "C"
{
#endif


/// LOG ///////////////////////////////////////////////////////////////////////

#ifdef __ANDROID__
	#define DEBUG_TAG "BAGUETTE"

	#ifdef LOG_VERBOSE
		#define LOGV(...)	__android_log_print(ANDROID_LOG_VERBOSE, DEBUG_TAG, __VA_ARGS__)
		#define LOG_DEBUG
	#else
		#define LOGV(...)
	#endif

	#ifdef LOG_DEBUG
		#define LOGD(...)	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, __VA_ARGS__)
		#define LOG_INFO
	#else
		#define LOGD(...)
	#endif

	#ifdef LOG_INFO
		#define LOGI(...)	__android_log_print(ANDROID_LOG_INFO, DEBUG_TAG, __VA_ARGS__)
		#define LOG_WARNING
	#else
		#define LOGI(...)
	#endif

	#ifdef LOG_WARNING
		#define LOGW(...)	__android_log_print(ANDROID_LOG_WARNING, DEBUG_TAG, __VA_ARGS__)
		#define LOG_ERROR
	#else
		#define LOGW(...)
	#endif

	#ifdef LOG_ERROR
		#define LOGE(...)	__android_log_print(ANDROID_LOG_ERROR, DEBUG_TAG, __VA_ARGS__)
	#else
		#define LOGE(...)
	#endif
#endif


/// OPENGL WRAPPER ////////////////////////////////////////////////////////////

GLuint glwLoadShader(GLenum shaderType, const char *shaderSource);

GLuint glwCreateProgram(const char *vertexShaderSource, const char *fragmentShaderSource);
void glwLinkProgram(GLuint programId);

#ifdef DEBUG_OPENGL
	static void glwGetError(const char *filename, const int line)
	{
		GLint error = glGetError();

		for(; error; error = glGetError())
		{
			LOGE("[%s:%d] GL Error - 0x%x\n", filename, line, error);
		}
	}

	#define GL() glwGetError(__FILE__, __LINE__)
#else
	#define GL()
#endif


#ifdef __cplusplus
}
#endif


#endif
