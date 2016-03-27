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

using std::map;
using std::make_pair;
using std::string;
using std::vector;

class HTTP
{
public:
    HTTP();
    string parseAndRespond(vector<char> request);
private:
    map<const unsigned short, const string> status_codes;
private:
    void initStatusCodes();
    string getFiletype(string filename);
    string getStatusCode(unsigned short status_code);
};

#endif /* defined(__SecSock__HTTP__) */
