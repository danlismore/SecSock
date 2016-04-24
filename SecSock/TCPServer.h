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
#include "TCP.h"

class TCPServer : public TCP
{
public:
    /**
     * Method name: TCPServer
     * Description: Constructor for the TCPServer class, needs no additional functionality so call
     *              parent constructor.
     * Parameters: host (string) - ip address with or without port,
     *             port (unsigned short) - ip address with or without port,
     *             is_secure (bool) - connection is secure
     */
    // Methods
    TCPServer(const std::string &host, const unsigned short &port, const bool &is_secure = true) : TCP(host, port, is_secure) {};
    void startServer();
    /**
     * Method name: stopServer
     * Description: Stop the TCP server, this currently doesn't work as startServer
     * won't break out of the loop. Stop server should be called from a seperate thread.
     */
    void stopServer();
    /**
     * Method name: process
     * Description: Pure virtual function, for processing the request buffer, this must
     *              be overridden with behaviour specific to the protocol being implmented.
     */
    virtual std::string process(std::vector<char> &request) = 0;
private:
    /**
     * Method name: createSocket
     * Description: Create a IPv4 or IPv6 TCP socket depending on IP address type
     *              determined by the address string.
     */
    int createSocket();
    /**
     * Method name: bindListen
     * Description: Bind to address specified by the sockaddr structure.
     * Parameters: sock (int) - the status of the sock we're binding to.
     *             addr (sockaddr*) - pointer to the socket address structure.
     *             addrsize (socklen_t) - size of the socket address structure.
     */
    int bindListen(int sock, struct sockaddr* addr, socklen_t addrsize);
    /**
     * Method name: startServer
     * Description: Start the TCP server, read and write using POSIX or OpenSSL
     * depending on whether server is "secure" or not. The latter requires a
     * certificate and key in the executable directory.
     */
    // Members
    std::atomic<bool> running;
    std::string reply;
};

#endif /* defined(__SeckSock__ServerConnect__) */
