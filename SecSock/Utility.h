//
//  Utility.h
//  SecSock
//
//  Created by dtl on 21/04/2016.
//  Copyright (c) 2016 LiosMor Security. All rights reserved.
//

#ifndef SecSock_Utility_h
#define SecSock_Utility_h

#include <type_traits>
#include <string>

template<typename Type>
inline static int nthSubstr(int n,
                            const std::basic_string<Type> &str,
                            const std::basic_string<Type> &sub,
                            bool sub_repeats = false)
{
    std::string::size_type pos = str.find(sub);
    std::string::size_type nxt = (sub_repeats) ? 1 : sub.length();
    int i;
    for(i = 1; i < n && pos != std::basic_string<Type>::npos; ++i)
        pos = str.find(sub, pos + nxt);
    if (i == n)
        return(static_cast<int>(pos));
    else
        return(-1);
}


template<typename Type>
inline static Type countDigits(Type n, unsigned int base)
{
    static_assert(std::is_integral<Type>::value, "Integer required.");
    unsigned int num_digits = 0;
    do
    {
        ++num_digits;
        n /= base;
    }
    while(n != 0);
    return num_digits;
}

#endif
