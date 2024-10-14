#include <stdio.h>
#include "WiFiWebSocket.h"

void connectToWiFi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        Serial.print(".");
        delay(500);
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi 連接失敗！");
    } else {
        Serial.println("已連接到 WiFi");
    }
}

bool connectToWebSocket(WebsocketsClient* client, const char* host, uint16_t port, const char* path) {
    return client->connect(host, port, path);
}

void sendMessage(const char* user, const char* action_code, float arg1, float arg2, float arg3) {
    // 創建 JSON 文檔，使用靜態內存
    StaticJsonDocument<256> doc;

    // 添加用戶和動作代碼到 JSON
    doc["user"] = user;
    doc["action_code"] = action_code;

    // 將 args 數組中的每個浮點數轉換為字串並添加到 JSON 中
    JsonArray args = doc.createNestedArray("args");
    args.add(String(arg1, 1));  // 保留1位小數
    args.add(String(arg2, 1));
    args.add(String(arg3, 1));

    // 序列化 JSON 並將其轉換為字符串
    String message;
    serializeJson(doc, message);

    // 檢查 client 是否為有效指標，避免錯誤
    if (client != nullptr) {
        // 發送消息
        client->send(message);
        Serial.print("已發送: ");
        Serial.println(message);
    } else {
        Serial.println("錯誤: client 是空的，無法發送消息");
    }
}

void ControlDevices(bool led1,bool led2,bool fan1,bool fan2) {
  digitalWrite(LED1, led1);
  digitalWrite(LED2, led2);
  digitalWrite(FAN1, fan1);
  digitalWrite(FAN2, fan2);
}
void processMessage(float arg1) {
    // 將浮點數 arg1 轉換為整數進行位數拆分
    int intArg1 = static_cast<int>(arg1);  // 轉換為整數
    int led1 = (intArg1 / 1000) % 10;      // 提取千位數
    int led2 = (intArg1 / 100) % 10;       // 提取百位數
    int fan1 = (intArg1 / 10) % 10;        // 提取十位數
    int fan2 = intArg1 % 10;               // 提取個位數
    // 呼叫控制設備的函數
    ControlDevices(led1, led2, fan1, fan2);
    // 調試輸出
    Serial.print("led1: "); Serial.println(led1);
    Serial.print("led2: "); Serial.println(led2);
    Serial.print("fan1: "); Serial.println(fan1);
    Serial.print("fan2: "); Serial.println(fan2);
}
void handleWebSocketMessage(WebsocketsMessage message) {
    lastResponseTime = millis(); // 更新上次收到回應的時間
    Serial.print("接收到訊息: ");
    Serial.println(message.data());

    StaticJsonDocument<256> responseDoc;  // 使用 StaticJsonDocument
    deserializeJson(responseDoc, message.data());
    const char* user = responseDoc["user"];
    const char* action_code = responseDoc["action_code"];
    float arg1 = responseDoc["args"][0];
    float arg2 = responseDoc["args"][1];
    float arg3 = responseDoc["args"][2];
    if (strcmp(action_code, "1234") == 0) { // 使用 strcmp 進行字串比較
      Serial.println("使用者操作！");
      processMessage(arg1);  // 傳遞浮點數到處理函數
    }
    // Serial.print("用戶: ");
    // Serial.println(user);
    // Serial.print("操作代碼: ");
    // Serial.println(action_code);
    // Serial.print("光強度: ");
    // Serial.println(arg1);
    // Serial.print("濕度: ");
    // Serial.println(arg2);
    // Serial.print("溫度: ");
    // Serial.println(arg3);
}

void checkConnection() {
    if (millis() - lastResponseTime > responseTimeout) {
        Serial.println("超過 5 秒未收到 WebSocket 回應");
        esp_restart();
    }
    Serial.println("check ok!");
}
