/// @file	Shaders.h
/// @brief	Defines shaders' sources
/// @author	Baguette Apps - Rémi Chaignon
/// @date	24/09/2011
///

#ifndef __SHADERS_H__
#define __SHADERS_H__


// FRAME //////////////////////////////////////////////////////////////////////

const char frameVertexShaderSource[] = \
	"attribute vec4 a_position;\
	attribute vec2 a_texCoord;\
	\
	varying vec2 v_texCoord;\
	\
	void main()\
	{\
		gl_Position = a_position;\
		v_texCoord  = a_texCoord;\
	}";

const char frameFragmentShaderSource[] = \
	"precision highp float;\
	\
	uniform lowp sampler2D s_luminance;\
	uniform lowp sampler2D s_chrominance;\
	\
	varying vec2 v_texCoord;\
	\
	void main()\
	{\
		vec4 luminance = texture2D(s_luminance, v_texCoord);\
		vec4 chrominance = texture2D(s_chrominance, v_texCoord);\
		vec3 color = vec3(luminance.r * 1.1643828125, chrominance.r, chrominance.a);\
	\
		gl_FragColor = vec4(	color.r + 1.59602734375 * color.g - (222.921 / 255.0),\
								color.r - 0.39176171875 * color.b - 0.81296875 * color.g + (135.576 / 255.0),\
								color.r + 2.017234375 * color.b - (276.836 / 255.0),\
								1.0);\
	}";


// REPAINT ////////////////////////////////////////////////////////////////////

const char repaintVertexShaderSource[] = \
	"attribute vec4 a_position;\
	attribute vec2 a_texCoord;\
	\
	varying vec2 v_texCoord;\
	\
	void main()\
	{\
		gl_Position = a_position;\
		v_texCoord  = a_texCoord;\
	}";

const char repaintFragmentShaderSource[] = \
	"precision highp float;\
	\
	uniform lowp sampler2D s_luminance;\
	uniform lowp sampler2D s_chrominance;\
	\
	uniform vec2 u_in;\
	uniform float u_out;\
	\
	varying vec2 v_texCoord;\
	\
	void main()\
	{\
		vec4 luminance = texture2D(s_luminance, v_texCoord);\
		vec4 chrominance = texture2D(s_chrominance, v_texCoord);\
		vec3 color = vec3(luminance.r * 1.1643828125, chrominance.r, chrominance.a);\
	\
		gl_FragColor = vec4(	color.r + 1.59602734375 * color.g - (222.921 / 255.0),\
								color.r - 0.39176171875 * color.b - 0.81296875 * color.g + (135.576 / 255.0),\
								color.r + 2.017234375 * color.b - (276.836 / 255.0),\
								1.0);\
	}";


// SCREEN /////////////////////////////////////////////////////////////////////

const char screenVertexShaderSource[] = \
	"attribute vec4 a_position;\
	attribute vec2 a_texCoord;\
	\
	varying vec2 v_texCoord;\
	\
	void main()\
	{\
		gl_Position = a_position;\
		v_texCoord  = a_texCoord;\
	}";

const char screenFragmentShaderSource[] = \
	"precision highp float;\
	\
	uniform lowp sampler2D s_texture;\
	\
	varying vec2 v_texCoord;\
	\
	void main()\
	{\
		gl_FragColor = texture2D(s_texture, v_texCoord);\
	}";


// ARROW //////////////////////////////////////////////////////////////////////

const char arrowVertexShaderSource[] = \
	"attribute vec4 a_position;\
	attribute vec2 a_texCoord;\
	\
	varying vec2 v_texCoord;\
	\
	void main()\
	{\
		gl_Position = a_position;\
		v_texCoord  = a_texCoord;\
	}";

const char arrowFragmentShaderSource[] = \
	"uniform lowp sampler2D s_texture;\
	uniform vec3 u_in;\
	\
	varying vec2 v_texCoord;\
	\
	void main()\
	{\
	//	vec4 vRGBA = texture2D(s_texture, v_texCoord);\
	\
	//	if(vRGBA.a == 1.0 && vRGBA.r == 1.0)\
	//	{\
	//		gl_FragColor = vec4(u_in, 1.0);\
	//		return;\
	//	}\
	\
	//	gl_FragColor = vRGBA;\
		gl_FragColor = vec4(u_in, 1.0);\
	}";


#endif
