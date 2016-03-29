//
//  HTTPHeaders.h
//  SecSock
//
//  Created by dtl on 25/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#ifndef __SecSock__HTTP__
#define __SecSock__HTTP__

#include <map>
#include <string>
#include <vector>

class HTTP
{
public:
    // Methods
    HTTP();
    void setWebRoot(const std::string &path);
    std::string parseAndRespond(std::vector<char> &request);
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

#endif /* defined(__SecSock__HTTP__) */
