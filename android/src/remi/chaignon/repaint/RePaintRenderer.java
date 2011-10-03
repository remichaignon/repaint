// @file	RePaintRenderer.java
// @brief	...
// @author	Baguette Apps - Rémi Chaignon
// @date	08/04/2011
//

package remi.chaignon.repaint;


//IMPORTS ////////////////////////////

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;
//import android.util.Log;

import remi.chaignon.repaint.NativeInterface;


//CLASS //////////////////////////////

// Custom OpenGL renderer
//
public class RePaintRenderer implements GLSurfaceView.Renderer
{

	// DATA ///////////////////////////

//	private static final String DEBUG_TAG = "BAGUETTE";

	private EGL10 egl = null;


	// CONSTRUCTORS ///////////////////

	//
	//
	public RePaintRenderer()
	{
//		Log.v(DEBUG_TAG, "[RePaintRenderer::RePaintRenderer]");
	}



	// EVENTS /////////////////////////

	// The surface has been created
	// @param	_unused	...
	// @param	_unused2	...
	//
	//@Override
	public void onSurfaceCreated(GL10 _unused, EGLConfig _unused2)
	{
//		Log.v(DEBUG_TAG, "[RePaintRenderer::onSurfaceCreated]");		
	}


	// The surface has been changed
	// @param	_unused		...
	// @param	_iWidth		New width of the surface
	// @param	_iHeight	New height of the surface
	//
	//@Override
	public void onSurfaceChanged(GL10 _unused, int _iWidth, int _iHeight)
	{
//		Log.v(DEBUG_TAG, "[RePaintRenderer::onSurfaceChanged]");

		egl = (EGL10)EGLContext.getEGL();
	}


	// Draw call
	// @param _unused	...
	//
	//@Override
	public void onDrawFrame(GL10 _unused)
	{
//		Log.v(DEBUG_TAG, "[RePaintRenderer::onDrawFrame]");

		// Pass the draw call the native interface
		NativeInterface.render();
		egl.eglWaitGL();
	}

}
