// @file	ConfigChooser.java
// @brief	...
// @author	Baguette Apps - Rémi Chaignon
// @date	08/04/2011
//

package remi.chaignon.repaint;


//IMPORTS ////////////////////////////

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLDisplay;

import android.opengl.GLSurfaceView;
//import android.util.Log;


//CLASS //////////////////////////////

// ...
//
public class ConfigChooser implements GLSurfaceView.EGLConfigChooser
{

	// DATA ///////////////////////////

//	private static final String DEBUG_TAG = "BAGUETTE";

	protected int m_iRedSize;
	protected int m_iGreenSize;
	protected int m_iBlueSize;
	protected int m_iAlphaSize;
	protected int m_iDepthSize;
	protected int m_iStencilSize;
	private int[] m_aiValue = new int[1];

	// This EGL config specification is used to specify 2.0 rendering. We use a minimum size of 4 bits for red/green/blue, but will perform actual matching in chooseConfig() below
	private static int EGL_OPENGL_ES2_BIT = 4;
	private static int[] m_aiConfigAttributes =
	{
		EGL10.EGL_RED_SIZE, 4,
		EGL10.EGL_GREEN_SIZE, 4,
		EGL10.EGL_BLUE_SIZE, 4,
		EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL10.EGL_NONE
	};



	// FUNCTIONS //////////////////////

	// ...
	// @param _iRedSize		...
	// @param _iGreenSize	...
	// @param _iBlueSize	...
	// @param _iAlphaSize	...
	// @param _iDepthSize	...
	// @param _iStencilSize	...
	//
	public ConfigChooser(int _iRedSize, int _iGreenSize, int _iBlueSize, int _iAlphaSize, int _iDepthSize, int _iStencilSize)
	{
//		Log.v(DEBUG_TAG, "[ConfigChooser::ConfigChooser]");

		m_iRedSize = _iRedSize;
		m_iGreenSize = _iGreenSize;
		m_iBlueSize = _iBlueSize;
		m_iAlphaSize = _iAlphaSize;
		m_iDepthSize = _iDepthSize;
		m_iStencilSize = _iStencilSize;
	}


	// ...
	// @param _egl		...
	// @param _display	...
	//
	//@Override
	public EGLConfig chooseConfig(EGL10 _egl, EGLDisplay _display)
	{
//		Log.v(DEBUG_TAG, "[ConfigChooser::chooseConfig]");

		// Get the number of minimally matching EGL configurations
		int[] iNumOfConfigs = new int[1];
		_egl.eglChooseConfig(_display, m_aiConfigAttributes, null, 0, iNumOfConfigs);

		int iConfigIndex = iNumOfConfigs[0];

		if(iConfigIndex <= 0)
		{
			throw new IllegalArgumentException("[ConfigChooser::chooseConfig] No configs match configSpec");
		}

		// Allocate then read the array of minimally matching EGL configs
		EGLConfig[] aConfigs = new EGLConfig[iConfigIndex];
		_egl.eglChooseConfig(_display, m_aiConfigAttributes, aConfigs, iConfigIndex, iNumOfConfigs);

		//printConfigs(_egl, _display, aConfigs);

		// Get the "best" configuration 
		EGLConfig config = chooseConfig(_egl, _display, aConfigs);
/*
		if(config != null)
		{
			Log.d(DEBUG_TAG, String.format("[ConfigChooser::chooseConfig] Choosen Config:"));
			printConfig(_egl, _display, config);
		}
		else
		{
			Log.d(DEBUG_TAG, String.format("[ConfigChooser::chooseConfig] No matching Config found"));
		}			
*/
		return config;
	}


	// ...
	// @param _egl		...
	// @param _display	...
	// @param _aConfigs	...
	//
	public EGLConfig chooseConfig(EGL10 _egl, EGLDisplay _display, EGLConfig[] _aConfigs)
	{
//		Log.v(DEBUG_TAG, "[ConfigChooser::chooseConfig]");

		for(EGLConfig config : _aConfigs)
		{
			int iDepth = findConfigAttrib(_egl, _display, config, EGL10.EGL_DEPTH_SIZE, 0);
			int iStencil = findConfigAttrib(_egl, _display, config, EGL10.EGL_STENCIL_SIZE, 0);

			// We need at least m_iDepthSize and m_iStencilSize bits
			if((iDepth < m_iDepthSize) || (iStencil < m_iStencilSize))
			{
				continue;
			}

			// We want an *exact* match for red/green/blue/alpha
			int iRed = findConfigAttrib(_egl, _display, config, EGL10.EGL_RED_SIZE, 0);
			int iGreen = findConfigAttrib(_egl, _display, config, EGL10.EGL_GREEN_SIZE, 0);
			int iBlue = findConfigAttrib(_egl, _display, config, EGL10.EGL_BLUE_SIZE, 0);
			int iAlpha = findConfigAttrib(_egl, _display, config, EGL10.EGL_ALPHA_SIZE, 0);

			if((iRed == m_iRedSize) && (iGreen == m_iGreenSize) && (iBlue == m_iBlueSize) && (iAlpha == m_iAlphaSize))
			{
				return config;
			}
		}

		return null;
	}


	// ...
	// @param _egl				...
	// @param _display			...
	// @param _config			...
	// @param _iAttribute		...
	// @param _iDefaultValue	...
	//
	private int findConfigAttrib(EGL10 _egl, EGLDisplay _display, EGLConfig _config, int _iAttribute, int _iDefaultValue)
	{
//		Log.v(DEBUG_TAG, "[ConfigChooser::findConfigAttrib]");

		if(_egl.eglGetConfigAttrib(_display, _config, _iAttribute, m_aiValue))
		{
			return m_aiValue[0];
		}

		return _iDefaultValue;
	}

/*
	// ...
	// @param _egl		...
	// @param _display	...
	// @param _aConfigs	...
	//
	private void printConfigs(EGL10 _egl, EGLDisplay _display, EGLConfig[] _aConfigs)
	{
		Log.v(DEBUG_TAG, "[ConfigChooser::printConfigs]");

		int iNumOfConfigs = _aConfigs.length;
		Log.d(DEBUG_TAG, String.format("[ConfigChooser::printConfigs] %d configurations", iNumOfConfigs));

		for(int i = 0; i < iNumOfConfigs; i++)
		{
			Log.d(DEBUG_TAG, String.format("[ConfigChooser::printConfigs] Configuration %d:\n", i));
			printConfig(_egl, _display, _aConfigs[i]);
		}
	}


	// ...
	// @param _egl				...
	// @param _display			...
	// @param _config			...
	//
	private void printConfig(EGL10 _egl, EGLDisplay _display, EGLConfig _config)
	{
		Log.v(DEBUG_TAG, "[ConfigChooser::printConfig]");

		int[] aiAttributesList =
		{
				EGL10.EGL_BUFFER_SIZE,
				EGL10.EGL_ALPHA_SIZE,
				EGL10.EGL_BLUE_SIZE,
				EGL10.EGL_GREEN_SIZE,
				EGL10.EGL_RED_SIZE,
				EGL10.EGL_DEPTH_SIZE,
				EGL10.EGL_STENCIL_SIZE,
				EGL10.EGL_CONFIG_CAVEAT,
				EGL10.EGL_CONFIG_ID,
				EGL10.EGL_LEVEL,
				EGL10.EGL_MAX_PBUFFER_HEIGHT,
				EGL10.EGL_MAX_PBUFFER_PIXELS,
				EGL10.EGL_MAX_PBUFFER_WIDTH,
				EGL10.EGL_NATIVE_RENDERABLE,
				EGL10.EGL_NATIVE_VISUAL_ID,
				EGL10.EGL_NATIVE_VISUAL_TYPE,
				0x3030, // EGL10.EGL_PRESERVED_RESOURCES,
				EGL10.EGL_SAMPLES,
				EGL10.EGL_SAMPLE_BUFFERS,
				EGL10.EGL_SURFACE_TYPE,
				EGL10.EGL_TRANSPARENT_TYPE,
				EGL10.EGL_TRANSPARENT_RED_VALUE,
				EGL10.EGL_TRANSPARENT_GREEN_VALUE,
				EGL10.EGL_TRANSPARENT_BLUE_VALUE,
				0x3039, // EGL10.EGL_BIND_TO_TEXTURE_RGB,
				0x303A, // EGL10.EGL_BIND_TO_TEXTURE_RGBA,
				0x303B, // EGL10.EGL_MIN_SWAP_INTERVAL,
				0x303C, // EGL10.EGL_MAX_SWAP_INTERVAL,
				EGL10.EGL_LUMINANCE_SIZE,
				EGL10.EGL_ALPHA_MASK_SIZE,
				EGL10.EGL_COLOR_BUFFER_TYPE,
				EGL10.EGL_RENDERABLE_TYPE,
				0x3042 // EGL10.EGL_CONFORMANT
		};

		String[] asNamesList =
		{
				"EGL_BUFFER_SIZE",
				"EGL_ALPHA_SIZE",
				"EGL_BLUE_SIZE",
				"EGL_GREEN_SIZE",
				"EGL_RED_SIZE",
				"EGL_DEPTH_SIZE",
				"EGL_STENCIL_SIZE",
				"EGL_CONFIG_CAVEAT",
				"EGL_CONFIG_ID",
				"EGL_LEVEL",
				"EGL_MAX_PBUFFER_HEIGHT",
				"EGL_MAX_PBUFFER_PIXELS",
				"EGL_MAX_PBUFFER_WIDTH",
				"EGL_NATIVE_RENDERABLE",
				"EGL_NATIVE_VISUAL_ID",
				"EGL_NATIVE_VISUAL_TYPE",
				"EGL_PRESERVED_RESOURCES",
				"EGL_SAMPLES",
				"EGL_SAMPLE_BUFFERS",
				"EGL_SURFACE_TYPE",
				"EGL_TRANSPARENT_TYPE",
				"EGL_TRANSPARENT_RED_VALUE",
				"EGL_TRANSPARENT_GREEN_VALUE",
				"EGL_TRANSPARENT_BLUE_VALUE",
				"EGL_BIND_TO_TEXTURE_RGB",
				"EGL_BIND_TO_TEXTURE_RGBA",
				"EGL_MIN_SWAP_INTERVAL",
				"EGL_MAX_SWAP_INTERVAL",
				"EGL_LUMINANCE_SIZE",
				"EGL_ALPHA_MASK_SIZE",
				"EGL_COLOR_BUFFER_TYPE",
				"EGL_RENDERABLE_TYPE",
				"EGL_CONFORMANT"
		};

		int[] aiValue = new int[1];

		for(int i = 0; i < aiAttributesList.length; i++)
		{
			int iAttribute = aiAttributesList[i];
			String sName = asNamesList[i];

			if(_egl.eglGetConfigAttrib(_display, _config, iAttribute, aiValue))
			{
				Log.d(DEBUG_TAG, String.format("[ConfigChooser::printConfig]  %s: %d\n", sName, aiValue[0]));
			}
			else
			{
				while(_egl.eglGetError() != EGL10.EGL_SUCCESS);
			}
		}
	}
*/
}
