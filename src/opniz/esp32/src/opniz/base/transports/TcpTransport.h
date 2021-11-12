#ifndef TCP_TRANSPORT_H
#define TCP_TRANSPORT_H

#include <WiFi.h>

#include "./Transport.h"

#include "../lib/utils.h" // DEBUG:

class TcpTransport : public Transport {
private:
    WiFiServer _server;
    WiFiClient _socket;
    WiFiClient _client;
    
    uint16_t _timeout = 60 * 1000;
    uint32_t _startTime;
    std::function<void()> _timeoutCallback = [this]() { connect(); };
    
    boolean _connectingSignalState = false;
    std::function<void(boolean)> _connectingSignal = [](boolean){};
    
public:
    TcpTransport(const char* address, const uint16_t port);
    ~TcpTransport();
    
    void connect();
    void connect(const std::function<void()> timeoutCallback);
    void connect(const std::function<void(boolean)> connectingSignal);
    void connect(const std::function<void()> timeoutCallback, const std::function<void(boolean)> connectingSignal);
    void close();
    
    boolean send(const String rpcRequest);
    void receive();
    
    boolean isConnected();
    void keepAlive();
    
    void setTimeout(const uint16_t timeout) { _timeout = timeout; };
    void setTimeoutCallback(const std::function<void()> timeoutCallback) { _timeoutCallback = timeoutCallback; };
    void setConnectingSignal(const std::function<void(boolean)> connectingSignal) { _connectingSignal = connectingSignal; };
};

#endif
