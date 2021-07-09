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
    while (index != v.size())
    {
        if (v[index].compare(K) == 0)
        {
            return index;
        }
        index++;
    }
    return -1;
}

inline int signum(double x)
{
    if (x > 0)
        return 1;
    if (x < 0)
        return -1;
    return 0;
}

// Java's algorithms to calculate the hashcode of a string

inline int hashCode(std::string value) 
{
    int h = 0;
    if (value.length() > 0)
    {
        const char *val = value.c_str();

        for (int i = 0; i < value.length(); i++)
        {
            h = 31 * h + val[i];
        }
    }
    return h;
}

// inline int hash(std::string key)
// {
//     int h;
//     return h = hashCode(key) ^ (h >>> 16);
// }

#endif