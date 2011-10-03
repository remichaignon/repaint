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
	uniform lowp sampler2D s_frame_luminance;\
	uniform lowp sampler2D s_frame_chrominance;\
	\
	uniform vec2 u_in;\
	uniform float u_out;\
	\
	varying vec2 v_texCoord;\
	\
	\
	vec3 convertYCrCbtoRGB(vec3 _vYCrCb)\
	{\
		return vec3(	_vYCrCb.r + 1.59602734375 * _vYCrCb.g - (222.921 / 255.0),\
						_vYCrCb.r - 0.39176171875 * _vYCrCb.b - 0.81296875 * _vYCrCb.g + (135.576 / 255.0),\
						_vYCrCb.r + 2.017234375 * _vYCrCb.b - (276.836 / 255.0));\
	}\
	\
	vec3 convertRGBtoHSL_2(vec3 _vRGB)\
	{\
		vec3 vHSL = vec3(0.0, 0.0, 0.0);\
	\
		if(_vRGB.r < _vRGB.g)\
		{\
			if(_vRGB.g < _vRGB.b)\
			{\
				/* min = r; */\
				/* max = b; */\
				float fDiff = _vRGB.b - _vRGB.r;\
				vHSL.b = _vRGB.b + _vRGB.r;\
	\
				if(vHSL.b < 1.0)\
				{\
					vHSL.g = fDiff / vHSL.b;\
					vHSL.b /= 2.0;\
				}\
				else\
				{\
					vHSL.g = fDiff / (2.0 - fDiff);\
					vHSL.b /= 2.0;\
				}\
	\
				vHSL.r = (4.0 + ((_vRGB.r - _vRGB.g) / fDiff)) * 60.0;\
				vHSL.r = (vHSL.r < 0.0) ? vHSL.r + 360.0 : vHSL.r;\
				return vHSL;\
			}\
	\
			if(_vRGB.r < _vRGB.b)\
			{\
				/* min = r; */\
				/* max = g; */\
				if(_vRGB.r == _vRGB.g)\
				{\
					return vHSL;\
				}\
	\
				float fDiff = _vRGB.g - _vRGB.r;\
				vHSL.b = _vRGB.g + _vRGB.r;\
	\
				if(vHSL.b < 1.0)\
				{\
					vHSL.g = fDiff / vHSL.b;\
					vHSL.b /= 2.0;\
				}\
				else\
				{\
					vHSL.g = fDiff / (2.0 - fDiff);\
					vHSL.b /= 2.0;\
				}\
	\
				vHSL.r = (2.0 + ((_vRGB.b - _vRGB.r) / fDiff)) * 60.0;\
				vHSL.r = (vHSL.r < 0.0) ? vHSL.r + 360.0 : vHSL.r;\
				return vHSL;\
			}\
	\
			/* min = b; */\
			/* max = g; */\
			if(_vRGB.b == _vRGB.g)\
			{\
				return vHSL;\
			}\
	\
			float fDiff = _vRGB.g - _vRGB.b;\
			vHSL.b = _vRGB.g + _vRGB.b;\
	\
			if(vHSL.b < 1.0)\
			{\
				vHSL.g = fDiff / vHSL.b;\
				vHSL.b /= 2.0;\
			}\
			else\
			{\
				vHSL.g = fDiff / (2.0 - fDiff);\
				vHSL.b /= 2.0;\
			}\
	\
			vHSL.r = (2.0 + ((_vRGB.b - _vRGB.r) / fDiff)) * 60.0;\
			vHSL.r = (vHSL.r < 0.0) ? vHSL.r + 360.0 : vHSL.r;\
			return vHSL;\
		}\
	\
		if(_vRGB.r < _vRGB.b)\
		{\
			/* min = g; */\
			/* max = b; */\
			float fDiff = _vRGB.b - _vRGB.g;\
			vHSL.b = _vRGB.b + _vRGB.g;\
	\
			if(vHSL.b < 1.0)\
			{\
				vHSL.g = fDiff / vHSL.b;\
				vHSL.b /= 2.0;\
			}\
			else\
			{\
				vHSL.g = fDiff / (2.0 - fDiff);\
				vHSL.b /= 2.0;\
			}\
	\
			vHSL.r = (4.0 + ((_vRGB.r - _vRGB.g) / fDiff)) * 60.0;\
			vHSL.r = (vHSL.r < 0.0) ? vHSL.r + 360.0 : vHSL.r;\
			return vHSL;\
		}\
	\
		if(_vRGB.g < _vRGB.b)\
		{\
			/* min = g; */\
			/* max = r; */\
			if(_vRGB.g == _vRGB.r)\
			{\
				return vHSL;\
			}\
	\
			float fDiff = _vRGB.r - _vRGB.g;\
			vHSL.b = _vRGB.r + _vRGB.g;\
	\
			if(vHSL.b < 1.0)\
			{\
				vHSL.g = fDiff / vHSL.b;\
				vHSL.b /= 2.0;\
			}\
			else\
			{\
				vHSL.g = fDiff / (2.0 - fDiff);\
				vHSL.b /= 2.0;\
			}\
	\
			vHSL.r = ((_vRGB.g - _vRGB.b) / fDiff) * 60.0;\
			vHSL.r = (vHSL.r < 0.0) ? vHSL.r + 360.0 : vHSL.r;\
			return vHSL;\
		}\
	\
		/* min = b; */\
		/* max = r; */\
		if(_vRGB.b == _vRGB.r)\
		{\
			return vHSL;\
		}\
	\
		float fDiff = _vRGB.r - _vRGB.b;\
		vHSL.b = _vRGB.r + _vRGB.b;\
	\
		if(vHSL.b < 1.0)\
		{\
			vHSL.g = fDiff / vHSL.b;\
			vHSL.b /= 2.0;\
		}\
		else\
		{\
			vHSL.g = fDiff / (2.0 - fDiff);\
			vHSL.b /= 2.0;\
		}\
	\
		vHSL.r = ((_vRGB.g - _vRGB.b) / fDiff) * 60.0;\
		vHSL.r = (vHSL.r < 0.0) ? vHSL.r + 360.0 : vHSL.r;\
		return vHSL;\
	}\
	\
	\
	vec3 convertRGBtoHSL(vec3 _vRGB)\
	{\
		vec3 vHSL = vec3(0.0, 0.0, 0.0);\
		float fMin = min(min(_vRGB.r, _vRGB.g), _vRGB.b);\
		float fMax = max(max(_vRGB.r, _vRGB.g), _vRGB.b);\
		float fDiff = fMax - fMin;\
	\
		vHSL.b = (fMax + fMin) / 2.0;\
	\
		if(fMin == fMax)\
		{\
			vHSL.r = 0.0;\
			vHSL.g = 0.0;\
			return vHSL;\
		}\
	\
		if(vHSL.b < 0.5)\
		{\
			vHSL.g = fDiff / (fMax + fMin);\
		}\
		else\
		{\
			vHSL.g = fDiff / (2.0 - fDiff);\
		}\
	\
		if(_vRGB.r == fMax)\
		{\
			vHSL.r = (_vRGB.g - _vRGB.b) / fDiff;\
		}\
		else\
		{\
			if(_vRGB.g == fMax)\
			{\
				vHSL.r = 2.0 + ((_vRGB.b - _vRGB.r) / fDiff);\
			}\
			else\
			{\
				vHSL.r = 4.0 + ((_vRGB.r - _vRGB.g) / fDiff);\
			}\
		}\
	\
		vHSL.r *= 60.0;\
		if(vHSL.r < 0.0)\
		{\
			vHSL.r += 360.0;\
		}\
	\
		return vHSL;\
	}\
	\
	vec3 convertHSLtoRGB(vec3 _vHSL)\
	{\
		vec3 vRGB = vec3(0.0, 0.0, 0.0);\
	\
		if(_vHSL.g == 0.0)\
		{\
			vRGB.r = _vHSL.b;\
			vRGB.g = _vHSL.b;\
			vRGB.b = _vHSL.b;\
			return vRGB;\
		}\
	\
		float fTmp1 = 0.0;\
		float fTmp2 = 0.0;\
		float fTmp3 = 0.0;\
	\
		if(_vHSL.b < 0.5)\
		{\
			fTmp2 = _vHSL.b * (1.0 + _vHSL.g);\
		}\
		else\
		{\
			fTmp2 = _vHSL.b + _vHSL.g - (_vHSL.b * _vHSL.g);\
		}\
	\
		fTmp1 = (2.0 * _vHSL.b) - fTmp2;\
	\
		_vHSL.r /= 360.0;\
	\
		/* R */\
		fTmp3 = _vHSL.r + (1.0 / 3.0);\
	\
		if(fTmp3 < 0.0)\
		{\
			fTmp3 += 1.0;\
		}\
		if(fTmp3 > 1.0)\
		{\
			fTmp3 - 1.0;\
		}\
	\
		if((6.0 * fTmp3) < 1.0)\
		{\
			vRGB.r = fTmp1 + ((fTmp2  - fTmp1) * 6.0 * fTmp3);\
		}\
		else\
		{\
			if((2.0 * fTmp3) < 1.0)\
			{\
				vRGB.r = fTmp2;\
			}\
			else\
			{\
				if((3.0 * fTmp3) < 2.0)\
				{\
					vRGB.r = fTmp1 + ((fTmp2 - fTmp1) * ((2.0 / 3.0) - fTmp3) * 6.0);\
				}\
				else\
				{\
					vRGB.r = fTmp1;\
				}\
			}\
		}\
	\
		/* G */\
		fTmp3 = _vHSL.r;\
	\
		if(fTmp3 < 0.0)\
		{\
			fTmp3 += 1.0;\
		}\
		if(fTmp3 > 1.0)\
		{\
			fTmp3 - 1.0;\
		}\
	\
		if((6.0 * fTmp3) < 1.0)\
		{\
			vRGB.g = fTmp1 + ((fTmp2  - fTmp1) * 6.0 * fTmp3);\
		}\
		else\
		{\
			if((2.0 * fTmp3) < 1.0)\
			{\
				vRGB.g = fTmp2;\
			}\
			else\
			{\
				if((3.0 * fTmp3) < 2.0)\
				{\
					vRGB.g = fTmp1 + ((fTmp2 - fTmp1) * ((2.0 / 3.0) - fTmp3) * 6.0);\
				}\
				else\
				{\
					vRGB.g = fTmp1;\
				}\
			}\
		}\
	\
		/* B */\
		fTmp3 = _vHSL.r - (1.0 / 3.0);\
	\
		if(fTmp3 < 0.0)\
		{\
			fTmp3 += 1.0;\
		}\
		if(fTmp3 > 1.0)\
		{\
			fTmp3 - 1.0;\
		}\
	\
		if((6.0 * fTmp3) < 1.0)\
		{\
			vRGB.b = fTmp1 + ((fTmp2  - fTmp1) * 6.0 * fTmp3);\
		}\
		else\
		{\
			if((2.0 * fTmp3) < 1.0)\
			{\
				vRGB.b = fTmp2;\
			}\
			else\
			{\
				if((3.0 * fTmp3) < 2.0)\
				{\
					vRGB.b = fTmp1 + ((fTmp2 - fTmp1) * ((2.0 / 3.0) - fTmp3) * 6.0);\
				}\
				else\
				{\
					vRGB.b = fTmp1;\
				}\
			}\
		}\
	\
		return vRGB;\
	}\
	\
	\
	void main()\
	{\
		vec4 vLuminance = texture2D(s_frame_luminance, v_texCoord);\
		vec4 vChrominance = texture2D(s_frame_chrominance, v_texCoord);\
	\
		/* Convert YCrCb to RGB */\
		vec3 vRGB = convertYCrCbtoRGB(vec3(vLuminance.r * 1.1643828125, vChrominance.r, vChrominance.a));\
	\
		/* Convert RGB to HSL */\
		vec3 vHSL = convertRGBtoHSL(vRGB);\
	\
		/* Compare HSL to u_in with u_in.a as tolerance value */\
		if(u_in.r < u_in.g)\
		{\
			if((vHSL.r < u_in.r) || (vHSL.r > u_in.g))\
			{\
				/* If do not match, set color to RGB and return */\
				gl_FragColor = vec4(vRGB.r, vRGB.g, vRGB.b, 1.0);\
				return;\
			}\
		}\
		else\
		{\
			if((vHSL.r < u_in.r) && (vHSL.r > u_in.g))\
			{\
				/* If do not match, set color to RGB and return */\
				gl_FragColor = vec4(vRGB.r, vRGB.g, vRGB.b, 1.0);\
				return;\
			}\
		}\
	\
		/* If do match, replace HSL by u_out */\
		vHSL = vec3(u_out, vHSL.g, vHSL.b);\
	\
		/* Convert HSL to RGB */\
		vRGB = convertHSLtoRGB(vHSL);\
	\
		/* Set color */\
		gl_FragColor = vec4(vRGB.r, vRGB.g, vRGB.b, 1.0);\
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
