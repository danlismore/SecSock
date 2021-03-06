//
//  ServerConnect.cpp
//  SecSock
//
//  Created by dtl on 21/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#include <unistd.h>
#include <vector>
#include "TCPServer.h"

/**
 * Method name: createSocket
 * Description: Create a IPv4 or IPv6 TCP socket depending on IP address type
 *              determined by the address string.
 */
int TCPServer::createSocket()
{
    int sock = socket(this->type, SOCK_STREAM, 0);
    if(this->type == IPv4)
    {
        struct sockaddr_in addr;
        inet_pton(this->type, this->host.c_str(), &(addr.sin_addr));
        addr.sin_family = htons(this->type);
        addr.sin_port = htons(this->port);
        sock = bindListen(sock,(struct sockaddr *)&addr, sizeof(addr));
    }
    if(this->type == IPv6)
    {
        struct sockaddr_in6 addr;
        inet_pton(this->type, this->host.c_str(), &(addr.sin6_addr));
        addr.sin6_family = htons(this->type);
        addr.sin6_port = htons(this->port);
        sock = bindListen(sock,(struct sockaddr *)&addr, sizeof(addr));
    }
    return sock;
}

/**
 * Method name: bindListen
 * Description: Bind to address specified by the sockaddr structure.
 * Parameters: sock (int) - the status of the sock we're binding to.
 *             addr (sockaddr*) - pointer to the socket address structure.
 *             addrsize (socklen_t) - size of the socket address structure.
 */
int TCPServer::bindListen(int sock, struct sockaddr* addr, socklen_t addrsize)
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

/**
 * Method name: startServer
 * Description: Start the TCP server, read and write using POSIX or OpenSSL 
 * depending on whether server is "secure" or not. The latter requires a 
 * certificate and key in the executable directory.
 */
void TCPServer::startServer()
{
    this->running = true;
    initOpenSSL();
    SSL_CTX * ctx = createContext();
    int sock = createSocket();
    int client = 0;
    std::vector<char> request(4096);
    while(this->running)
    {
        unsigned int len;
        if(this->type == IPv4)
        {
            struct sockaddr_in addr;
            len = sizeof(addr);
            client = accept(sock, (struct sockaddr*)&addr, &len);
        }
        else if(this->type == IPv6)
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
        if(this->secure)
        {
            SSL * ssl = SSL_new(ctx);
            SSL_set_fd(ssl, client);
            if (SSL_accept(ssl) <= 0)
            {
                ERR_print_errors_fp(stderr);
            }
            else
            {
                if(SSL_read(ssl, &request[0], (int) request.size()) < 0)
                {
                    perror("Could not read from secure client");
                    exit(EXIT_FAILURE);
                }
                if(SSL_write(ssl, reply.c_str(), reply.length()) < 0)
                {
                    perror("Could not write to client");
                    exit(EXIT_FAILURE);
                }
                for (auto it = request.begin(); it != request.end(); it++)
                {
                    printf("%c", *it);
                }
            }
        }
        else
        {
            if(read(client, &request[0], request.size()) < 0)
            {
                perror("Could not read from client");
                exit(EXIT_FAILURE);
            }
            reply = process(request);
            if(write(client, reply.c_str(), reply.length()) < 0)
            {
                perror("Could not write to client");
                exit(EXIT_FAILURE);
            }
            for (auto it = request.begin(); it != request.end(); it++)
            {
                printf("%c", *it);
            }
        }
    }
    close(client);
    close(sock);
}

/**
 * Method name: stopServer
 * Description: Stop the TCP server, this currently doesn't work as startServer
 * won't break out of the loop. Stop server should be called from a seperate thread.
 */
void TCPServer::stopServer()
{
    this->running = false;
}