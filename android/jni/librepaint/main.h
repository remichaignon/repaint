// @file	main.h
// @brief	...
// @author	Baguette Apps - Rémi Chaignon
// @date	08/04/2011
//


#ifndef __REPAINT_MAIN_H__
#define __REPAINT_MAIN_H__

#include "Utils.h"
#include "Shaders.h"
#include "Objects.h"

#define HUE_THRESHOLD	7.5f
#define HUE_STEP		20.0f

#define FRAME_OFFSET	16


#define SURFACE_WIDTH	0
#define SURFACE_HEIGHT	1
#define SURFACE_SIZE	2
#define FRAME_WIDTH		3
#define FRAME_HEIGHT	4
#define FRAME_SIZE		5
#define BUFFER_WIDTH	6
#define BUFFER_HEIGHT	7
#define BUFFER_SIZE		8
#define TEXTURE_WIDTH	9
#define TEXTURE_HEIGHT	10
#define TEXTURE_SIZE	11

#define BUFFER_OFFSET(i) (GLubyte *)(NULL + (i))


GLint	sizes[12];

GLint	screenBuffer = -1;
GLubyte	*buffer = NULL;

GLint	touchAreaOriginX = -1;
GLint	touchAreaOriginY = -1;
GLint	touchAreaWidth = -1;
GLint	touchAreaHeight = -1;

GLfloat	newHue = 0.0f;
GLfloat	saturation = 0.0f;
GLfloat	lightness = 0.0f;

bool	isInitialized = false;
bool	hasBeenTouched = false;
bool	doLeft = false;
bool	doRight = false;
bool	doReset = false;

enum ePrograms
{
	SHADER_FRAME,
	SHADER_REPAINT,
	SHADER_SCREEN,
	SHADER_ARROW,
	NUMBER_OF_PROGRAMS
};
GLuint	programIds[NUMBER_OF_PROGRAMS];

enum eTextures
{
	TEXTURE_TARGET,
	TEXTURE_LUMINANCE,
	TEXTURE_CHROMINANCE,
	TEXTURE_ARROW,
	NUMBER_OF_TEXTURES
};
GLuint	textureIds[NUMBER_OF_TEXTURES];

enum eFrameBuffers
{
	FRAMEBUFFER_OFFSCREEN,
	NUMBER_OF_FRAMEBUFFERS
};
GLuint	frameBuffers[NUMBER_OF_FRAMEBUFFERS];

enum eFrameAttributes
{
	FRAME_ATTRIBUTE_POSITION,
	FRAME_ATTRIBUTE_TEXTURECOORDINATE,
};
enum eFrameUniforms
{
	FRAME_UNIFORM_LUMINANCE,
	FRAME_UNIFORM_CHROMINANCE,
	NUMBER_OF_FRAME_UNIFORMS
};
GLint	frameUniforms[NUMBER_OF_FRAME_UNIFORMS];

enum eRepaintAttributes
{
	REPAINT_ATTRIBUTE_POSITION,
	REPAINT_ATTRIBUTE_TEXTURECOORDINATE,
};
enum eRepaintUniforms
{
	REPAINT_UNIFORM_LUMINANCE,
	REPAINT_UNIFORM_CHROMINANCE,
	REPAINT_UNIFORM_COLOR_IN,
	REPAINT_UNIFORM_COLOR_OUT,
	NUMBER_OF_REPAINT_UNIFORMS
};
GLint	repaintUniforms[NUMBER_OF_REPAINT_UNIFORMS];

enum eScreenAttributes
{
	SCREEN_ATTRIBUTE_POSITION,
	SCREEN_ATTRIBUTE_TEXTURECOORDINATE,
};
enum eScreenUniforms
{
	SCREEN_UNIFORM_TEXTURE,
	NUMBER_OF_SCREEN_UNIFORMS
};
GLint	screenUniforms[NUMBER_OF_SCREEN_UNIFORMS];

enum eArrowAttributes
{
	ARROW_ATTRIBUTE_POSITION,
	ARROW_ATTRIBUTE_TEXTURECOORDINATE,
};
enum eArrowUniforms
{
	ARROW_UNIFORM_TEXTURE,
	ARROW_UNIFORM_COLOR_IN,
	NUMBER_OF_ARROW_UNIFORMS
};
GLint	arrowUniforms[NUMBER_OF_ARROW_UNIFORMS];


#ifdef __cplusplus
extern "C"
{
#endif


void Java_remi_chaignon_repaint_NativeInterface_initialize(JNIEnv *env, jobject self, jint surfaceWidth, jint surfaceHeight, jint frameWidth, jint frameHeight, jint bufferWidth, jint bufferHeight, jbyte *cameraBuffer, jstring assetPath);
void Java_remi_chaignon_repaint_NativeInterface_update(JNIEnv *env, jobject self);
void Java_remi_chaignon_repaint_NativeInterface_render(JNIEnv *env, jobject self);
void Java_remi_chaignon_repaint_NativeInterface_touch(JNIEnv *env, jobject self, jint originX, jint originY, jint width, jint height);
void Java_remi_chaignon_repaint_NativeInterface_left(JNIEnv *env, jobject self);
void Java_remi_chaignon_repaint_NativeInterface_right(JNIEnv *env, jobject self);
void Java_remi_chaignon_repaint_NativeInterface_reset(JNIEnv *env, jobject self);
void Java_remi_chaignon_repaint_NativeInterface_destroy(JNIEnv *env, jobject self);

///////////////////////////////////////////////////////////////////////////////

void createTargetObject();
void createScreenObject();
void createObjects();

void createLuminanceTexture();
void createChrominanceTexture();
void createTargetTexture();
void createTextures();

void createFramebuffers();
void createBuffers();

void createFrameShader();
void createRepaintShader();
void createScreenShader();
void createShaders();

void getScreenBuffer();
void bindOffScreenBuffer();
void bindOnScreenBuffer();

void renderFrame();
void renderRepaint();
void renderScreen();

void read();

void left();
void right();
void reset();

///////////////////////////////////////////////////////////////////////////////

void convertYCrCbtoRGB(float y, float cr, float cb, float &r, float &g, float &b);
void convertYCrCbtoHSL(float y, float cr, float cb, float &h, float &s, float &l);
void convertRGBtoYCrCb(float r, float g, float b, float &y, float &cr, float &cb);
void convertRGBtoHSL(float r, float g, float b, float &h, float &s, float &l);
void convertHSLtoYCrCb(float h, float s, float l, float &y, float &cr, float &cb);
void convertHSLtoRGB(float h, float s, float l, float &r, float &g, float &b);


#ifdef __cplusplus
}
#endif


#endif
