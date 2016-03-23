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

using std::string;

class Connect
{
public:
    /**
     * Enum name: IPType
     * Description: Holds the two different IP versions, values match socket defines.
     * Members: host (string) - ip address with or without port,
     *             is_secure (bool) - connection is secure
     */
    enum IPType
    {
        IPv4 = 2,
        IPv6 = 10
    };
    /**
     * Method name: Connect
     * Description: Constructor for the Connect class.
     * Parameters: host (string) - ip address with or without port,
     *             is_secure (bool) - connection is secure
     */
    Connect(string host, bool is_secure = true);
    /**
     * Method name: Connect
     * Description: Constructor for the Connect class.
     * Parameters: host (string) - ip address,
     *             port (unsigned short) - port number,
     *             is_secure (bool) - connection is secure
     */
    Connect(string host, unsigned short port, bool is_secure = true);
    /**
     * Method name: setHost
     * Description: Set the host to a specified string.
     * Parameters: host (string) - ip address
     */
    void setHost(string host);
    /**
     * Method name: setPort
     * Description: Set the port to a specified number.
     * Parameters: port (unsigned short) - port number
     */
    void setPort(unsigned short port);
    /**
     * Method name: setCert
     * Description: Set the path to a cert file.
     * Parameters: cert (string) - cert path
     */
    void setCert(string cert);
    /**
     * Method name: setKey
     * Description: Set the path to a key file.
     * Parameters: key (string) - key path
     */
    void setKey(string key);
private:
    /**
     * Method name: validateHost
     * Description: Check whether a host is valid and set type to IP version.
     * Parameters: host (string) - the host to checj
     */
    bool validateHost(const string& host);
    /**
     * Method name: portCheck
     * Description: Check whether a port is in a valid range.
     * Parameters: port (unsigned short) - the port to check
     */
    bool portCheck(const unsigned short& port);
    /**
     * Method name: portCheck
     * Description: Check whether port as a string is a valid number and is in a valid range.
     * Parameters: port (string) - the port to check
     */
    bool portCheck(const string& port);
protected:
    /**
     * Method name: initOpenSSL
     * Description: Initiate OpenSSL algorithms and error strings.
     */
    void initOpenSSL();
    /**
     * Method name: createContext
     * Description: Create the context, get cert and key from file.
     */
    SSL_CTX * createContext();
    /**
     * Method name: cleanupOpenSSL
     * Description: Clean up OpenSSL.
     */
    void cleanupOpenSSL();
protected:
    IPType m_type;
    bool m_secure;
    string m_cert, m_key;
    string m_host;
    unsigned short m_port;
};

#endif /* defined(__SeckSock__Connect__) */
