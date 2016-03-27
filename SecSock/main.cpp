//
//  main.cpp
//  SecSock
//
//  Created by dtl on 21/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#include <iostream>
#include <future>
#include <thread>
#include "ServerConnect.h"
#include "HTTP.h"

int main(int argc, const char * argv[]) {
    ServerConnect server("127.0.0.1", 6001, false);
    server.startServer();
    return 0;
}
