import SwiftUI
import WebKit

struct StreamingView: View {
    var streamURL: String

    var body: some View {
        VStack {
            Text("即時影像")
                .font(.largeTitle)
                .padding()

            if let url = URL(string: streamURL) {
                WebView(url: url)
                    .frame(width: UIScreen.main.bounds.width * 0.9, height: UIScreen.main.bounds.width * 0.56) // 16:9 比例
                    .cornerRadius(15)
                    .padding()
            } else {
                Text("無效的 URL")
                    .foregroundColor(.red)
                    .padding()
            }

            Spacer()
        }
        .navigationTitle("即時影像播放")
        .navigationBarTitleDisplayMode(.inline)
    }
}

struct WebView: UIViewRepresentable {
    let url: URL

    func makeUIView(context: Context) -> WKWebView {
        WKWebView()
    }

    func updateUIView(_ uiView: WKWebView, context: Context) {
        let request = URLRequest(url: url)
        uiView.load(request)
    }
}
