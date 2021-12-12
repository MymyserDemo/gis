import UIKit
import WebKit

class MainView: UIViewController, WKUIDelegate {

    var webView: WKWebView!
    
    func loggerView(_ loggerArgument:LoggerArgument) {
        print(
            String(NSString(bytes: loggerArgument.className!,
                            length: loggerArgument.classNameLength,
                            encoding: String.Encoding.utf8.rawValue)!
            ),
            String(NSString(bytes: loggerArgument.functionName!,
                            length: loggerArgument.functionNameLength,
                            encoding: String.Encoding.utf8.rawValue)!
            ),
            String(NSString(bytes: loggerArgument.message!,
                            length: loggerArgument.messageLength,
                            encoding: String.Encoding.utf8.rawValue)!
            )
        )
    }
    
    override func loadView() {
        let webConfiguration = WKWebViewConfiguration()
        webView = WKWebView(frame: .zero, configuration: webConfiguration)
        webView.uiDelegate = self
        view = webView
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        let myURL = URL(string: "http://www.apple.com")
        let myRequest = URLRequest(url: myURL!)
        webView.load(myRequest)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
}

