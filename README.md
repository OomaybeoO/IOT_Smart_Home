# IOT_Smart_Home

此專案為一個智慧家庭系統，透過 Arduino 與 Swift 應用來控制及監測家庭環境。專案包含三個主要部分：
- **arduino_CameraServer**: 基於 Arduino 的攝影機伺服器
- **arduino_main**: 主要 Arduino 控制邏輯
- **Smart-home**: 使用 Swift 開發的智慧家庭應用程式

## 專案目錄

### arduino_CameraServer
此部分是基於 Arduino 的攝影機伺服器，負責透過網路提供即時影像串流功能。

- **app_httpd.cpp**: 網頁伺服器的實作，負責影像串流。
- **arduino_CameraServer.ino**: Arduino 主程式檔。
- **camera_index.h**: 定義網頁伺服器的首頁內容。
- **camera_pins.h**: 定義攝影機的引腳配置。
- **ci.json**: 設定文件。
- **partitions.csv**: 記憶體分區配置表。

### arduino_main
此部分包含所有與感測器和 Wi-Fi 網路相關的控制邏輯。

- **SP.cpp / SP.h**: 控制感測器的邏輯與數據讀取。
- **SensorManager.cpp / SensorManager.h**: 管理各種感測器的數據。
- **WiFiWebSocket.cpp / WiFiWebSocket.h**: 使用 WebSocket 通訊的網路管理模組。
- **arduino_main.ino**: 主程式文件，負責與 Swift 應用進行通訊並控制感測器和設備。

### Smart-home (Swift App)
此部分是智慧家庭應用的 iOS 前端，透過 WebSocket 與 Arduino 通訊，實現即時數據顯示與控制功能。

- **ContentView.swift**: 主要的 SwiftUI 檢視。
- **HomeView.swift**: 應用的主畫面。
- **ListView.swift**: 顯示感測器數據的列表視圖。
- **MoreView.swift**: 設定頁面。
- **StreamingView.swift**: 即時影像串流的檢視。
- **WebSocketManager.swift**: WebSocket 連接與管理。

## 如何運行

### 硬體要求
- **ESP32-CAM**: 用於影像串流
- **Arduino**: 連接各種感測器與控制元件
- **感測器**: 溫度、氧氣、pH值等感測器

### 軟體要求
- **Arduino IDE**: 編譯與上傳 Arduino 程式碼
- **Xcode**: 編譯與運行 Swift 應用程式
- **Django**: 作為後端服務

### 部署步驟

1. 在 Arduino IDE 中開啟 `arduino_main.ino` 與 `arduino_CameraServer.ino`，並上傳至 ESP32 和 Arduino 板。
2. 使用 Xcode 編譯並運行 Swift 應用，確保手機與 Arduino 在同一網路下。
3. 確認感測器數據可以透過 WebSocket 連接顯示在應用程式上，並且影像串流功能正常運作。

