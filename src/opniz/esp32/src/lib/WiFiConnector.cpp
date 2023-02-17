#include "./WiFiConnector.h"

WiFiConnector::WiFiConnector(const char* ssid, const char* password) : _ssid(ssid), _password(password){}

WiFiConnector::~WiFiConnector() {
    disconnect();
}

bool WiFiConnector::connect() {
    return connect(_timeoutCallback, _connectingSignal);
}
bool WiFiConnector::connect(std::function<void()> timeoutCallback) {
    return connect(timeoutCallback, _connectingSignal);
}
bool WiFiConnector::connect(std::function<void(boolean)> connectingSignal) {
    return connect(_timeoutCallback, connectingSignal);
}
bool WiFiConnector::connect(std::function<void()> timeoutCallback, std::function<void(boolean)> connectingSignal) {
    if (isConnected()) return true;
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);
    Serial.print("WiFi connecting");
    
    uint32_t _startTime = millis();
    while (!isConnected()) {
        if((millis() - _startTime) > _timeout) {
            _startTime = millis();
            timeoutCallback();
            return false;
        }
        
        _connectingSignalState = !_connectingSignalState;
        connectingSignal(_connectingSignalState);
        
        Serial.print(".");
        delay(250);
    }
    
    connectingSignal(false);
    Serial.println("\nWiFi connected!");
    Serial.printf("SSID: %s\nIP: %s\n\n", _ssid, WiFi.localIP().toString());
    return true;
}

bool WiFiConnector::disconnect() {
    if (!isConnected()) return true;
    
    Serial.print("WiFi disconnecting");
    
    uint32_t _startTime = millis();
    while (!WiFi.disconnect(true)) {
        if((millis() - _startTime) > _timeout) {
            _startTime = millis();
            return false;
        }
        
        Serial.print(".");
        delay(250);
    }
    
    Serial.println("WiFi disconnected!");
    return true;
}

