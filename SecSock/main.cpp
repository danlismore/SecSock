//
//  main.cpp
//  SecSock
//
//  Created by dtl on 21/03/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#include <iostream>
#include "ServerConnect.h"

int main(int argc, const char * argv[]) {
    ServerConnect server("0.0.0.0", 60000);
    server.startServer();
    return 0;
}
