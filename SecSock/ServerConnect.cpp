//
//  ServerConnect.cpp
//  SecSock
//
//  Created by dtl on 21/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#include <unistd.h>
#include <vector>
#include "HTTP.h"
#include "ServerConnect.h"

int ServerConnect::createSocket()
{
    int sock = socket(m_type, SOCK_STREAM, 0);
    if(m_type == IPv4)
    {
        struct sockaddr_in addr;
        inet_pton(m_type, m_host.c_str(), &(addr.sin_addr));
        addr.sin_family = htons(m_type);
        addr.sin_port = htons(m_port);
        sock = bindListen(sock,(struct sockaddr *)&addr, sizeof(addr));
    }
    if(m_type == IPv6)
    {
        struct sockaddr_in6 addr;
        inet_pton(m_type, m_host.c_str(), &(addr.sin6_addr));
        addr.sin6_family = htons(m_type);
        addr.sin6_port = htons(m_port);
        sock = bindListen(sock,(struct sockaddr *)&addr, sizeof(addr));
    }
    return sock;
}

int ServerConnect::bindListen(int sock, struct sockaddr* addr, socklen_t addrsize)
{
    if(sock < 0)
    {
        perror("Unable to establish socket");
        exit(EXIT_FAILURE);
    }
    if(bind(sock, addr, addrsize) < 0)
    {
        perror("Unable to bind to address");
        exit(EXIT_FAILURE);
    }
    if(listen(sock, 1) < 0)
    {
        perror("An error occured while listening to socket");
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
    int client = 0;
    std::vector<char> v(4096);
    while(m_running)
    {
        unsigned int len;
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
            perror("Unable to accept connection to client");
            exit(EXIT_FAILURE);
        }
        reply = "";
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
                if(SSL_read(ssl, &v[0], (int) v.size()) < 0)
                {
                    perror("Could not read from secure client");
                    exit(EXIT_FAILURE);
                }
                if(SSL_write(ssl, reply.c_str(), reply.length()) < 0)
                {
                    perror("Could not write to client");
                    exit(EXIT_FAILURE);
                }
                for (auto it = v.begin(); it != v.end(); it++)
                {
                    printf("%c", *it);
                    reply += *it;
                }
            }
        }
        else
        {
            if(read(client, &v[0], v.size()) < 0)
            {
                perror("Could not read from client");
                exit(EXIT_FAILURE);
            }
            else if(write(client, reply.c_str(), reply.length()) < 0)
            {
                perror("Could not write to client");
                exit(EXIT_FAILURE);
            }
            HTTP http;
            http.parseAndRespond(v);
            for (auto it = v.begin(); it != v.end(); it++)
            {
                printf("%c", *it);
                reply += *it;
            }
            
        }
    }
    close(client);
    close(sock);
}

void ServerConnect::stopServer()
{
    m_running = false;
}