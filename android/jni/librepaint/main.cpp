// @file	main.cpp
// @brief	...
// @author	Baguette Apps - Rémi Chaignon
// @date	08/04/2011
//

#include "main.h"


//
//
void Java_remi_chaignon_repaint_NativeInterface_initialize(JNIEnv *env, jobject self, jint surfaceWidth, jint surfaceHeight, jint frameWidth, jint frameHeight, jint bufferWidth, jint bufferHeight, jbyte *cameraBuffer, jstring assetPath)
{
	LOGV("[JNI::initialize]");


	// PARAMETERS /////////////////////

	sizes[SURFACE_WIDTH] = surfaceWidth;
	sizes[SURFACE_HEIGHT] = surfaceHeight;
	sizes[SURFACE_SIZE] = sizes[SURFACE_WIDTH] * sizes[SURFACE_HEIGHT];
	sizes[FRAME_WIDTH] = frameWidth;
	sizes[FRAME_HEIGHT] = frameHeight;
	sizes[FRAME_SIZE] = sizes[FRAME_WIDTH] * sizes[FRAME_HEIGHT];
	sizes[BUFFER_WIDTH] = bufferWidth;
	sizes[BUFFER_HEIGHT] = (GLint)(bufferHeight * 1.5);
	sizes[BUFFER_SIZE] = sizes[BUFFER_WIDTH] * sizes[BUFFER_HEIGHT];
	sizes[TEXTURE_WIDTH] = (GLint)pow(2, (int)ceil(log(frameWidth) / log(2)));
	sizes[TEXTURE_HEIGHT] = (GLint)pow(2, (int)ceil(log(frameHeight) / log(2)));
	sizes[TEXTURE_SIZE] = sizes[TEXTURE_WIDTH] * sizes[TEXTURE_HEIGHT];
	LOGD("[JNI::initialize] Surface(%d, %d) - Frame(%d, %d) - Buffer(%d, %d) - Texture (%d, %d)",
		sizes[SURFACE_WIDTH], sizes[SURFACE_HEIGHT],
		sizes[FRAME_WIDTH], sizes[FRAME_HEIGHT],
		sizes[BUFFER_WIDTH], sizes[BUFFER_HEIGHT],
		sizes[TEXTURE_WIDTH], sizes[TEXTURE_HEIGHT]);

	buffer = (GLubyte *)cameraBuffer;

	frameVertices[VERTEX_BOTTOM_LEFT_X] = -(GLfloat)sizes[FRAME_HEIGHT] / sizes[SURFACE_WIDTH];
	frameVertices[VERTEX_BOTTOM_LEFT_Y] = -(GLfloat)sizes[FRAME_WIDTH] / sizes[SURFACE_HEIGHT];
	frameVertices[VERTEX_BOTTOM_LEFT_Z] = 0.0f;
	frameVertices[VERTEX_BOTTOM_LEFT_U] = (sizes[FRAME_WIDTH] - 0.5f) / sizes[TEXTURE_WIDTH];
	frameVertices[VERTEX_BOTTOM_LEFT_V] = (sizes[FRAME_HEIGHT] - 0.5f) / sizes[TEXTURE_HEIGHT];
	frameVertices[VERTEX_BOTTOM_RIGHT_X] = (GLfloat)sizes[FRAME_HEIGHT] / sizes[SURFACE_WIDTH];
	frameVertices[VERTEX_BOTTOM_RIGHT_Y] = -(GLfloat)sizes[FRAME_WIDTH] / sizes[SURFACE_HEIGHT];
	frameVertices[VERTEX_BOTTOM_RIGHT_Z] = 0.0f;
	frameVertices[VERTEX_BOTTOM_RIGHT_U] = (sizes[FRAME_WIDTH] - 0.5f) / sizes[TEXTURE_WIDTH];
	frameVertices[VERTEX_BOTTOM_RIGHT_V] = 0.0f;
	frameVertices[VERTEX_TOP_RIGHT_X] = (GLfloat)sizes[FRAME_HEIGHT] / sizes[SURFACE_WIDTH];
	frameVertices[VERTEX_TOP_RIGHT_Y] = (GLfloat)sizes[FRAME_WIDTH] / sizes[SURFACE_HEIGHT];
	frameVertices[VERTEX_TOP_RIGHT_Z] = 0.0f;
	frameVertices[VERTEX_TOP_RIGHT_U] =  0.0f;
	frameVertices[VERTEX_TOP_RIGHT_V] = 0.0f;
	frameVertices[VERTEX_TOP_LEFT_X] = -(GLfloat)sizes[FRAME_HEIGHT] / sizes[SURFACE_WIDTH];
	frameVertices[VERTEX_TOP_LEFT_Y] = (GLfloat)sizes[FRAME_WIDTH] / sizes[SURFACE_HEIGHT];
	frameVertices[VERTEX_TOP_LEFT_Z] = 0.0f;
	frameVertices[VERTEX_TOP_LEFT_U] = 0.0f;
	frameVertices[VERTEX_TOP_LEFT_V] = (sizes[FRAME_HEIGHT] - 0.5f) / sizes[TEXTURE_HEIGHT];

	screenVertices[VERTEX_BOTTOM_LEFT_X] = -(GLfloat)sizes[TEXTURE_HEIGHT] / sizes[SURFACE_WIDTH];
	screenVertices[VERTEX_BOTTOM_LEFT_Y] = -(GLfloat)sizes[TEXTURE_WIDTH] / sizes[SURFACE_HEIGHT];
	screenVertices[VERTEX_BOTTOM_LEFT_Z] = 0.0f;
	screenVertices[VERTEX_BOTTOM_LEFT_U] = 0.0f;
	screenVertices[VERTEX_BOTTOM_LEFT_V] = 0.0f;
	screenVertices[VERTEX_BOTTOM_RIGHT_X] = (GLfloat)sizes[TEXTURE_HEIGHT] / sizes[SURFACE_WIDTH];
	screenVertices[VERTEX_BOTTOM_RIGHT_Y] = -(GLfloat)sizes[TEXTURE_WIDTH] / sizes[SURFACE_HEIGHT];
	screenVertices[VERTEX_BOTTOM_RIGHT_Z] = 0.0f;
	screenVertices[VERTEX_BOTTOM_RIGHT_U] = (sizes[FRAME_HEIGHT] - 0.5f) / sizes[TEXTURE_WIDTH];
	screenVertices[VERTEX_BOTTOM_RIGHT_V] = 0.0f;
	screenVertices[VERTEX_TOP_RIGHT_X] = (GLfloat)sizes[TEXTURE_HEIGHT] / sizes[SURFACE_WIDTH];
	screenVertices[VERTEX_TOP_RIGHT_Y] = (GLfloat)sizes[TEXTURE_WIDTH] / sizes[SURFACE_HEIGHT];
	screenVertices[VERTEX_TOP_RIGHT_Z] = 0.0f;
	screenVertices[VERTEX_TOP_RIGHT_U] = (sizes[FRAME_HEIGHT] - 0.5f) / sizes[TEXTURE_WIDTH];
	screenVertices[VERTEX_TOP_RIGHT_V] = (sizes[FRAME_WIDTH] - 0.5f) / sizes[TEXTURE_HEIGHT];
	screenVertices[VERTEX_TOP_LEFT_X] = -(GLfloat)sizes[TEXTURE_HEIGHT] / sizes[SURFACE_WIDTH];
	screenVertices[VERTEX_TOP_LEFT_Y] = (GLfloat)sizes[TEXTURE_WIDTH] / sizes[SURFACE_HEIGHT];
	screenVertices[VERTEX_TOP_LEFT_Z] =  0.0f;
	screenVertices[VERTEX_TOP_LEFT_U] =  0.0f;
	screenVertices[VERTEX_TOP_LEFT_V] = (sizes[FRAME_WIDTH] - 0.5f) / sizes[TEXTURE_HEIGHT];


	LOGD("FRAME =\n\t%f, %f, %f\n\t\t%f %f\n\t%f, %f, %f\n\t\t%f %f\n\t%f, %f, %f\n\t\t%f %f\n\t%f, %f, %f\n\t\t%f %f",
		frameVertices[0], frameVertices[1], frameVertices[2],		frameVertices[3], frameVertices[4],
		frameVertices[5], frameVertices[6], frameVertices[7],		frameVertices[8], frameVertices[9],
		frameVertices[10], frameVertices[11], frameVertices[12],	frameVertices[13], frameVertices[14],
		frameVertices[15], frameVertices[16], frameVertices[17],	frameVertices[18], frameVertices[19]);

	LOGD("SCREEN =\n\t%f, %f, %f\n\t\t%f %f\n\t%f, %f, %f\n\t\t%f %f\n\t%f, %f, %f\n\t\t%f %f\n\t%f, %f, %f\n\t\t%f %f",
		screenVertices[0], screenVertices[1], screenVertices[2],	screenVertices[3], screenVertices[4],
		screenVertices[5], screenVertices[6], screenVertices[7],	screenVertices[8], screenVertices[9],
		screenVertices[10], screenVertices[11], screenVertices[12],	screenVertices[13], screenVertices[14],
		screenVertices[15], screenVertices[16], screenVertices[17],	screenVertices[18], screenVertices[19]);


	// OPENGL /////////////////////////

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); GL();

	createTextures();
	createBuffers();
	createShaders();


	isInitialized = true;
}


//
//
void Java_remi_chaignon_repaint_NativeInterface_update(JNIEnv *env, jobject self)
{
	LOGV("[JNI::update]");

	if(isInitialized)
	{
		// Bind Luminance
		glBindTexture(GL_TEXTURE_2D, textureIds[TEXTURE_LUMINANCE]); GL();

		// Update texture
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, sizes[FRAME_WIDTH], sizes[FRAME_HEIGHT], GL_LUMINANCE, GL_UNSIGNED_BYTE,  BUFFER_OFFSET(buffer + FRAME_OFFSET)); GL();


		// Bind Chrominance
		glBindTexture(GL_TEXTURE_2D, textureIds[TEXTURE_CHROMINANCE]); GL();

		// Update texture
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, sizes[FRAME_WIDTH] / 2, sizes[FRAME_HEIGHT] / 2, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE,
			BUFFER_OFFSET(buffer + FRAME_OFFSET + sizes[FRAME_SIZE])); GL();
	}
}


//
//
void Java_remi_chaignon_repaint_NativeInterface_render(JNIEnv *env, jobject self)
{
	LOGV("[JNI::render]");

	if(isInitialized)
	{
/*		if(doReset)
		{
			reset();
			doLeft = false;
			doRight = false;
			doReset = false;
		}
		else
		{
			if(doLeft)
			{
				left();
				doLeft = false;
			}

			if(doRight)
			{
				right();
				doRight = false;
			}
		}

		getScreenBuffer();

		bindOffScreenBuffer();
		renderOffScreen();

		if(hasBeenTouched)
		{
			hasBeenTouched = false;

			read();
		}

		bindOnScreenBuffer();
		renderOnScreen();
*/
		renderSimpleFrame();
	}
}


//
//
void Java_remi_chaignon_repaint_NativeInterface_touch(JNIEnv *env, jobject self, jint originX, jint originY, jint width, jint height)
{
	LOGV("[JNI::touch]");

	hasBeenTouched = true;

	touchAreaWidth = width;
	touchAreaHeight = height;
	touchAreaOriginX = originX - (touchAreaWidth / 2);
	touchAreaOriginY = originY - (touchAreaHeight / 2);
	LOGD("[JNI::touch] %d %d %d %d", touchAreaOriginX, touchAreaOriginY, touchAreaWidth, touchAreaHeight);
}


//
//
void Java_remi_chaignon_repaint_NativeInterface_left(JNIEnv *env, jobject self)
{
	LOGV("[JNI::left]");

	doLeft = true;
}


//
//
void Java_remi_chaignon_repaint_NativeInterface_right(JNIEnv *env, jobject self)
{
	LOGV("[JNI::right]");

	doRight = true;
}


//
//
void Java_remi_chaignon_repaint_NativeInterface_reset(JNIEnv *env, jobject self)
{
	LOGV("[JNI::reset]");

	doReset = true;
}


//
//
void Java_remi_chaignon_repaint_NativeInterface_destroy(JNIEnv *env, jobject self)
{
	LOGV("[JNI::destroy]");

	glDeleteTextures(NUMBER_OF_TEXTURES, textureIds); GL();
	glDeleteFramebuffers(NUMBER_OF_FRAMEBUFFERS, frameBuffers); GL();
}

///////////////////////////////////////////////////////////////////////////////

//
//
void getScreenBuffer()
{
	LOGV("[JNI::getScreenBuffer]");

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &screenBuffer); GL();
}

//
//
void bindOffScreenBuffer()
{
	LOGV("[JNI::bindOffScreenBuffer]");

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffers[FRAMEBUFFER_OFFSCREEN]); GL();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureIds[TEXTURE_TARGET], 0); GL();
}

//
//
void bindOnScreenBuffer()
{
	LOGV("[JNI::bindOnScreenBuffer]");

	glBindFramebuffer(GL_FRAMEBUFFER, screenBuffer); GL();
}


//
//
void createTextures()
{
	LOGV("[JNI::createTextures]");

	// Setup the textures
	glGenTextures(NUMBER_OF_TEXTURES, textureIds); GL();

	// Target
	glActiveTexture(GL_TEXTURE0); GL();
	glBindTexture(GL_TEXTURE_2D, textureIds[TEXTURE_TARGET]); GL();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizes[TEXTURE_WIDTH], sizes[TEXTURE_HEIGHT], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); GL();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); GL();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); GL();

	// Luminance
	glActiveTexture(GL_TEXTURE1); GL();
	glBindTexture(GL_TEXTURE_2D, textureIds[TEXTURE_LUMINANCE]); GL();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, sizes[TEXTURE_WIDTH], sizes[TEXTURE_HEIGHT], 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, NULL); GL();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); GL();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); GL();

	// Chrominance
	glActiveTexture(GL_TEXTURE2); GL();
	glBindTexture(GL_TEXTURE_2D, textureIds[TEXTURE_CHROMINANCE]); GL();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, sizes[TEXTURE_WIDTH] / 2, sizes[TEXTURE_HEIGHT] / 2, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, NULL); GL();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); GL();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); GL();
}


//
//
void createBuffers()
{
	LOGV("[JNI::createBuffers]");

	glGenFramebuffers(NUMBER_OF_FRAMEBUFFERS, frameBuffers); GL();
}


//
//
void createShaders()
{
	LOGV("[JNI::createShaders]");

	// FRAME //////////////////////////

	// Create program
	programIds[SHADER_FRAME] = glwCreateProgram(frameVertexShaderSource, frameFragmentShaderSource);

	// Bind locations
	glBindAttribLocation(programIds[SHADER_FRAME], FRAME_ATTRIBUTE_POSITION, "a_position"); GL();
	glBindAttribLocation(programIds[SHADER_FRAME], FRAME_ATTRIBUTE_TEXTURECOORDINATE, "a_texCoord"); GL();

	// Link program
	glwLinkProgram(programIds[SHADER_FRAME]);

	// Get locations
	frameUniforms[FRAME_UNIFORM_LUMINANCE] = glGetUniformLocation(programIds[SHADER_FRAME], "s_luminance"); GL();
	frameUniforms[FRAME_UNIFORM_CHROMINANCE] = glGetUniformLocation(programIds[SHADER_FRAME], "s_chrominance"); GL();


	// Use program
	glUseProgram(programIds[SHADER_FRAME]); GL();

	// Set uniforms
	glUniform1i(frameUniforms[FRAME_UNIFORM_LUMINANCE], 1); GL();
	glUniform1i(frameUniforms[FRAME_UNIFORM_CHROMINANCE], 2); GL();

	LOGI("[JNI::createShaders] FRAME_ATTRIBUTE_POSITION = %d", FRAME_ATTRIBUTE_POSITION);
	LOGI("[JNI::createShaders] FRAME_ATTRIBUTE_TEXTURECOORDINATE = %d", FRAME_ATTRIBUTE_TEXTURECOORDINATE);
	LOGI("[JNI::createShaders] FRAME_UNIFORM_LUMINANCE = %d", frameUniforms[FRAME_UNIFORM_LUMINANCE]);
	LOGI("[JNI::createShaders] FRAME_UNIFORM_CHROMINANCE = %d", frameUniforms[FRAME_UNIFORM_CHROMINANCE]);


	// REPAINT ////////////////////////

	// Create program
	programIds[SHADER_REPAINT] = glwCreateProgram(repaintVertexShaderSource, repaintFragmentShaderSource);

	// Bind locations
	glBindAttribLocation(programIds[SHADER_REPAINT], REPAINT_ATTRIBUTE_POSITION, "a_position"); GL();
	glBindAttribLocation(programIds[SHADER_REPAINT], REPAINT_ATTRIBUTE_TEXTURECOORDINATE, "a_texCoord"); GL();

	// Link program
	glwLinkProgram(programIds[SHADER_REPAINT]);

	// Get locations
	repaintUniforms[REPAINT_UNIFORM_LUMINANCE] = glGetUniformLocation(programIds[SHADER_REPAINT], "s_luminance"); GL();
	repaintUniforms[REPAINT_UNIFORM_CHROMINANCE] = glGetUniformLocation(programIds[SHADER_REPAINT], "s_chrominance"); GL();
	repaintUniforms[REPAINT_UNIFORM_COLOR_IN] = glGetUniformLocation(programIds[SHADER_REPAINT], "u_in"); GL();
	repaintUniforms[REPAINT_UNIFORM_COLOR_OUT] = glGetUniformLocation(programIds[SHADER_REPAINT], "u_out"); GL();


	// Use program
	glUseProgram(programIds[SHADER_REPAINT]); GL();

	// Set uniforms
	GLfloat color[2] = { 0.0f, 0.0001f };
	glUniform1i(repaintUniforms[REPAINT_UNIFORM_LUMINANCE], 1); GL();
	glUniform1i(repaintUniforms[REPAINT_UNIFORM_CHROMINANCE], 2); GL();
	glUniform2fv(repaintUniforms[REPAINT_UNIFORM_COLOR_IN], 1, color); GL();
	glUniform1f(repaintUniforms[REPAINT_UNIFORM_COLOR_OUT], 0.0f); GL();

	LOGI("[JNI::createShaders] REPAINT_ATTRIBUTE_POSITION = %d", REPAINT_ATTRIBUTE_POSITION);
	LOGI("[JNI::createShaders] REPAINT_ATTRIBUTE_TEXTURECOORDINATE = %d", REPAINT_ATTRIBUTE_TEXTURECOORDINATE);
	LOGI("[JNI::createShaders] REPAINT_UNIFORM_LUMINANCE = %d", repaintUniforms[REPAINT_UNIFORM_LUMINANCE]);
	LOGI("[JNI::createShaders] REPAINT_UNIFORM_CHROMINANCE = %d", repaintUniforms[REPAINT_UNIFORM_CHROMINANCE]);
	LOGI("[JNI::createShaders] REPAINT_UNIFORM_COLOR_IN = %d", repaintUniforms[REPAINT_UNIFORM_COLOR_IN]);
	LOGI("[JNI::createShaders] REPAINT_UNIFORM_COLOR_OUT = %d", repaintUniforms[REPAINT_UNIFORM_COLOR_OUT]);


	// SCREEN /////////////////////////

	// Create program
	programIds[SHADER_SCREEN] = glwCreateProgram(screenVertexShaderSource, screenFragmentShaderSource);

	// Bind locations
	glBindAttribLocation(programIds[SHADER_SCREEN], SCREEN_ATTRIBUTE_POSITION, "a_position"); GL();
	glBindAttribLocation(programIds[SHADER_SCREEN], SCREEN_ATTRIBUTE_TEXTURECOORDINATE, "a_texCoord"); GL();

	// Link program
	glwLinkProgram(programIds[SHADER_SCREEN]);

	// Get locations
	repaintUniforms[SCREEN_UNIFORM_TEXTURE] = glGetUniformLocation(programIds[SHADER_SCREEN], "s_texture"); GL();


	// Use program
	glUseProgram(programIds[SHADER_REPAINT]); GL();

	// Set uniforms
	glUniform1i(repaintUniforms[SCREEN_UNIFORM_TEXTURE], 0); GL();

	LOGI("[JNI::createShaders] SCREEN_ATTRIBUTE_POSITION = %d", SCREEN_ATTRIBUTE_POSITION);
	LOGI("[JNI::createShaders] SCREEN_ATTRIBUTE_TEXTURECOORDINATE = %d", SCREEN_ATTRIBUTE_TEXTURECOORDINATE);
	LOGI("[JNI::createShaders] SCREEN_UNIFORM_TEXTURE = %d", repaintUniforms[SCREEN_UNIFORM_TEXTURE]);
}


//
//
void renderOffScreen()
{
	LOGV("[JNI::renderOffScreen]");

	// Clear
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); GL();
	glClear(GL_COLOR_BUFFER_BIT); GL();


	// FRAME //////////////////////////

	// Use frame shader program
	glUseProgram(programIds[SHADER_REPAINT]); GL();

	// Enable vertes attributes
	glEnableVertexAttribArray(REPAINT_ATTRIBUTE_POSITION); GL();
	glEnableVertexAttribArray(REPAINT_ATTRIBUTE_TEXTURECOORDINATE); GL();

	// Load the vertex position
	glVertexAttribPointer(REPAINT_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, FRAME_VERTICES_STRIDE, BUFFER_OFFSET(frameVertices)); GL();
	glVertexAttribPointer(REPAINT_ATTRIBUTE_TEXTURECOORDINATE, 2, GL_FLOAT, GL_FALSE, FRAME_VERTICES_STRIDE, BUFFER_OFFSET(frameVertices + FRAME_VERTICES_OFFSET)); GL();

	// Draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, frameIndices); GL();

	// Reset to default
	glDisableVertexAttribArray(REPAINT_ATTRIBUTE_POSITION); GL();
	glDisableVertexAttribArray(REPAINT_ATTRIBUTE_TEXTURECOORDINATE); GL();
}


//
//
void renderOnScreen()
{
	LOGV("[JNI::renderOnScreen]");

	// Clear
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL();
	glClear(GL_COLOR_BUFFER_BIT); GL();


	// SCREEN /////////////////////////

	// Use screen shader program
	glUseProgram(programIds[SHADER_SCREEN]); GL();

	// Enable vertex attributes
	glEnableVertexAttribArray(SCREEN_ATTRIBUTE_POSITION); GL();
	glEnableVertexAttribArray(SCREEN_ATTRIBUTE_TEXTURECOORDINATE); GL();

	// Load the vertex position
	glVertexAttribPointer(SCREEN_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, SCREEN_VERTICES_STRIDE, BUFFER_OFFSET(screenVertices)); GL();
	glVertexAttribPointer(SCREEN_ATTRIBUTE_TEXTURECOORDINATE, 2, GL_FLOAT, GL_FALSE, SCREEN_VERTICES_STRIDE, BUFFER_OFFSET(screenVertices + SCREEN_VERTICES_OFFSET)); GL();

	// Draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, screenIndices); GL();

	// Reset to default
	glDisableVertexAttribArray(SCREEN_ATTRIBUTE_POSITION); GL();
	glDisableVertexAttribArray(SCREEN_ATTRIBUTE_TEXTURECOORDINATE); GL();
}


//
//
void renderSimpleFrame()
{
	LOGV("[JNI::renderSimpleFrame]");

	// Clear
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL();
	glClear(GL_COLOR_BUFFER_BIT); GL();

	// Use frame shader program
	glUseProgram(programIds[SHADER_FRAME]); GL();

	// Enable vertes attributes
	glEnableVertexAttribArray(FRAME_ATTRIBUTE_POSITION); GL();
	glEnableVertexAttribArray(FRAME_ATTRIBUTE_TEXTURECOORDINATE); GL();

	// Load the vertex position
	glVertexAttribPointer(FRAME_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, FRAME_VERTICES_STRIDE, BUFFER_OFFSET(frameVertices)); GL();
	glVertexAttribPointer(FRAME_ATTRIBUTE_TEXTURECOORDINATE, 2, GL_FLOAT, GL_FALSE, FRAME_VERTICES_STRIDE, BUFFER_OFFSET(&frameVertices[3])); GL();

	// Draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, frameIndices); GL();

	// Reset to default
	glDisableVertexAttribArray(FRAME_ATTRIBUTE_POSITION); GL();
	glDisableVertexAttribArray(FRAME_ATTRIBUTE_TEXTURECOORDINATE); GL();
}


//
//
void read()
{
	LOGD("[JNI::read]");

	unsigned int totalRed = 0;
	unsigned int totalGreen = 0;
	unsigned int totalBlue = 0;
	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	float hue = 0.0f;
	saturation = 0.0f;
	lightness = 0.0f;

	unsigned int size = touchAreaWidth * touchAreaHeight;
	GLubyte *sampleBuffer = (GLubyte *)malloc(size * 4);

	GLint correctedTouchAreaOriginY = sizes[SURFACE_HEIGHT] - touchAreaOriginY;
	LOGD("offX, offY, W, H = %d %d %d %d", touchAreaOriginX, correctedTouchAreaOriginY, touchAreaWidth, touchAreaHeight);

	glReadPixels(touchAreaOriginX, correctedTouchAreaOriginY, touchAreaWidth, touchAreaHeight, GL_RGBA, GL_UNSIGNED_BYTE, sampleBuffer); GL();

	for(unsigned int i = 0; i < size; ++i)
	{
		totalRed += sampleBuffer[(i * 4)];
		totalGreen += sampleBuffer[(i * 4) + 1];
		totalBlue += sampleBuffer[(i * 4) + 2];
	}

	LOGD("Total - R %d G %d B %d", (unsigned int)totalRed, (unsigned int)totalGreen, (unsigned int)totalBlue);
	float denominator = size * 255.0f;
	red = (float)totalRed / denominator;
	green = (float)totalGreen / denominator;
	blue = (float)totalBlue / denominator;
	LOGD("Average - R %f G %f B %f", red, green, blue);
	convertRGBtoHSL(red, green, blue, hue, saturation, lightness);
	LOGD("Average - H %f S %f L %f", hue, saturation, lightness);

	for(unsigned int i = 0; i < size; ++i)
	{
		if((i % 2) == 0)
		{
			sampleBuffer[(i * 4)] = (GLubyte)0;
			sampleBuffer[(i * 4) + 1] = (GLubyte)0;
			sampleBuffer[(i * 4) + 2] = (GLubyte)0;
			sampleBuffer[(i * 4) + 3] = (GLubyte)255;
		}
	}
	glBindTexture(GL_TEXTURE_2D, textureIds[TEXTURE_TARGET]); GL();
	glTexSubImage2D(GL_TEXTURE_2D, 0, touchAreaOriginX, correctedTouchAreaOriginY, touchAreaWidth, touchAreaHeight, GL_RGBA, GL_UNSIGNED_BYTE, sampleBuffer); GL();

	// Use frame program
	glUseProgram(programIds[SHADER_REPAINT]); GL();

	// Set uniforms
	if(hue > 180.0f)
	{
		newHue = hue - 180.0f;
	}
	else
	{
		newHue = hue + 180.0f;
	}
	LOGD("New - H %f S %f L %f", newHue, saturation, lightness);
	GLfloat colorIn[2] = { ((hue - HUE_THRESHOLD) < 0.0f) ? (hue - HUE_THRESHOLD + 360.0f) : (hue - HUE_THRESHOLD), ((hue + HUE_THRESHOLD) > 360.0f) ? (hue + HUE_THRESHOLD - 360.0f) : (hue + HUE_THRESHOLD) };
	LOGD("Threshold = [%f, %f]", colorIn[0], colorIn[1]);
	glUniform2fv(repaintUniforms[REPAINT_UNIFORM_COLOR_IN], 1, colorIn); GL();
	glUniform1f(repaintUniforms[REPAINT_UNIFORM_COLOR_OUT], newHue); GL();
}


//
//
void left()
{
	LOGD("[JNI::left]");
}


//
//
void right()
{
	LOGD("[JNI::right]");
}


//
//
void reset()
{
	LOGD("[JNI::reset]");

	newHue = 0.0f;

	// Use frame program
	glUseProgram(programIds[SHADER_REPAINT]); GL();

	// Set uniforms
	GLfloat colorIn[2] = { 0.0f, 0.0001f };
	glUniform2fv(repaintUniforms[REPAINT_UNIFORM_COLOR_IN], 1, colorIn); GL();
	glUniform1f(repaintUniforms[REPAINT_UNIFORM_COLOR_OUT], 0.0f); GL();
}


///////////////////////////////////////////////////////////////////////////////

//
//
float minimum(float f, float g)
{
	LOGV("[JNI::min]");


	if(f < g)
	{
		return f;
	}

	return g;
}

//
//
float maximum(float f, float g)
{
	LOGV("[JNI::max]");


	if(f > g)
	{
		return f;
	}

	return g;
}

// TODO: Implement those functions correctly (just stubbed out so far)

//
//
void convertYCrCbtoRGB(float y, float cr, float cb, float &r, float &g, float &b)
{
	LOGV("[JNI::convertYCrCbtoRGB]");


	r = -222.921f + ((298.082f * y) + (408.583f * cr)) / 256.0f;
	g = 135.576f + ((298.082f * y) + (-208.120f * cr) + (-100.291f * cb)) / 256.0f;
	b = -276.836f + ((298.082f * y) + (516.412f * cb)) / 256.0f;
}

//
//
void convertYCrCbtoHSL(float y, float cr, float cb, float &h, float &s, float &l)
{
	LOGV("[JNI::convertYCrCbtoHSL]");


//	float tmp0, tmp1, tmp2;

//	convertYCrCbtoRGB(y, cr, cb, &tmp0, &tmp1, &tmp2);
//	convertRGBtoHSL(tmp0, tmp1, tmp2, h, s, l);
}

//
//
void convertRGBtoYCrCb(float r, float g, float b, float &y, float &cr, float &cb)
{
	LOGV("[JNI::convertRGBtoYCrCb]");


	y = 16.0f + ((65.738f * r) + (129.057f * g) + (25.064f * b)) / 256.0f;
	cr = 128.0f + ((-37.945f * r) + (-74.494f * g) + (112.439f * b)) / 256.0f;
	cb = 128.0f + ((112.439f * r) + (94.154f * g) + (18.285f * b)) / 256.0f;
}

//
//
void convertRGBtoHSL(float r, float g, float b, float &h, float &s, float &l)
{
	LOGV("[JNI::convertRGBtoHSL]");


	float min = minimum(minimum(r, g), b);
	float max = maximum(maximum(r, g), b);
	float diff = max - min;

	l = (max + min) / 2.0f;


	if(min == max)
	{
		h = 0.0f;
		s = 0.0f;
		return;
	}

	if(l < 0.5f)
	{
		s = diff / (max + min);
	}
	else
	{
		s = diff / (2.0f - diff);
	}

	if(r == max)
	{
		h = (g - b) / diff;
	}
	else
	{
		if(g == max)
		{
			h = 2.0f + ((b - r) / diff);
		}
		else
		{
			h = 4.0f + ((r - g) / diff);
		}
	}

	h *= 60.0f;
	if(h < 0.0f)
	{
		h += 360.0f;
	}
}

//
//
void convertHSLtoYCrCb(float h, float s, float l, float &y, float &cr, float &cb)
{
	LOGV("[JNI::convertHSLtoYCrCb]");


//	float tmp0, tmp1, tmp2;

//	convertHSLtoRGB(h, s, l, &tmp0, &tmp1, &tmp2);
//	convertRGBtoYCrCb(tmp0, tmp1, tmp2, y, cr, cb);
}

//
//
void convertHSLtoRGB(float h, float s, float l, float &r, float &g, float &b)
{
	LOGV("[JNI::convertHSLtoRGB]");


	if(s == 0.0f)
	{
		r = l;
		g = l;
		b = l;
		return;
	}

	float tmp1 = 0.0f;
	float tmp2 = 0.0f;
	float tmp3 = 0.0f;

	if(l < 0.5f)
	{
		tmp2 = l * (1.0f + s);
	}
	else
	{
		tmp2 = l + s - (l * s);
	}

	tmp1 = (2.0f * l) - tmp2;

	h /= 360.0f;

	// R
	tmp3 = h + (1.0f / 3.0f);

	if(tmp3 < 0.0f)
	{
		tmp3 += 1.0f;
	}
	if(tmp3 > 1.0f)
	{
		tmp3 - 1.0f;
	}

	if((6.0f * tmp3) < 1.0f)
	{
		r = tmp1 + ((tmp2  - tmp1) * 6.0f * tmp3);
	}
	else
	{
		if((2.0f * tmp3) < 1.0f)
		{
			r = tmp2;
		}
		else
		{
			if((3.0f * tmp3) < 2.0f)
			{
				r = tmp1 + ((tmp2 - tmp1) * ((2.0f / 3.0f) - tmp3) * 6.0f);
			}
			else
			{
				r = tmp1;
			}
		}
	}

	// G
	tmp3 = h;

	if(tmp3 < 0.0f)
	{
		tmp3 += 1.0f;
	}
	if(tmp3 > 1.0f)
	{
		tmp3 - 1.0f;
	}

	if((6.0f * tmp3) < 1.0f)
	{
		g = tmp1 + ((tmp2  - tmp1) * 6.0f * tmp3);
	}
	else
	{
		if((2.0f * tmp3) < 1.0f)
		{
			g = tmp2;
		}
		else
		{
			if((3.0f * tmp3) < 2.0f)
			{
				g = tmp1 + ((tmp2 - tmp1) * ((2.0f / 3.0f) - tmp3) * 6.0f);
			}
			else
			{
				g = tmp1;
			}
		}
	}

	// B
	tmp3 = h - (1.0f / 3.0f);

	if(tmp3 < 0.0f)
	{
		tmp3 += 1.0f;
	}
	if(tmp3 > 1.0f)
	{
		tmp3 - 1.0f;
	}

	if((6.0f * tmp3) < 1.0f)
	{
		b = tmp1 + ((tmp2  - tmp1) * 6.0f * tmp3);
	}
	else
	{
		if((2.0f * tmp3) < 1.0f)
		{
			b = tmp2;
		}
		else
		{
			if((3.0f * tmp3) < 2.0f)
			{
				b = tmp1 + ((tmp2 - tmp1) * ((2.0f / 3.0f) - tmp3) * 6.0f);
			}
			else
			{
				b = tmp1;
			}
		}
	}
}

