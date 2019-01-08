// Aristos Athens

//
// Compiler guard
//

#ifndef UTIL_H
#define UTIL_H

//
// Include
//

#include <iostream>

//
// Functions
//
template<typename T>
void print(T val)
{
    std::cout << val;
}

template<typename T>
void println(T val)
{
    print(val);
    print("\n");
}

#endif // UTIL_H