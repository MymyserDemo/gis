/**
* アプリ側のJavaとHybrid側のC++を結合する.
*/
#include <jni.h>
#include <string>

#include "MainController.h"

JNIEnv* _env;
jobject _obj;
jmethodID func;
// Hybrid側メインコントローラー
MainController *mainController;

/**
* Hybrid側内部から呼ばれるコールバック関数.
*/
void
setLoggerFunction(LoggerArgument loggerArgument) {
  _env->CallVoidMethod(_obj, func, _env->NewStringUTF(loggerArgument.functionName));
};

/**
* Java側からCを介してHybrid側のC++のメソッドを呼び出します.
*/
extern "C" {
  void Java_com_example_test_javaapp_MainActivity_create(JNIEnv *env, jobject) {
    mainController = new MainController();
  }

  void Java_com_example_test_javaapp_MainActivity_initilaize(JNIEnv *env, jobject) {
    mainController->initialize();
  }

  void Java_com_example_test_javaapp_MainActivity_finalize(JNIEnv *env, jobject) {
    mainController->finalize();
  }

  /**
  * Hybrid側メインコントローラーにコールバック関数を設定します.
  */
  void Java_com_example_test_javaapp_MainActivity_setLogger(JNIEnv* env, jobject obj) {

    mainController->setLogger(setLoggerFunction);
    _env = env;
    // Hybrid側内部から呼ばれるコールバック関数はスレッドが異なるためNewGlobalRefで取得します
    _obj = env->NewGlobalRef(obj);
    jclass jc = env->FindClass("com/example/test/javaapp/MainActivity");
    func = env->GetMethodID(
          jc,
          "callback",
          "(Ljava/lang/String;)V"
    );
  }
}
