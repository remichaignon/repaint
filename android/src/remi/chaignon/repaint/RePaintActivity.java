// @file	RePaintActivity.java
// @brief	...
// @author	Baguette Apps - Rémi Chaignon
// @date	08/04/2011
//

package remi.chaignon.repaint;



//IMPORTS ////////////////////////////

import android.app.Activity;
import android.os.Bundle;
//import android.util.Log;
import android.view.Window;
import android.view.WindowManager;

import remi.chaignon.repaint.RePaintSurface;


//CLASS //////////////////////////////

// RePaint activity (main activity launched when the application starts)
//
public class RePaintActivity extends Activity
{

	// DATA ///////////////////////////

//	private static final String DEBUG_TAG = "BAGUETTE";

	private RePaintSurface surface = null;



	// EVENTS /////////////////////////

	// ...
	// @param _savedInstanceState	...
	//
	@Override
	protected void onCreate(Bundle _savedInstanceState)
	{
//		Log.v(DEBUG_TAG, "[RePaintActivity::onCreate]");

		super.onCreate(_savedInstanceState);

		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

		// Create the OpenGL surface
		surface = new RePaintSurface(this);

		// Display the capture surface in the main window
		setContentView(surface);
	}


	// ...
	//
	@Override
	protected void onStart()
	{
//		Log.v(DEBUG_TAG, "[RePaintActivity::onStart]");

		super.onStart();
	}


	// ...
	//
	@Override
	protected void onRestart()
	{
//		Log.v(DEBUG_TAG, "[RePaintActivity::onRestart]");

		super.onRestart();
	}


	// ...
	//
	@Override
	protected void onResume()
	{
//		Log.v(DEBUG_TAG, "[RePaintActivity::onResume]");

		
		super.onResume();
		surface.onResume();
	}


	// ...
	//
	@Override
	protected void onPause()
	{
//		Log.v(DEBUG_TAG, "[RePaintActivity::onPause]");

		super.onPause();
		surface.onPause();

		finish();
	}


	// ...
	//
	@Override
	protected void onStop()
	{
//		Log.v(DEBUG_TAG, "[RePaintActivity::onStop]");

		super.onStop();
	}


	// ...
	//
	@Override
	protected void onDestroy()
	{
//		Log.v(DEBUG_TAG, "[RePaintActivity::onDestroy]");

		super.onDestroy();

		System.exit(0);
	}


	// ...
	// @param _savedInstanceState 	...
	//
	@Override
	protected void onRestoreInstanceState(Bundle _savedInstanceState)
	{
//		Log.v(DEBUG_TAG, "[RePaintActivity::onRestoreInstanceState]");

		super.onRestoreInstanceState(_savedInstanceState);
	}


	// ...
	// @param _outInstaceState 	...
	//
	@Override
	protected void onSaveInstanceState(Bundle _outInstanceState)
	{
//		Log.v(DEBUG_TAG, "[RePaintActivity::onSaveInstanceState]");

		super.onSaveInstanceState(_outInstanceState);
	}


	// ...
	//
	@Override
	public void onBackPressed()
	{
//		Log.v(DEBUG_TAG, "[MainActivity::onBackPressed]");

		surface.onBackPressed();
	}

}
