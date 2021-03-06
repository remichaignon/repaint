/// @file	Objects.h
/// @brief	Defines objects' vertices
/// @author	Baguette Apps - Rémi Chaignon
///

#ifndef __OBJECTS_H__
#define __OBJECTS_H__


#define VERTEX_BOTTOM_LEFT_X	0
#define VERTEX_BOTTOM_LEFT_Y	1
#define VERTEX_BOTTOM_LEFT_Z	2
#define VERTEX_BOTTOM_LEFT_U	3
#define VERTEX_BOTTOM_LEFT_V	4

#define VERTEX_BOTTOM_RIGHT_X	5
#define VERTEX_BOTTOM_RIGHT_Y	6
#define VERTEX_BOTTOM_RIGHT_Z	7
#define VERTEX_BOTTOM_RIGHT_U	8
#define VERTEX_BOTTOM_RIGHT_V	9

#define VERTEX_TOP_RIGHT_X		10
#define VERTEX_TOP_RIGHT_Y		11
#define VERTEX_TOP_RIGHT_Z		12
#define VERTEX_TOP_RIGHT_U		13
#define VERTEX_TOP_RIGHT_V		14

#define VERTEX_TOP_LEFT_X		15
#define VERTEX_TOP_LEFT_Y		16
#define VERTEX_TOP_LEFT_Z		17
#define VERTEX_TOP_LEFT_U		18
#define VERTEX_TOP_LEFT_V		19


// SIMPLE /////////////////////////////////////////////////////////////////////

#define SIMPLE_VERTICES_STRIDE	5 * sizeof(GLfloat)
#define SIMPLE_VERTICES_OFFSET	&simpleVertices[VERTEX_BOTTOM_LEFT_X]
#define SIMPLE_TEXCOORD_OFFSET	&simpleVertices[VERTEX_BOTTOM_LEFT_U]

GLfloat simpleVertices[20] =
{
// VERTEX_BOTTOM_LEFT_X
// VERTEX_BOTTOM_LEFT_Y
// VERTEX_BOTTOM_LEFT_Z
// VERTEX_BOTTOM_LEFT_U
// VERTEX_BOTTOM_LEFT_V

// VERTEX_BOTTOM_RIGHT_X
// VERTEX_BOTTOM_RIGHT_Y
// VERTEX_BOTTOM_RIGHT_Z
// VERTEX_BOTTOM_RIGHT_U
// VERTEX_BOTTOM_RIGHT_V

// VERTEX_TOP_RIGHT_X
// VERTEX_TOP_RIGHT_Y
// VERTEX_TOP_RIGHT_Z
// VERTEX_TOP_RIGHT_U
// VERTEX_TOP_RIGHT_V

// VERTEX_TOP_LEFT_X
// VERTEX_TOP_LEFT_Y
// VERTEX_TOP_LEFT_Z
// VERTEX_TOP_LEFT_U
// VERTEX_TOP_LEFT_V
};
const GLubyte simpleIndices[6] = { 0, 1, 2,	2, 3, 0 };


// FRAME //////////////////////////////////////////////////////////////////////

#define FRAME_VERTICES_STRIDE	5 * sizeof(GLfloat)
#define FRAME_VERTICES_OFFSET	&frameVertices[VERTEX_BOTTOM_LEFT_X]
#define FRAME_TEXCOORD_OFFSET	&frameVertices[VERTEX_BOTTOM_LEFT_U]

GLfloat frameVertices[20];
const GLubyte frameIndices[6] = { 0, 1, 2,	2, 3, 0 };


// SCREEN /////////////////////////////////////////////////////////////////////

#define SCREEN_VERTICES_STRIDE	5 * sizeof(GLfloat)
#define SCREEN_VERTICES_OFFSET	&screenVertices[VERTEX_BOTTOM_LEFT_X]
#define SCREEN_TEXCOORD_OFFSET	&screenVertices[VERTEX_BOTTOM_LEFT_U]

GLfloat screenVertices[20];
const GLubyte screenIndices[6] = { 0, 1, 2,	 2, 3, 0 };


// ARROW //////////////////////////////////////////////////////////////////////

GLfloat arrowVertices[] = {};
const GLubyte arrowIndices[] = {};



#endif
