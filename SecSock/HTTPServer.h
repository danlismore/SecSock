//
//  HTTPHeaders.h
//  SecSock
//
//  Created by dtl on 25/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#ifndef __SecSock__HTTPServer__
#define __SecSock__HTTPServer__

#include <map>
#include <string>
#include <vector>
#include "TCPServer.h"

class HTTPServer : public TCPServer
{
public:
    // Methods
    HTTPServer(const std::string &host, const unsigned short &port, const bool &is_secure = true);
    void setWebRoot(const std::string &path);
    std::string process(std::vector<char> &request) override;
private:
    // Members
    const std::string http_version;
    const std::string server_name;
    std::string web_root;
    std::vector<char> file_buffer;
    std::map<const unsigned short, const std::string> status_codes;
    // Methods
    void initStatusCodes();
    bool readFromFile(std::string file_path);
    std::string getContentType(const std::string &file_name);
    std::string getContentLength();
    std::string getStatusCode(unsigned short status_code);
};

#endif /* defined(__SecSock__HTTPServer__) */
