/**
* Android Java用アプリケーションメイン.
*/
package com.example.test.javaapp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

  // Used to load the 'native-lib' library on application startup.
  static {
      System.loadLibrary("native-lib");
  }

  /**
  * onCreateでHybrid側メインコントローラーを初期化します.
  */
  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    setContentView(R.layout.activity_main);

    create();

    setLogger();

    initilaize();
  }

  /**
  * onStopでHybrid側メインコントローラーを破棄します.
  */
  @Override
  protected  void onStop() {
    finalize();
    super.onStop();
  }

  public void callback(String message) {
    Log.d("TEST", message);
  }

  // Cとのインターフェース定義
  public native void create();
  public native void initilaize();
  public native void finalize();
  public native void setLogger();
}

