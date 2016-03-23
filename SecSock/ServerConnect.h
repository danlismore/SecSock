//
//  ServerConnect.h
//  SecSock
//
//  Created by dtl on 21/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#ifndef __SeckSock__ServerConnect__
#define __SeckSock__ServerConnect__

#include "Connect.h"

class ServerConnect : public Connect
{
public:
    ServerConnect(string host, unsigned short port, bool is_secure = true) : Connect(host, port, is_secure) {};
    int createSocket();
    int bindListen(int sock, struct sockaddr* addr);
    void startServer();
    void stopServer();
private:
    bool m_running;
    string reply;
};

#endif /* defined(__SeckSock__ServerConnect__) */
