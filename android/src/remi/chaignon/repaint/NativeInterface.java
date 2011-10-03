// @file	NativeInterface.java
// @brief	...
// @author	Baguette Apps - Rémi Chaignon
// @date	08/04/2011
//

package remi.chaignon.repaint;


//CLASS //////////////////////////////

//
//
public class NativeInterface
{
	
	// LIBRARY ////////////////////////

	// Load the native interface library
	static
	{
		System.loadLibrary("repaint");
	}



	// FUNCTIONS //////////////////////

	//
	//
	static native void initialize(int surfaceWidth, int surfaceHeight, int frameWidth, int frameHeight, int bufferWidth, int bufferHeight, byte[] cameraBuffer, String assetPath);

	//
	//
	static native void update();

	//
	//
	static native void render();

	//
	//
	static native void touch(int originX, int originY, int width, int height);

	//
	//
	static native void left();

	//
	//
	static native void right();

	//
	//
	static native void reset();

	//
	//
	static native void destroy();
	
}
