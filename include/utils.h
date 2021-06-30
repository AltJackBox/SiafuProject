#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <unistd.h>

inline void pwd()
{
    char buffer[256];
    char *val = getcwd(buffer, sizeof(buffer));
    if (val)
    {
        std::cout << buffer << std::endl;
    }
}

inline bool ends_with(std::string const &value, std::string const &ending)
{
    if (ending.size() > value.size())
        return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

inline int getIndex(std::vector<std::string> v, std::string K)
{
    int index = 0;
    while (index != v.size()){
        if (v[index].compare(K) == 0) {
            return index;
        }
        index++;
    }
    return -1;
}

#endif