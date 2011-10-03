// @file	WindowSurfaceFactory
// @brief	Defines the creation of a EGL Surface
// @author	Baguette Apps - Rémi Chaignon
// @date	08/04/2011
//

package remi.chaignon.repaint;


//IMPORTS ////////////////////////////

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.egl.EGLSurface;

import android.opengl.GLSurfaceView;
//import android.util.Log;


//CLASS //////////////////////////////

// ...
//
public class WindowSurfaceFactory implements GLSurfaceView.EGLWindowSurfaceFactory
{

	// DATA ///////////////////////////

//	private static final String DEBUG_TAG = "BAGUETTE";



	// FUNCTIONS //////////////////////

	// ...
	// @param	_egl			...
	// @param	_display		...
	// @param	_config			...
	// @param	_nativeWindow	...
	//
	//@Override
	public EGLSurface createWindowSurface(EGL10 _egl, EGLDisplay _display, EGLConfig _config, Object _nativeWindow)
	{
//		Log.v(DEBUG_TAG, "[WindowSurfaceFactory::createWindowSurface]");

//		checkEglError("[WindowSurfaceFactory::destroyContext] Before eglCreateWindowSurface", _egl);
		EGLSurface surface = _egl.eglCreateWindowSurface(_display, _config, _nativeWindow, null);
//		checkEglError("[WindowSurfaceFactory::destroyContext] After eglCreateWindowSurface", _egl);

		return surface;
	}


	// ...
	// @param	_egl		...
	// @param	_display	...
	// @param	_surface	...
	//
	//@Override
	public void destroySurface(EGL10 _egl, EGLDisplay _display, EGLSurface _surface)
	{
//		Log.v(DEBUG_TAG, "[WindowSurfaceFactory::destroySurface]");

//		checkEglError("[WindowSurfaceFactory::destroySurface] Before eglDestroySurface", _egl);
		_egl.eglDestroySurface(_display, _surface);
//		checkEglError("[WindowSurfaceFactory::destroySurface] After eglDestroySurface", _egl);
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
