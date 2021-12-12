/**
* アプリ側のJavaとHybrid側のC++を結合する.
*/
#include <jni.h>
#include <string>

#include "MainController.h"

JNIEnv* _env;
jobject _obj;
jmethodID loggerFunc;
jmethodID errorFunc;
// Hybrid側メインコントローラー
MainController *mainController;

/**
* Hybrid側内部から呼ばれるログ出力コールバック関数.
*/
void
setLoggerFunction(LoggerArgument loggerArgument) {
  _env->CallVoidMethod(
          _obj,
          loggerFunc,
          _env->NewStringUTF(loggerArgument.functionName),
          _env->NewStringUTF(loggerArgument.message)
  );
};

/**
* Hybrid側内部から呼ばれるエラー出力コールバック関数.
*/
void
setErrorFunction(ErrorArgument errorArgument) {
  _env->CallVoidMethod(
          _obj,
          errorFunc,
          _env->NewStringUTF(errorArgument.className),
          errorArgument.errorCode
  );
};

/**
 * CSVファイルロード完了.
 * CSVファイルがロードされた後にハイブリッド側のコールバックを実行します.
 * @param data ロードデータ
 * @param loader ロードデータ情報
 */
void bridgingLoadCsvComplete(char *data, CsvLoader loader) {
  // Hybrid側コールバック
  loader.csvLoaderCallback(data, loader);
  // CSVファイルロードコンポーネント削除
  delete loader.getInstance();
}

/**
 * Hybrid側から呼ばれるCSVファイルロード開始.
 */
void CsvLoader::bridgingLoadCsv() {
}

/**
 * Hybrid側から呼ばれるアプリ側のデータリストタイトル行追加.
 * @param data タイトルデータ
 */
void bridgingDataListAddHeader(char *data) {
}

/**
 * Hybrid側から呼ばれるアプリ側のデータリスト行データ追加.
 * @param data 行データ
 */
void bridgingDataListAddData(char *data) {
}

/**
 * Hybrid側から呼ばれるアプリ側のオプション1表示.
 * @param data 行データ
 */
void bridgingOption1(char *data) {
}

/**
 * Hybrid側から呼ばれるアプリ側のオプション2表示.
 * @param data 行データ
 */
void bridgingOption2(char *data) {
}

/**
 * Hybrid側から呼ばれるアプリ側のオプション3表示.
 * @param data 行データ
 */
void bridgingOption3(char *data) {
}

/**
* Hybrid側から呼ばれるアプリ側のポイント表示.
* @param data ポイントデータ
*/
void bridgingPutPoint(char *data, size_t layerNo) {
}

/**
 * Hybrid側から呼ばれるアプリ側のライン表示.
 * @param data ラインデータ
 */
void bridgingPutLine(char *data, size_t layerNo) {
}

/**
 * Hybrid側から呼ばれるアプリ側のGeoJson表示.
 * @param data GeoJsonファイルパス
 */
void bridgingPutGeoJson(const char *data, size_t layerNo) {
}

/**
* Java側からCを介してHybrid側のC++のメソッドを呼び出します.
*/
extern "C" {
  void Java_com_example_test_javaapp_Main_hbCreate(JNIEnv *env, jobject) {
    mainController = new MainController();
  }

  void Java_com_example_test_javaapp_Main_hbInitilaize(JNIEnv *env, jobject) {
    if(mainController == NULL) {
      mainController = new MainController();
    }
    else {
      mainController->initialize();
    }
  }

  void Java_com_example_test_javaapp_Main_hbFinalize(JNIEnv *env, jobject) {
    if(mainController == NULL) {
      return;
    }
    mainController->finalize();
    mainController = NULL;
  }

  /**
  * Hybrid側メインコントローラーにログ出力コールバック関数を設定します.
  */
  void Java_com_example_test_javaapp_Main_hbSetLogger(JNIEnv* env, jobject obj) {
    if(mainController == NULL) {
      return;
    }
    mainController->setLogger(setLoggerFunction);
    _env = env;
    // Hybrid側内部から呼ばれるコールバック関数はスレッドが異なるためNewGlobalRefで取得します
    _obj = env->NewGlobalRef(obj);
    jclass jc = env->FindClass("com/example/test/javaapp/Main");
    loggerFunc = env->GetMethodID(
          jc,
          "loggerCallback",
          "(Ljava/lang/String;Ljava/lang/String;)V"
    );
  }

  /**
  * Hybrid側メインコントローラーにエラーログ出力コールバック関数を設定します.
  */
  void Java_com_example_test_javaapp_Main_hbSetError(JNIEnv* env, jobject obj) {
    if(mainController == NULL) {
      return;
    }
    mainController->setError(setErrorFunction);
    _env = env;
    // Hybrid側内部から呼ばれるコールバック関数はスレッドが異なるためNewGlobalRefで取得します
    _obj = env->NewGlobalRef(obj);
    jclass jc = env->FindClass("com/example/test/javaapp/Main");
    errorFunc = env->GetMethodID(
          jc,
          "errorCallback",
          "(Ljava/lang/String;I)V"
    );
  }

  /**
  * Hybrid側メインコントローラーにエラーコードを設定します.
  */
  void Java_com_example_test_javaapp_Main_hbSetErrorCode(JNIEnv *env, jobject, jstring className, jchar errorCode) {
    if(mainController == NULL) {
      return;
    }
    mainController->setErrorCode(env->GetStringUTFChars(className , 0), errorCode);
  }
}
