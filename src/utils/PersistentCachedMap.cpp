#include <utils/PersistentCachedMap.h>
#include <model/Gradient.h>
#include <model/Position.h>
#include <exception>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <dirent.h>
#include <experimental/filesystem>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

void PersistentCachedMap::persistObject(Position *key, Gradient *value)
{
    try
    {
        std::ofstream f(path + key->toString() + ".data" /*, std::ofstream::binary*/);
        boost::archive::text_oarchive oa{f};
        oa << value;
    }
    catch (std::exception &e)
    {
        std::cout << "RuntimeException : Can't write " + path + key->toString() + ".data";
    }
}

Gradient *PersistentCachedMap::recoverObject(std::string key)
{
    try
    {
        std::ifstream f(path + key + ".data" /*, std::ifstream::binary*/);
        boost::archive::text_iarchive ia{f};
        Gradient *a;
        ia >> a;
        return a;
    }
    catch (std::exception &e)
    {
        toc.erase(key); // Try and heal the list
        std::cerr << "RuntimeException : Can't read" + path + "-" + key + ".data, did u erase it manually ?\n";
    }
}

void PersistentCachedMap::putInCache(std::string key, Gradient *value)
{
    int repeated = getIndex(recent, key);

    if (repeated != -1)
    { // It's already there
        recent.erase(recent.begin() + repeated);
    }
    else
    {
        std::pair<std::string, Gradient *> pair(key, value);
        cache.insert(pair);
    }

    recent.push_back(key); // Refresh recent list

    if (cache.size() > cacheSize)
    { // Remove old element
        std::string to_erase = recent.at(0);
        recent.erase(recent.begin());
        cache.erase(to_erase);
        // System.out.println("Dropped element form cache");
    }
}

PersistentCachedMap::PersistentCachedMap(std::string basePath, std::string name, int cacheSize)
{
    this->cacheSize = cacheSize;
    this->recent.reserve(cacheSize);
    this->path = basePath + name + "/";

    const char *pathUsed = path.c_str();

    DIR *dir = opendir(pathUsed);

    if (ENOENT == errno)
    {
        std::cerr << "RuntimeException : Can't open " + path + "\n";
    }

    std::string ext(".data");
    std::vector<std::string> files;
    std::ifstream file;
    std::string filename;

    for (auto &p : std::experimental::filesystem::directory_iterator(path))
    {
        if (p.path().extension() == ext)
        {

            filename = p.path().string(); // UPDATE : p.path().stem().string(); ---> without extension
            file = std::ifstream{name};
            //std::cout << name << '\n';
            if (!file)
            {
                std::cout << "File is missing : " + filename + ", no entry inside map\n";
            }
            else
            {
                toc.insert(p.path().stem().string());
            }
        }
    }
}

void PersistentCachedMap::put(Position *key, Gradient *value)
{
    if ((key == nullptr) || (value == nullptr))
    {
        std::cerr << "NullPointerException\n";
    }

    if (key->toString().length() > MAX_KEY_LENGTH)
    {
        std::cerr << "IllegalArgumentException : You tried to add a key whose toString method yielded a string over 250 chars\n";
    }

    if (!toc.count(key->toString()))
    {
        // oldValue = get(key);
        persistObject(key, value);
        toc.insert(key->toString());
        putInCache(key->toString(), value);
    }
}

Gradient *PersistentCachedMap::get(std::string key)
{
    if (key.empty())
    {
        std::cerr << "NullPointerException\n";
    }

    if (!toc.count(key))
    {
        return nullptr;
    }
    else
    {
        Gradient *value;

        if (std::find(recent.begin(), recent.end(), key) != recent.end())
        {
            value = cache[key];
        }
        else
        {
            value = recoverObject(key);
            putInCache(key, value);
        }

        return value;
    }
}

bool PersistentCachedMap::containsKey(std::string key)
{
    return toc.count(key);
}