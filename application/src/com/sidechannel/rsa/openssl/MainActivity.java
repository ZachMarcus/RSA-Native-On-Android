package com.sidechannel.rsa.openssl;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import com.sidechannel.rsa.openssl.R;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

	static {
		System.loadLibrary("crypto-rsa");
	}
    private final String TAG="Crypto-RSA";
    //private int[] mChoice;
    private CheckBox rsa, rsaOpenCL, RSAGMP;
    private Button runbutton;
    private TextView tv;

	public native String RSAFromJNI(boolean rsaChoice, boolean rsaOpenCLChoice, boolean runRSAGMPChoice, int numberOfTimes);
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		addListenerOnRunButton();
		//Context context = getApplicationContext();
		//CharSequence text = RSAFromJNI();
		//int duration = Toast.LENGTH_LONG;
		//Toast toast = Toast.makeText(context,  text,  duration);
		//toast.show();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	public void addListenerOnRunButton() {
	     runbutton = (Button) findViewById(R.id.runbutton);
	     
	     runbutton.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				//delete the next several lines of this
				/*Context context = getApplicationContext();
				CharSequence text = (CharSequence)(GetAPKPath());
				int duration = Toast.LENGTH_LONG;
				Toast toast = Toast.makeText(context,  text,  duration);
				toast.show();*/
				startTests();
				
			}
	     });
	}	
	
	private void copyFile(final String f) {
		InputStream in;
		try {
			//creates the output data
			in = getAssets().open(f);
			final File of = new File(getDir("execdir",MODE_PRIVATE), f);

			final OutputStream out = new FileOutputStream(of);

			final byte b[] = new byte[65535];
			int sz = 0;
			while ((sz = in.read(b)) > 0) {
				out.write(b, 0, sz);
			}
			in.close();
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void startTests() {
		
		Context context = getApplicationContext();
		CharSequence text = "Proceeding to run...";
		int duration = Toast.LENGTH_LONG;
		Toast toast = Toast.makeText(context,  text,  duration);
		toast.show();
    	tv = (TextView) findViewById(R.id.tv);
    	
    	//create checkboxes for each option
    	rsa = (CheckBox) findViewById(R.id.rsa);
    	rsaOpenCL = (CheckBox) findViewById(R.id.rsaOpenCL);
    	RSAGMP = (CheckBox) findViewById(R.id.RSAGMP);
    	
    	boolean rsaChoice = false;
        boolean rsaOpenCLChoice = false;
        boolean runRSAGMPChoice = false;
    	if (rsa.isChecked()) {
    		rsaChoice = true;
    	} 
    	if (rsaOpenCL.isChecked()) {
    		rsaOpenCLChoice = true;
    	}
    	if (RSAGMP.isChecked()) {
    		runRSAGMPChoice = true;
    	}
    	
    	EditText myEditText = (EditText) findViewById(R.id.numberOfTimes);
    	int numberOfTimes = Integer.parseInt(myEditText.getText().toString());

    	try {
            //tv.setText("Running Tests...");
			String returnValue = RSAFromJNI(rsaChoice, rsaOpenCLChoice, runRSAGMPChoice, numberOfTimes);
			text = (CharSequence) returnValue;
			toast = Toast.makeText(context,  text,  duration);
			toast.show();
    	} catch(Exception e) {
    		Log.i(TAG, e.getMessage());
    	}
    }
	
	int GetAssetOffset(String filename) {
        int filesize=0;
        try {
            android.content.res.AssetFileDescriptor fd=this.getAssets().openFd(filename);
            filesize=(int)fd.getStartOffset();
        } catch(java.io.IOException e) {}
        return filesize;
    }
    String GetAPKPath() {
        return this.getPackageResourcePath();
    }
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}




