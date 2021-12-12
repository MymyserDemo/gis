/**
* iOS Swift用アプリケーションメイン.
*/
import UIKit
import Foundation

@UIApplicationMain
class Main: UIResponder, UIApplicationDelegate {

  var window: UIWindow?
  var mainView: MainView = MainView()

  func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {

    self.window = UIWindow(frame: UIScreen.main.bounds)
    self.window?.backgroundColor = UIColor.white
    self.window?.makeKeyAndVisible()
    self.window?.rootViewController = self.mainView
    
    return true
  }
    
  func applicationWillResignActive(_ application: UIApplication) {
  }

  func applicationDidEnterBackground(_ application: UIApplication) {
    // ホームボタン押下でバックグラウンド
    mainControllerFinalize()
  }

  func applicationWillEnterForeground(_ application: UIApplication) {
  }

  func applicationDidBecomeActive(_ application: UIApplication) {

    mainControllerCreate()
    
    // ログ出力コールバック関数の設定と定義
    mainControllerSetLogger({
        (loggerArgument) in
        let _loggerArgument:LoggerArgument = loggerArgument
        print(
            String(NSString(bytes: _loggerArgument.className!,
                            length: _loggerArgument.classNameLength,
                            encoding: String.Encoding.utf8.rawValue)!
            ),
            String(NSString(bytes: _loggerArgument.functionName!,
                            length: _loggerArgument.functionNameLength,
                            encoding: String.Encoding.utf8.rawValue)!
            ),
            String(NSString(bytes: _loggerArgument.message!,
                            length: _loggerArgument.messageLength,
                            encoding: String.Encoding.utf8.rawValue)!
            )
        )
    })
    
    // エラー出力コールバック関数の設定と定義
    mainControllerSetError({
        (errorArgument) in
        let _errorArgument:ErrorArgument = errorArgument
        print(
            String(NSString(bytes: _errorArgument.className!,
                            length: _errorArgument.classNameLength,
                            encoding: String.Encoding.utf8.rawValue)!
            ),
            String(_errorArgument.errorCode)
        )
    })
    
    mainControllerInitialize()
    
    // エラーログを出力する
    mainControllerSetErrorCode("applicationDidBecomeActive", 1)
  }

  func applicationWillTerminate(_ application: UIApplication) {
  }
}

