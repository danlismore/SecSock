//
//  Connect.cpp
//  SecSock
//
//  Created by dtl on 21/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#include <sys/socket.h>
#include "Connect.h"

Connect::Connect(string host, bool is_secure)
{
    m_secure = is_secure;
    setCert("cert.pem");
    setKey("key.pem");
    if(host.find(':') != string::npos)
    {
        size_t pos = host.find(':');
        m_host = host.substr(0, pos - 1);
        if(!validateHost(m_host))
        {
            perror("Invalid hostname or IP!");
            exit(EXIT_FAILURE);
        }
        if(!portCheck(m_port))
        {
            perror("Invalid port number or error parsing!");
            exit(EXIT_FAILURE);
        }
        m_port = std::stoi(host.substr(pos + 1, host.length()));
    }
    else
    {
        m_host = host;
        if(m_secure)
            m_port = 443;
        else
            m_port = 80;
    }
}

Connect::Connect(string host, unsigned short port, bool is_secure)
{
    m_secure = is_secure;
    setCert("cert.pem");
    setKey("key.pem");
    if(!validateHost(host))
    {
        perror("Invalid hostname or IP!");
        exit(EXIT_FAILURE);
    }
    if(!portCheck(port))
    {
        perror("Invalid port number!");
        exit(EXIT_FAILURE);
    }
    else
    {
        m_host = host;
        m_port = port;
    }
}

void Connect::setHost(string host)
{
    m_host = host;
}

void Connect::setPort(unsigned short port)
{
    m_port = port;
}

void Connect::setCert(string cert)
{
    m_cert = cert;
}

void Connect::setKey(string key)
{
    m_key = key;
}

bool Connect::validateHost(const string &host)
{
    struct sockaddr_in sa4;
    struct sockaddr_in6 sa6;
    if(inet_pton(AF_INET, host.c_str(), &(sa4.sin_addr)) != 0)
    {
        m_type = IPv4;
        return true;
    }
    else if(inet_pton(AF_INET6, host.c_str(), &(sa6.sin6_addr)) != 0)
    {
        m_type = IPv6;
        return true;
    }
    else
    {
        return false;
    }
}

bool Connect::portCheck(const unsigned short& port)
{
    return (0 < port && port < 65535);
}

bool Connect::portCheck(const string& port)
{
    return std::all_of(port.begin(), port.end(), ::isdigit) &&
       (0 < std::stoi(port) && std::stoi(port) < 65535);
}

void Connect::initOpenSSL()
{
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

SSL_CTX * Connect::createContext()
{
    SSL_CTX * ctx = SSL_CTX_new(TLSv1_method());
    if (!ctx)
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    SSL_CTX_ctrl(ctx, SSL_CTRL_SET_TMP_ECDH, 1 ,NULL);
    if (SSL_CTX_use_certificate_file(ctx, m_cert.c_str(), SSL_FILETYPE_PEM) < 0)
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, m_key.c_str(), SSL_FILETYPE_PEM) < 0 )
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    return ctx;
}

void Connect::cleanup_openssl()
{
    EVP_cleanup();
}

