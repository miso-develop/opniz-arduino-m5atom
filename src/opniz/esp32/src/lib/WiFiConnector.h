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
    
    void connect();
    void connect(std::function<void()> timeoutCallback);
    void connect(std::function<void(boolean)> connectingSignal);
    void connect(std::function<void()> timeoutCallback, std::function<void(boolean)> connectingSignal);
    
    void disconnect();
    void reconnect();
    bool isConnected();
    
    void keepAlive();
    void watch();
    
    void setTimeout(uint16_t timeout) { _timeout = timeout; };
    void setTimeoutCallback(std::function<void()> timeoutCallback) { _timeoutCallback = timeoutCallback; };
    void setConnectingSignal(std::function<void(boolean)> connectingSignal) { _connectingSignal = connectingSignal; };
};

#endif
