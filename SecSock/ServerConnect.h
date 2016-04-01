//
//  ServerConnect.h
//  SecSock
//
//  Created by dtl on 21/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#ifndef __SeckSock__ServerConnect__
#define __SeckSock__ServerConnect__

#include <arpa/inet.h>
#include "Connect.h"

class ServerConnect : public Connect
{
public:
    /**
     * Method name: ServerConnect
     * Description: Constructor for the ServerConnect class, needs no additional functionality so call
     *              parent constructor.
     * Parameters: host (string) - ip address with or without port,
     *             port (unsigned short) - ip address with or without port,
     *             is_secure (bool) - connection is secure
     */
    // Methods
    ServerConnect(const std::string &host, const unsigned short &port, const bool &is_secure = true) : Connect(host, port, is_secure) {};
    int createSocket();
    int bindListen(int sock, struct sockaddr* addr, socklen_t addrsize);
    void startServer();
    void stopServer();
    virtual std::string process(std::vector<char> &request) { return ""; };
private:
    // Members
    std::atomic<bool> running;
    std::string reply;
};

#endif /* defined(__SeckSock__ServerConnect__) */
