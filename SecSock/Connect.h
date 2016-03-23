//
//  Connect.h
//  SecSock
//
//  Created by dtl on 21/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#ifndef __SeckSock__Connect__
#define __SeckSock__Connect__

#include <string>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <arpa/inet.h>

using std::string;

class Connect
{
public:
    enum IPType
    {
        IPv4 = AF_INET,
        IPv6 = AF_INET6
    };
    Connect(string host, bool is_secure = true);
    Connect(unsigned short port, bool is_secure = true);
    Connect(string host, unsigned short port, bool is_secure = true);
    void setHost(string host);
    void setPort(unsigned short port);
    void setCert(string cert);
    void setKey(string cert);
private:
    bool validateHost(const string& host);
    bool portCheck(const unsigned short& port);
    bool portCheck(const string& port);
protected:
    void initOpenSSL();
    SSL_CTX * createContext();
    void cleanup_openssl();
protected:
    IPType m_type;
    bool m_secure;
    string m_cert, m_key;
    string m_host;
    unsigned short m_port;
};

#endif /* defined(__SeckSock__Connect__) */
