//
//  HTTP.cpp
//  SecSock
//
//  Created by dtl on 26/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#include <algorithm>
#include "HTTP.h"

using std::find;

HTTP::HTTP()
{
    initStatusCodes();
}

void HTTP::initStatusCodes()
{
    // 1** Informational
    status_codes.insert(make_pair(100, "100 Continue"));
    status_codes.insert(make_pair(101, "101 Switching Protocols"));
    status_codes.insert(make_pair(102, "102 Processing"));
    // 2** Success
    status_codes.insert(make_pair(200, "200 OK"));
    status_codes.insert(make_pair(201, "201 Created"));
    status_codes.insert(make_pair(202, "202 Accepted"));
    status_codes.insert(make_pair(203, "203 Non-Authoritative Information"));
    status_codes.insert(make_pair(204, "204 No Content"));
    status_codes.insert(make_pair(205, "205 Reset Content"));
    status_codes.insert(make_pair(206, "206 Partial Content"));
    status_codes.insert(make_pair(207, "207 Multi-status_codes"));
    status_codes.insert(make_pair(208, "208 Already Reported"));
    status_codes.insert(make_pair(226, "226 IM Used"));
    // 3** Redirection
    status_codes.insert(make_pair(300, "300 Multiple Choices"));
    status_codes.insert(make_pair(301, "301 Moved permanently"));
    status_codes.insert(make_pair(302, "302 Found"));
    status_codes.insert(make_pair(303, "303 See Other"));
    status_codes.insert(make_pair(304, "304 Not Modified"));
    status_codes.insert(make_pair(305, "305 Use Proxy"));
    status_codes.insert(make_pair(306, "306 Switch Proxy"));
    status_codes.insert(make_pair(307, "307 Temporary Redirect"));
    status_codes.insert(make_pair(308, "308 Permanent Redirect"));
    // 4** Client Error
    status_codes.insert(make_pair(400, "400 Bad Request"));
    status_codes.insert(make_pair(401, "401 Unauthorized"));
    status_codes.insert(make_pair(402, "402 Payment Required"));
    status_codes.insert(make_pair(403, "403 Forbidden"));
    status_codes.insert(make_pair(404, "404 Not Found"));
    status_codes.insert(make_pair(405, "405 Method Not Allowed"));
    status_codes.insert(make_pair(406, "406 Not Acceptable"));
    status_codes.insert(make_pair(407, "407 Proxy Authentication Required"));
    status_codes.insert(make_pair(408, "408 Request Timeout"));
    status_codes.insert(make_pair(409, "409 Conflict"));
    status_codes.insert(make_pair(410, "410 Gone"));
    status_codes.insert(make_pair(411, "411 Length Required"));
    status_codes.insert(make_pair(412, "412 Precondition Failed"));
    status_codes.insert(make_pair(413, "413 Payload Too Large"));
    status_codes.insert(make_pair(414, "414 URI Too Long"));
    status_codes.insert(make_pair(415, "415 Unsupported Media Type"));
    status_codes.insert(make_pair(416, "416 Range Not Satisfiable"));
    status_codes.insert(make_pair(417, "417 Expectation Failed"));
    status_codes.insert(make_pair(418, "418 I'm a teapot"));
    status_codes.insert(make_pair(421, "421 Misdirected Request"));
    status_codes.insert(make_pair(422, "422 Unprocessable Entity"));
    status_codes.insert(make_pair(423, "423 Locked"));
    status_codes.insert(make_pair(424, "424 Failed Dependency"));
    status_codes.insert(make_pair(426, "426 Upgrade Required"));
    status_codes.insert(make_pair(428, "428 Precondition Required"));
    status_codes.insert(make_pair(429, "429 Too Many Requests"));
    status_codes.insert(make_pair(431, "431 Request Header Fields Too Large"));
    status_codes.insert(make_pair(451, "451 Unavailable For Legal Reasons"));
    // 5** Server Error
    status_codes.insert(make_pair(500, "500 Internal Server Error"));
    status_codes.insert(make_pair(501, "501 Not Implemented"));
    status_codes.insert(make_pair(502, "502 Bad Gateway"));
    status_codes.insert(make_pair(503, "503 Service Unavailable"));
    status_codes.insert(make_pair(504, "504 Gateway Timeout"));
    status_codes.insert(make_pair(505, "505 HTTP Version Not Supported"));
    status_codes.insert(make_pair(506, "506 Variant Also Negotiates"));
    status_codes.insert(make_pair(507, "507 Insufficient Storage"));
    status_codes.insert(make_pair(508, "508 Loop Detected"));
    status_codes.insert(make_pair(510, "510 Not Extended"));
    status_codes.insert(make_pair(511, "511 Network Authentication Required"));
}

string HTTP::getStatusCode(unsigned short status_code)
{
    map<const unsigned short, const string>::iterator status_it;
    status_it = status_codes.find(status_code);
    return status_it->second;
}

string HTTP::parseAndRespond(vector<char> request)
{
    vector<char>::iterator posf, posl;
    posf = find(request.begin(), request.end(), ' ');
    string request_type(request.begin(), posf);
    return request_type;
}

string HTTP::getFiletype(string filename)
{
    if(filename.find(".html") != string::npos)
        return "text/html";
    else if(filename.find(".gif") != string::npos)
        return "image/gif";
    else if(filename.find(".jpg") != string::npos)
        return "image/jpeg";
    else
        return "text/plain";
}