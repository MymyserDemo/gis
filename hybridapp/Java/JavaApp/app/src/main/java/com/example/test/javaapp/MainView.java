/**
* Android Java用アプリケーションメイン.
*/
package com.example.test.javaapp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import static com.example.test.javaapp.R.id.MainView;

public class MainView extends AppCompatActivity {
  /**
  * アプリ開始.
  */
  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    setContentView(R.layout.activity_main);

    WebView myWebView = (WebView) findViewById(MainView);
    myWebView.setWebViewClient(new WebViewClient());
    myWebView.loadUrl("http://www.appkaihatsu.com/");
  }

  /**
   * onStartでHybrid側メインコントローラーの作成、初期処理を行います.
   */
  @Override
  protected  void onStart() {
    super.onStart();
  }

  /**
   * onStopでHybrid側メインコントローラーの終了処理、破棄を行います.
  */
  @Override
  protected  void onStop() {
    super.onStop();
  }

  /**
   * アプリ終了.
   */
  @Override
  protected  void onDestroy() {
    super.onDestroy();
  }
}

