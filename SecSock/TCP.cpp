//
//  Connect.cpp
//  SecSock
//
//  Created by dtl on 21/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#include <arpa/inet.h>
#include <sys/socket.h>
#include "TCP.h"

/**
 * Method name: TCP
 * Description: Constructor for the TCP class.
 * Parameters: host (string) - ip address with or without port, 
 *             is_secure (bool) - connection is secure
 */
TCP::TCP(const std::string &host, const bool &is_secure)
{
    setCert("cert.pem");
    setKey("key.pem");
    if(host.find(':') != std::string::npos)
    {
        size_t pos = host.find(':');
        this->host = host.substr(0, pos - 1);
        if(!validateHost(this->host))
        {
            perror("Invalid hostname or IP");
            exit(EXIT_FAILURE);
        }
        if(!portCheck(this->port))
        {
            perror("Invalid port number or error parsing");
            exit(EXIT_FAILURE);
        }
        this->port = std::stoi(host.substr(pos + 1, host.length()));
    }
    else
    {
        this->host = host;
        if(this->secure)
            this->port = 443;
        else
            this->port = 80;
    }
}

/**
 * Method name: TCP
 * Description: Constructor for the TCP class.
 * Parameters: host (string) - ip address,
 *             port (unsigned short) - port number,
 *             is_secure (bool) - connection is secure
 */
TCP::TCP(const std::string &host, const unsigned short &port, const bool &is_secure)
{
    this->secure = is_secure;
    setCert("cert.pem");
    setKey("key.pem");
    if(!validateHost(host))
    {
        perror("Invalid hostname or IP");
        exit(EXIT_FAILURE);
    }
    if(!portCheck(port))
    {
        perror("Invalid port number");
        exit(EXIT_FAILURE);
    }
    else
    {
        this->host = host;
        this->port = port;
    }
}

/**
 * Method name: setHost
 * Description: Set the host to a specified string.
 * Parameters: host (string) - ip address
 */
void TCP::setHost(const std::string &host)
{
    this->host = host;
}

/**
 * Method name: setPort
 * Description: Set the port to a specified number.
 * Parameters: port (unsigned short) - port number
 */
void TCP::setPort(const unsigned short &port)
{
    this->port = port;
}

/**
 * Method name: setCert
 * Description: Set the path to a cert file.
 * Parameters: cert (string) - cert path
 */
void TCP::setCert(const std::string &cert)
{
    this->cert = cert;
}

/**
 * Method name: setKey
 * Description: Set the path to a key file.
 * Parameters: key (string) - key path
 */
void TCP::setKey(const std::string &key)
{
    this->key = key;
}

/**
 * Method name: validateHost
 * Description: Check whether a host is valid and set type to IP version.
 * Parameters: host (string) - the host to checj
 */
bool TCP::validateHost(const std::string &host)
{
    struct sockaddr_in sa4;
    struct sockaddr_in6 sa6;
    if(inet_pton(AF_INET, host.c_str(), &(sa4.sin_addr)) != 0)
    {
        this->type = IPv4;
        return true;
    }
    else if(inet_pton(AF_INET6, host.c_str(), &(sa6.sin6_addr)) != 0)
    {
        this->type = IPv6;
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Method name: portCheck
 * Description: Check whether a port is in a valid range.
 * Parameters: port (unsigned short) - the port to check
 */
bool TCP::portCheck(const unsigned short &port)
{
    return (0 < port && port < 65535);
}

/**
 * Method name: portCheck
 * Description: Check whether port as a string is a valid number and is in a valid range.
 * Parameters: port (string) - the port to check
 */
bool TCP::portCheck(const std::string &port)
{
    return std::all_of(port.begin(), port.end(), ::isdigit) &&
       (0 < std::stoi(port) && std::stoi(port) < 65535);
}

/**
 * Method name: initOpenSSL
 * Description: Initiate OpenSSL algorithms and error strings.
 */
void TCP::initOpenSSL()
{
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

/**
 * Method name: createContext
 * Description: Create the context, get cert and key from file.
 */
SSL_CTX * TCP::createContext()
{
    SSL_CTX * ctx = SSL_CTX_new(TLSv1_method());
    if (!ctx)
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    SSL_CTX_ctrl(ctx, SSL_CTRL_SET_TMP_ECDH, 1 ,NULL);
    if (SSL_CTX_use_certificate_file(ctx, this->cert.c_str(), SSL_FILETYPE_PEM) < 0)
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, this->key.c_str(), SSL_FILETYPE_PEM) < 0 )
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    return ctx;
}

/**
 * Method name: cleanupOpenSSL
 * Description: Clean up OpenSSL.
 */
void TCP::cleanupOpenSSL()
{
    EVP_cleanup();
}

