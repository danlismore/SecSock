//
//  ServerConnect.cpp
//  SecSock
//
//  Created by dtl on 21/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#include "ServerConnect.h"

int ServerConnect::createSocket()
{
    int sock;
    struct sockaddr_in addr;
    
    addr.sin_family = m_type;
    addr.sin_port = htons(m_port);
    addr.sin_addr.s_addr = inet_addr(m_host.c_str());
    sock = socket(m_type, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("Unable to establish socket!");
        exit(EXIT_FAILURE);
    }
    if(bind(sock, (struct sockaddr *) &addr, sizeof(addr) < 0))
    {
        perror("Unable to bind to address!");
        exit(EXIT_FAILURE);
    }
    if(listen(sock, 1) < 0)
    {
        perror("An error occured while listening to socket!");
        exit(EXIT_FAILURE);
    }
    return sock;
}

void ServerConnect::startServer()
{
    m_running = true;
    initOpenSSL();
    SSL_CTX * ctx = createContext();
    int sock = createSocket();
    
    while(m_running)
    {
        unsigned int len;
        int client;
        if(m_type == IPv4)
        {
            struct sockaddr_in addr;
            len = sizeof(addr);
            client = accept(sock, (struct sockaddr*)&addr, &len);
        }
        else if(m_type == IPv6)
        {
            struct sockaddr_in6 addr;
            len = sizeof(addr);
            client = accept(sock, (struct sockaddr*)&addr, &len);
        }
        if (client < 0)
        {
            perror("Unable to accept connection to client!");
            exit(EXIT_FAILURE);
        }
        reply = "test\n";
        if(m_secure)
        {
            SSL * ssl = SSL_new(ctx);
            SSL_set_fd(ssl, client);
            if (SSL_accept(ssl) <= 0)
            {
                ERR_print_errors_fp(stderr);
            }
            else
            {
                SSL_write(ssl, reply.c_str(), reply.length());
            }
        }
    }
}

void ServerConnect::stopServer()
{
    m_running = false;
}