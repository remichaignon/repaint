// @file	ContextFactory.java
// @brief	...
// @author	Baguette Apps - Rémi Chaignon
// @date	08/04/2011
//

package remi.chaignon.repaint;


//IMPORTS ////////////////////////////

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;

import android.opengl.GLSurfaceView;
//import android.util.Log;


//CLASS //////////////////////////////

// ...
//
public class ContextFactory implements GLSurfaceView.EGLContextFactory
{

	// DATA ///////////////////////////

//	private static final String DEBUG_TAG = "BAGUETTE";

	private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;



	// FUNCTIONS //////////////////////

	// ...
	// @param _egl			...
	// @param _display		...
	// @param _eglConfig	...
	//
	//@Override
	public EGLContext createContext(EGL10 _egl, EGLDisplay _display, EGLConfig _eglConfig)
	{
//		Log.v(DEBUG_TAG, "[ContextFactory::createContext]");

		int[] aiAttributeList = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE };

//		checkEglError("[ContextFactory::createContext] Before eglCreateContext", _egl);
		EGLContext context = _egl.eglCreateContext(_display, _eglConfig, EGL10.EGL_NO_CONTEXT, aiAttributeList);
//		checkEglError("[ContextFactory::createContext] After eglCreateContext", _egl);

		return context;
	}


	// ...
	// @param _egl		...
	// @param _display	...
	// @param _context	...
	//
	//@Override
	public void destroyContext(EGL10 _egl, EGLDisplay _display, EGLContext _context)
	{
//		Log.v(DEBUG_TAG, "[ContextFactory::destroyContext]");

//		checkEglError("[ContextFactory::destroyContext] Before eglDestroyContext", _egl);
		_egl.eglDestroyContext(_display, _context);
//		checkEglError("[ContextFactory::destroyContext] After eglDestroyContext", _egl);
	}


	// ...
	// @param _sMessage	...
	// @param _egl		...
	//
//	private static void checkEglError(String _sMessage, EGL10 _egl)
//	{
//		int iError;

//		while((iError = _egl.eglGetError()) != EGL10.EGL_SUCCESS)
//		{
//			Log.e(DEBUG_TAG, String.format("%s: EGL error: 0x%x", _sMessage, iError));
//		}
//	}
}

