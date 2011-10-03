// @file	RePaintSurface.java
// @brief	...
// @author	Baguette Apps - Rémi Chaignon
// @date	08/04/2011
//

package remi.chaignon.repaint;


//IMPORTS ////////////////////////////

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.content.Context;
import android.graphics.ImageFormat;
import android.graphics.PixelFormat;
import android.hardware.Camera;
import android.hardware.Camera.Parameters;
import android.hardware.Camera.Size;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
//import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;

import remi.chaignon.repaint.ContextFactory;
import remi.chaignon.repaint.ConfigChooser;
import remi.chaignon.repaint.WindowSurfaceFactory;
import remi.chaignon.repaint.RePaintRenderer;
import remi.chaignon.repaint.NativeInterface;
import remi.chaignon.repaint.R;


//CLASS //////////////////////////////

// Custom OpenGL surface
//
public class RePaintSurface extends GLSurfaceView implements Camera.PreviewCallback
{

	// DATA ///////////////////////////

//	private static final String DEBUG_TAG = "BAGUETTE";

	private static final int TOUCH_AREA_WIDTH = 30;
	private static final int TOUCH_AREA_HEIGHT = 30;

	private Context context = null;
	private RePaintRenderer renderer = null;

	private int surfaceWidth = -1;
	private int surfaceHeight = -1;

	// Camera
	private Camera camera = null;
	private byte[] buffer = null;
	private int bufferWidth = -1;
	private int bufferHeight = -1;
	private int frameWidth = -1;
	private int frameHeight = -1;

	private String cachePath = null;
	private int touchX = -1;
	private int touchY = -1;

	private boolean isInitialized = false;
	private boolean isRepainting = false;



	// CONSTRUCTORS ///////////////////

	// Constructor
	// @param	_context	Activity's context
	//
	public RePaintSurface(Context _context)
	{
		super(_context);
//		Log.v(DEBUG_TAG, "[RePaintSurface::RePaintSurface]");

		//
		context = _context;

		//
		setDebugFlags(DEBUG_CHECK_GL_ERROR | DEBUG_LOG_GL_CALLS);

		// We need to choose an EGLConfig that matches the format of our surface exactly
		this.getHolder().setFormat(PixelFormat.RGBA_8888);
		setEGLConfigChooser(new ConfigChooser(8, 8, 8, 8, 0, 0));

		//
		setEGLWindowSurfaceFactory(new WindowSurfaceFactory());

		// Setup the context factory for 2.0 rendering
		setEGLContextFactory(new ContextFactory());

		// Set the capture renderer
		renderer = new RePaintRenderer();
		setRenderer(renderer);
		setRenderMode(RENDERMODE_WHEN_DIRTY);
	}



	// EVENTS /////////////////////////

	// ...
	//
	@Override
	public void onResume()
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::onResume]");

		if(isInitialized)
		{
			camera.startPreview();
		}
	}


	// ...
	//
	@Override
	public void onPause()
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::onPause]");

		if(isInitialized)
		{
			camera.stopPreview();
		}
	}


	// ...
	// @param _surfaceHolder	...
	//
	@Override
	public void surfaceCreated(SurfaceHolder _surfaceHolder)
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::surfaceCreated]");

		super.surfaceCreated(_surfaceHolder);
	}


	// ...
	// @param _surfaceHolder	...
	// @param _iFormat			...
	// @param _iWidth			...
	// @param _iHeight			...
	//
	@Override
	public void surfaceChanged(SurfaceHolder _surfaceHolder, int _format, int _width, int _height)
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::surfaceChanged]");

		super.surfaceChanged(_surfaceHolder, _format, _width, _height);
		surfaceWidth = _width;
		surfaceHeight = _height;

		// Ready for OpenGL !!!
		this.queueEvent(
				new Runnable()
				{
					//@Override
					public void run()
					{
						initialize();
					}
				});
	}


	// ...
	// @param _surfaceHolder	...
	//
	@Override
	public void surfaceDestroyed(SurfaceHolder _surfaceHolder)
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::surfaceDestroyed]");

		super.surfaceDestroyed(_surfaceHolder);
		NativeInterface.destroy();
	}


	// A frame from the camera is available
	// @param	_acBuffer	Buffer that holds the frame
	// @param	_camera		Camera from which the frame was captured
	//
	//@Override
	public void onPreviewFrame(byte[] _buffer, Camera _camera)
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::onPreviewFrame]");

		// Pass the buffer to the native interface and re-use the buffer
		this.queueEvent(previewHandler);
	}

	// ...
	//
	private Runnable previewHandler = new Runnable()
	{
	    //@Override
	    public void run()
	    {
	    	if(!isInitialized)
	    	{
				camera.addCallbackBuffer(buffer);
	    		return;
	    	}
	    
			// Update the camera's textures
			NativeInterface.update();
			camera.addCallbackBuffer(buffer);
			requestRender();
	    }
	};


	//
	// @param _motionEvent	...
	// @return ...
	//
	@Override
	public boolean onTouchEvent(MotionEvent _motionEvent)
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::onTouchEvent]");

		if(_motionEvent.getAction() == MotionEvent.ACTION_UP)
		{
			if(isRepainting)
			{
				if((int)_motionEvent.getY() > (int)(surfaceHeight * 0.75f))
				{
					if((int)_motionEvent.getX() < (surfaceWidth / 2))
					{
						NativeInterface.left();
					}
					else
					{
						NativeInterface.right();
					}
				}
			}
			else
			{
				touchX = (int)_motionEvent.getX();
				touchY = (int)_motionEvent.getY();

				this.queueEvent(new Runnable()
				{
					//@Override
					public void run()
					{
						NativeInterface.touch(touchX, touchY, TOUCH_AREA_WIDTH, TOUCH_AREA_HEIGHT);
					}
				});

				isRepainting = true;
			}
		}

		// Sleep the UI thread
		try
		{
			Thread.sleep(16);
		}
		catch(InterruptedException _exception)
		{
			_exception.printStackTrace();
		}

		return true;
	}


	//
	//
	public void onBackPressed()
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::onBackPressed]");

		// Pass the back event to the native interface
		if(isRepainting)
		{
			NativeInterface.reset();
			isRepainting = false;
		}
	}



	// FUNCTIONS //////////////////////

	// ...
	//
	public void initialize()
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::initialize]");

		initializeOpenGL();
		initializeCache();
		initializeCamera();

		NativeInterface.initialize(surfaceWidth, surfaceHeight, frameWidth, frameHeight, bufferWidth, bufferHeight, buffer, context.getCacheDir().getAbsolutePath());

		isInitialized = true;
	}


	// ...
	//
	public void initializeOpenGL()
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::initializeOpenGL]");

//		Log.d(DEBUG_TAG, "[RePaintSurface::initializeOpenGL] GL_VERSION = " + GLES20.glGetString(GLES20.GL_VERSION));
//		Log.d(DEBUG_TAG, "[RePaintSurface::initializeOpenGL] GL_VENDOR = " + GLES20.glGetString(GLES20.GL_VENDOR));
//		Log.d(DEBUG_TAG, "[RePaintSurface::initializeOpenGL] GL_RENDERER = " + GLES20.glGetString(GLES20.GL_RENDERER));
//		Log.d(DEBUG_TAG, "[RePaintSurface::initializeOpenGL] GL_EXTENSIONS = " + GLES20.glGetString(GLES20.GL_EXTENSIONS));

//		Log.d(DEBUG_TAG, "[RePaintSurface::initializeOpenGL] Viewport(0, 0, " + m_iSurfaceWidth + ", " + m_iSurfaceHeight + ")");

		GLES20.glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
		GLES20.glViewport(0, 0, surfaceWidth, surfaceHeight);
//		checkGlError("[RePaintSurface::initializeOpenGL] glViewport");
	}


	// ...
	//
	public void initializeCamera()
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::initializeCamera]");

		// Create the camera
		camera = Camera.open();

//		if(m_camera == null)
//		{
//			Log.e(DEBUG_TAG, "[RePaintSurface::initializeCamera] Could not find back-facing camera");
//		}

        try
		{
        	// Get the camera's parameters
			Parameters cameraParameters = camera.getParameters();

			// Get the camera's size
			Size cameraSize = cameraParameters.getPreviewSize();
			frameWidth = cameraSize.width;
			frameHeight = cameraSize.height;
			bufferWidth = frameWidth;
			bufferHeight = (int)(frameHeight * 1.5f);

			// Get the camera's image format
			int imageFormat = cameraParameters.getPreviewFormat();
/*			switch(imageFormat)
			{
				case ImageFormat.JPEG:		Log.d(DEBUG_TAG, "[RePaintSurface::initializeCamera] ImageFormat = JPEG");
											break;
				case ImageFormat.NV16:		Log.d(DEBUG_TAG, "[RePaintSurface::initializeCamera] ImageFormat = NV16");
											break;
				case ImageFormat.NV21:		Log.d(DEBUG_TAG, "[RePaintSurface::initializeCamera] ImageFormat = NV21");	// Default (http://developer.android.com/reference/android/hardware/Camera.PreviewCallback.html)
											break;
				case ImageFormat.RGB_565:	Log.d(DEBUG_TAG, "[RePaintSurface::initializeCamera] ImageFormat = RGB_565");
											break;
				case ImageFormat.UNKNOWN:	Log.d(DEBUG_TAG, "[RePaintSurface::initializeCamera] ImageFormat = UNKNOWN");
											break;
				case ImageFormat.YUY2:		Log.d(DEBUG_TAG, "[RePaintSurface::initializeCamera] ImageFormat = YUY2");
											break;
				//case ImageFormat.YV12:	Log.d(DEBUG_TAG, "[RePaintSurface::initializeCamera] ImageFormat = YV12");	// Level 9
				//							break;
				default:					Log.e(DEBUG_TAG, "[RePaintSurface::initializeCamera] ImageFormat Unrecognised");
											break;
			}
*/
			// Get the camera's pixel depth
			int pixelDepth = ImageFormat.getBitsPerPixel(imageFormat);
/*
			if(pixelDepth == -1)
			{
				Log.e(DEBUG_TAG, "[RePaintSurface::initializeCamera] Image format not supported");
			}
*/
			// Create the camera buffer
			buffer = new byte[bufferWidth * bufferHeight * pixelDepth / 8];

			// Setup the camera's callback and buffer
			camera.addCallbackBuffer(buffer);
			camera.setPreviewCallbackWithBuffer(this);
		}
		catch(Exception _exception)
		{
//			Log.e(DEBUG_TAG, "[RePaintSurface::initializeCamera] Failed to get the camera's parameters");
			camera.release();
			camera = null;
			return;
		}

		// Start the camera
		camera.startPreview();
	}


	// ...
	//
	public void destroyCamera()
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::destroyCamera]");

		// Release the camera
		if(camera != null)
		{
	        camera.stopPreview();
			camera.release();
			camera = null;
		}
	}

	// ...
	//
	private void initializeCache()
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::initializeCache]");

		cachePath = context.getCacheDir().getAbsolutePath();

		//cacheFile(R.raw.frame_vsh, "shaders/frame.vsh");
		//cacheFile(R.raw.frame_fsh, "shaders/frame.fsh");
		//cacheFile(R.raw.arrow_vsh, "shaders/arrow.vsh");
		//cacheFile(R.raw.arrow_fsh, "shaders/arrow.fsh");
		//cacheFile(R.raw.screen_vsh, "shaders/screen.vsh");
		//cacheFile(R.raw.screen_fsh, "shaders/screen.fsh");

		//cacheFile(R.drawable.arrow, "images/arrow.png");
	}

	//
	//
	private void cacheFile(int _resourceId, String _assetPath)
	{
//		Log.v(DEBUG_TAG, "[RePaintSurface::cacheFile]");

		try
		{
			// Create cache file
			File file = new File(cachePath, _assetPath);
//			Log.d(DEBUG_TAG, "[RePaintSurface::cacheFile] Name = " + file.getAbsolutePath());

			if(file.exists())
			{
				file.delete();
			}

			try
			{
				File parent = file.getParentFile();
				parent.mkdirs();
				file.createNewFile();
			}
			catch(IOException _exception)
			{
//				Log.e(DEBUG_TAG, "[RePaintSurface::cacheFile] Couldn't create cache file");
				return;
			}

			if(!file.exists())
			{
//				Log.e(DEBUG_TAG, "[RePaintSurface::cacheFile] Didn't create cache file");
				return;
			}
			//file.setWritable(true);	// API9

			InputStream inputStream = context.getResources().openRawResource(_resourceId);
			OutputStream outputStream = new FileOutputStream(file);
			byte bufferStream[] = new byte[1024];
			int length = 0;

			while((length = inputStream.read(bufferStream)) > 0)
			{
				outputStream.write(bufferStream, 0, length);
			}

			outputStream.close();
			inputStream.close();
		}
		catch(IOException _exception)
		{
//			Log.e(DEBUG_TAG, "[RePaintSurface::cacheFile] Couldn't build cache file");
			_exception.printStackTrace();
			return;
		}
	}


	//
	//
//	static void checkGlError(String _sOperation)
//	{
//		for(int iError = GLES20.glGetError(); iError != 0; iError = GLES20.glGetError())
//		{
//			Log.d(DEBUG_TAG, "[RePaintSurface::checkGlError] After " + _sOperation + " glError " + iError);
//		}
//	}

}
