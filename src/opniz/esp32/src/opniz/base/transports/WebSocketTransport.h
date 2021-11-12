#ifndef WEBSOCKET_TRANSPORT_H
#define WEBSOCKET_TRANSPORT_H

#include <WebSocketsClient.h>
#include <SocketIOclient.h>
#include <ArduinoJson.h>

#include "./Transport.h"

#include "../lib/utils.h" // DEBUG:

typedef std::function<void(socketIOmessageType_t type, uint8_t * payload, size_t length)> SocketIOclientEvent;

class WebSocketTransport : public Transport {
private:
    SocketIOclient _socketIO;
    
    SocketIOclientEvent _createSocketIOEvent();
    void _socketIOEventHandler(uint8_t *payload, size_t length);
    
public:
    WebSocketTransport(const char* address, const uint16_t port);
    ~WebSocketTransport();
    
    void init(std::function<String(String)> rpcHandlerFunction);
    
    void connect();
    void close();
    
    boolean send(const String rpcRequests);
    void receive();
    
    boolean isConnected();
    void keepAlive();
};

#endif
