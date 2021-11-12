#ifndef TRANSPORT_CREATOR_H
#define TRANSPORT_CREATOR_H

#include "./Transport.h"
#include "./TcpTransport.h"
#include "./WebSocketTransport.h"

typedef enum {
    WebSocket,
    TCP,
} Protocol;

class TransportCreator final {
public:
    TransportCreator() = delete;
    ~TransportCreator() = delete;
    
    static Transport* create(const char* address, const uint16_t port, const Protocol protocol = WebSocket) {
        switch (protocol) {
            case WebSocket:
                return new WebSocketTransport(address, port);
                break;
            case TCP:
                return new TcpTransport(address, port);
                break;
            default:
                return new WebSocketTransport(address, port);
                break;
        }
    }
};

#endif
