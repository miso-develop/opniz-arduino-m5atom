#ifndef WIFI_CONNECTOR_H
#define WIFI_CONNECTOR_H

#include <WiFi.h>

class WiFiConnector {
private:
    const char* _ssid;
    const char* _password;
    
    uint16_t _timeout = 60 * 1000;
    uint32_t _startTime;
    std::function<void()> _timeoutCallback = [this]() { connect(); };
    
    boolean _connectingSignalState = false;
    std::function<void(boolean)> _connectingSignal = [](boolean){};
    
public:
    WiFiConnector(const char* ssid, const char* password);
    ~WiFiConnector();
    
    bool connect();
    bool connect(std::function<void()> timeoutCallback);
    bool connect(std::function<void(boolean)> connectingSignal);
    bool connect(std::function<void()> timeoutCallback, std::function<void(boolean)> connectingSignal);
    
    bool disconnect();
    bool reconnect() { disconnect(); return connect(); };
    bool isConnected() { return WiFi.status() == WL_CONNECTED; };
    
    bool keepAlive() { return connect(); };
    bool watch() { return connect(); };
    
    void setTimeout(uint16_t timeout) { _timeout = timeout; };
    void setTimeoutCallback(std::function<void()> timeoutCallback) { _timeoutCallback = timeoutCallback; };
    void setConnectingSignal(std::function<void(boolean)> connectingSignal) { _connectingSignal = connectingSignal; };
    
    uint16_t getTimeout() { return _timeout; };
    String getSsid() { return _ssid; };
    String getIp() { return isConnected() ? WiFi.localIP().toString() : "Not connected"; };
};

#endif
