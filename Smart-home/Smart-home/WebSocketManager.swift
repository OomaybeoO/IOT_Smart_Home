import Foundation
import Combine

class WebSocketManager: ObservableObject {
    @Published var temperature: String = "N/A"
    @Published var humidity: String = "N/A"
    @Published var light: String = "N/A"
    
    private var webSocketTask: URLSessionWebSocketTask?
    private var cancellables = Set<AnyCancellable>()
    
    func connect() {
        let url = URL(string: "ws://49.213.238.75:8001/ws/sensor/room_name/")!
        webSocketTask = URLSession.shared.webSocketTask(with: url)
        webSocketTask?.resume()
        print("WebSocket connection successful!")
        
        listen()
    }
    
    func disconnect() {
        webSocketTask?.cancel(with: .goingAway, reason: nil)
    }
    
    private func listen() {
        webSocketTask?.receive { [weak self] result in
            switch result {
            case .failure(let error):
                print("Error receiving message: \(error)")
            case .success(let message):
                self?.handleMessage(message)
                self?.listen() // Continue listening for messages
            }
        }
    }
    
    private func handleMessage(_ message: URLSessionWebSocketTask.Message) {
        switch message {
        case .string(let text):
            print("Received string message: \(text)") // Print received string message
            parseMessage(text)
            //        case .data(let data):
            //            print("Received data message: \(data)") // Print received data message
        default:
            print("Received unsupported message type")
        }
    }
    
    private func parseMessage(_ message: String) {
        if let data = message.data(using: .utf8) {
            if let json = try? JSONSerialization.jsonObject(with: data) as? [String: Any],
               let actionCode = json["action_code"] as? String,
               let args = json["args"] as? [String] {
                receiveMessage(actionCode: actionCode, args: args)
            }
        }
    }
    
    private func receiveMessage(actionCode: String, args: [String]) {
        if actionCode == "9999", args.count == 3 {
            // Safely unwrap the optional values
            if let temperatureValue = Double(args[0]),
               let humidityValue = Double(args[1]),
               let lightValue = Double(args[2]) {
                
                // 使用主執行緒更新 UI
                DispatchQueue.main.async {
                    // Update properties with the converted numeric values
                    self.temperature = "\(temperatureValue)°C"
                    self.humidity = "\(humidityValue)%"
                    self.light = "\(lightValue) Lux"
                    
                    // Print the values for debugging
                    print("Temperature: \(temperatureValue)°C, Humidity: \(humidityValue)%, Light: \(lightValue) Lux")
                }
                
            } else {
                print("Failed to convert one or more values to Double.")
            }
        } else {
            print("Invalid data received or action code mismatch.")
        }
    }


    
    
}
