# 專案概述

此專案分為三個主要部分：`arduino_CameraServer`、`arduino_main` 和 `Smart-home`。每個資料夾包含不同的功能，協同完成整體專案目標。

## 1. arduino_CameraServer

### 說明：
該部分包含與相機伺服器設置相關的 Arduino 程式碼，負責實時串流和相機控制功能。

### 主要功能：
- 使用 ESP32-CAM 進行串流。
- 建立 HTTP 伺服器以托管相機畫面。
- 基本的相機設定控制（解析度、亮度等）。

### 內容：
- **`camera_server.ino`**：初始化並控制 ESP32-CAM 伺服器的主程式。
- **`config.h`**：相機與網路設定的配置檔案。

---

## 2. arduino_main

### 說明：
這部分包含 Arduino 系統的核心功能，主要關注於感測器數據讀取和設備控制。

### 主要功能：
- 感測器整合，用於監測環境參數。
- 控制致動器（如燈光、馬達、開關等）。
- 與其他模組或伺服器進行通訊。

### 內容：
- **`main.ino`**：負責處理感測器數據讀取與致動器控制的主要 Arduino 程式。
- **`sensor_utils.h`**：與感測器互動的輔助函式。
- **`actuator_control.h`**：控制各種致動器（如燈光、馬達等）的程式碼。

---

## 3. Smart-home

### 說明：
此資料夾包含使用 Swift 開發的智慧家庭控制應用程式，該應用程式負責提供使用者介面，讓用戶通過手機控制和監控家庭自動化設備。

### 主要功能：
- 控制家庭自動化設備（如燈光、溫度控制等）。
- 與 Arduino 裝置進行即時通訊，接收感測器數據並發送控制命令。
- 提供直觀的介面以顯示感測器數據和設備狀態。

### 內容：
- **`SmartHome.xcodeproj`**：Swift App 的 Xcode 專案檔案。
- **`ViewController.swift`**：主視圖控制器，處理介面邏輯和用戶交互。
- **`WebSocketManager.swift`**：處理 WebSocket 連接，與後端伺服器或 Arduino 裝置通訊。
- **`Models/`**：包含應用程式使用的數據模型，管理感測器數據和設備狀態。

---

## 開始使用

1. **設置 Arduino 相機伺服器**：
   - 將 `camera_server.ino` 上傳至你的 ESP32-CAM 設備。
   - 在 `config.h` 中配置網路設定。
   - 啟動伺服器，並通過瀏覽器訪問串流畫面。

2. **運行主要 Arduino 程式**：
   - 將 `main.ino` 上傳至管理感測器和致動器的 Arduino 板。
   - 確保所有感測器和設備均正確連接。

3. **使用 Smart-home App**：
   - 使用 Xcode 開啟 `SmartHome.xcodeproj` 專案。
   - 編譯並安裝應用程式至 iOS 設備。
   - 啟動應用程式，並通過 WebSocket 與 Arduino 裝置進行即時通訊，實現對家庭自動化系統的控制。

## 授權
本專案依照 MIT 授權條款授權使用，詳情請參閱 [LICENSE](LICENSE) 文件。
