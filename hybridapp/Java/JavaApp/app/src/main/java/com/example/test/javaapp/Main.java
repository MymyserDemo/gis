package com.example.test.javaapp;

import android.app.Application;
import android.util.Log;

public class Main extends Application {

    static {
        System.loadLibrary("BridgingJava");
    }

    @Override
    public void onCreate() {

        super.onCreate();

        hbCreate();
        hbSetLogger();
        hbSetError();
        hbInitilaize();

        // エラーログを出力する
        hbSetErrorCode("MainView", (char)1);

    }

    @Override
    public void onTerminate() {

        hbFinalize();

        super.onTerminate();
    }

    /**
     * ログ出力コールバック関数.
     * @param functionName ログを出力したクラス名+関数名.
     * @param message ログに出力するメッセージ.
     */
    public void loggerCallback(String functionName, String message) {
        Log.d("TEST", functionName + ":" + message);
    }

    /**
     * エラー出力コールバック関数.
     * @param className エラーの発生したクラスの名称.
     * @param errorCode エラーコード.
     */
    public void errorCallback(String className, int errorCode) {
        Log.e("ERROR", className + ":" + errorCode);
    }

    // Cとのインターフェース定義
    public native void hbCreate();
    public native void hbInitilaize();
    public native void hbFinalize();
    public native void hbSetLogger();
    public native void hbSetError();
    public native void hbSetErrorCode(String className, char errorCode);
}
