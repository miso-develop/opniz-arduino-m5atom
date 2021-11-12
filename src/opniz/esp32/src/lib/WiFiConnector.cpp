#include "./WiFiConnector.h"

WiFiConnector::WiFiConnector(const char* ssid, const char* password) {
    _ssid = ssid;
    _password = password;
}

WiFiConnector::~WiFiConnector() {
    disconnect();
}

void WiFiConnector::connect() {
    connect(_timeoutCallback, _connectingSignal);
}
void WiFiConnector::connect(std::function<void()> timeoutCallback) {
    connect(timeoutCallback, _connectingSignal);
}
void WiFiConnector::connect(std::function<void(boolean)> connectingSignal) {
    connect(_timeoutCallback, connectingSignal);
}
void WiFiConnector::connect(std::function<void()> timeoutCallback, std::function<void(boolean)> connectingSignal) {
    if (isConnected()) return;
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);
    Serial.print("WiFi connecting");
    
    // connecting
    uint32_t _startTime = millis();
    while (!isConnected()) {
        if((millis() - _startTime) > _timeout) {
            _startTime = millis();
            timeoutCallback();
            return;
        }
        
        _connectingSignalState = !_connectingSignalState;
        connectingSignal(_connectingSignalState);
        
        Serial.print(".");
        delay(250);
    }
    
    connectingSignal(false);
    Serial.print("\nWiFi connected: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}

void WiFiConnector::disconnect() {
    if (!isConnected()) return;
    
    // タイムアウトチェック
    while (!WiFi.disconnect(true)) {
        if((millis() - _startTime) > _timeout) esp_restart();
        
        Serial.print(".");
        delay(250);
    }
    
    Serial.println("WiFi disconnected!");
}

void WiFiConnector::reconnect() {
    disconnect();
    connect();
}

bool WiFiConnector::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiConnector::keepAlive() {
    connect();
}

void WiFiConnector::watch() {
    connect();
}
