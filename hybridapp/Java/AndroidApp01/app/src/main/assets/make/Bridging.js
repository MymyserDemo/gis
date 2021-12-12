mergeInto(LibraryManager.library, {
  // アプリ側のログ表示処理
  loggerCallback: function(className, functionName, message) {
    var logMessage =
      Pointer_stringify(className) + ":" + 
      Pointer_stringify(functionName) + ":" +
      Pointer_stringify(message);    
      logOutput(logMessage);
  },
  // アプリ側のエラー表示処理
  errorCallback: function(className, errorCode) {
    var errorMessage = 
      "Error:" + 
      Pointer_stringify(className) + ":" + 
      errorCode.toString();
      logOutput(errorMessage);
  },
});

