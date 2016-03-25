//
//  HTTPHeaders.h
//  SecSock
//
//  Created by dtl on 25/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#ifndef __SecSock__HTTPHeaders__
#define __SecSock__HTTPHeaders__

#include <map>
#include <string>

using std::map;
using std::string;

/* Singleton class for HTTPHeaders - contains unchangeable information */
class HTTPHeaders
{
public:
    static HTTPHeaders *instance()
    {
        if (!httpheaders)
            httpheaders = new HTTPHeaders;
        return httpheaders;
    }
    string getStatusCode(unsigned short status_code)
    {
        status_it = status_codes.find(status_code);
        return status_it->second;
    }
private:
    static HTTPHeaders * httpheaders;
    map<unsigned short, string> status_codes;
    map<unsigned short, string>::iterator status_it;
private:
    HTTPHeaders()
    {
        initStatusCodes();
    }
    void initStatusCodes()
    {
        // 1** Informational
        status_codes[100] = "100 Continue";
        status_codes[101] = "101 Switching Protocols";
        status_codes[102] = "102 Processing";
        // 2** Success
        status_codes[200] = "200 OK";
        status_codes[201] = "201 Created";
        status_codes[202] = "202 Accepted";
        status_codes[203] = "203 Non-Authoritative Information";
        status_codes[204] = "204 No Content";
        status_codes[205] = "205 Reset Content";
        status_codes[206] = "206 Partial Content";
        status_codes[207] = "207 Multi-status_codes";
        status_codes[208] = "208 Already Reported";
        status_codes[226] = "226 IM Used";
        // 3** Redirection
        status_codes[300] = "300 Multiple Choices";
        status_codes[301] = "301 Moved permanently";
        status_codes[302] = "302 Found";
        status_codes[303] = "303 See Other";
        status_codes[304] = "304 Not Modified";
        status_codes[305] = "305 Use Proxy";
        status_codes[306] = "306 Switch Proxy";
        status_codes[307] = "307 Temporary Redirect";
        status_codes[308] = "308 Permanent Redirect";
        // 4** Client Error
        status_codes[400] = "400 Bad Request";
        status_codes[401] = "401 Unauthorized";
        status_codes[402] = "402 Payment Required";
        status_codes[403] = "403 Forbidden";
        status_codes[404] = "404 Not Found";
        status_codes[405] = "405 Method Not Allowed";
        status_codes[406] = "406 Not Acceptable";
        status_codes[407] = "407 Proxy Authentication Required";
        status_codes[408] = "408 Request Timeout";
        status_codes[409] = "409 Conflict";
        status_codes[410] = "410 Gone";
        status_codes[411] = "411 Length Required";
        status_codes[412] = "412 Precondition Failed";
        status_codes[413] = "413 Payload Too Large";
        status_codes[414] = "414 URI Too Long";
        status_codes[415] = "415 Unsupported Media Type";
        status_codes[416] = "416 Range Not Satisfiable";
        status_codes[417] = "417 Expectation Failed";
        status_codes[418] = "418 I'm a teapot";
        status_codes[421] = "421 Misdirected Request";
        status_codes[422] = "422 Unprocessable Entity";
        status_codes[423] = "423 Locked";
        status_codes[424] = "424 Failed Dependency";
        status_codes[426] = "426 Upgrade Required";
        status_codes[428] = "428 Precondition Required";
        status_codes[429] = "429 Too Many Requests";
        status_codes[431] = "431 Request Header Fields Too Large";
        status_codes[451] = "451 Unavailable For Legal Reasons";
        // 5** Server Error
        status_codes[500] = "500 Internal Server Error";
        status_codes[501] = "501 Not Implemented";
        status_codes[502] = "502 Bad Gateway";
        status_codes[503] = "503 Service Unavailable";
        status_codes[504] = "504 Gateway Timeout";
        status_codes[505] = "505 HTTP Version Not Supported";
        status_codes[506] = "506 Variant Also Negotiates";
        status_codes[507] = "507 Insufficient Storage";
        status_codes[508] = "508 Loop Detected";
        status_codes[510] = "510 Not Extended";
        status_codes[511] = "511 Network Authentication Required";
    }
};

#endif /* defined(__SecSock__HTTPHeaders__) */
