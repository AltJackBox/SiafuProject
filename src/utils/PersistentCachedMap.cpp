#include <utils/PersistentCachedMap.h>
#include <model/Gradient.h>
#include <model/Position.h>
#include <exceptions/NullPointerException.h>
#include <utils.h>
#include <exception>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <dirent.h>
#include <experimental/filesystem>

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

void PersistentCachedMap::persistObject(Position *key, Gradient *value)
{

    Position *pos = value->getCenter();
    int w = value->getWidth();
    int h = value->getHeight();
    std::vector<int> vec = value->getDistance();
    try
    {
        std::ofstream f(path + key->toString() + ".data");
        cereal::BinaryOutputArchive oarchive(f);

        oarchive(w, h, pos->getRow(), pos->getCol(), vec);
        delete pos;
        delete value;
    }
    catch (std::exception &e)
    {
        throw std::runtime_error("Can't write " + path + key->toString() + ".data");
        delete pos;
        
    }
}

Gradient *PersistentCachedMap::recoverObject(std::string key)
{
    try
    {
        std::ifstream f(path + key + ".data");
        cereal::BinaryInputArchive iarchive(f); // Create an input archive

        int w, h, centerI, centerJ;
        std::vector<int> vec;
        iarchive(w, h, centerI, centerJ, vec); // Read the data from the archive
        return new Gradient(new Position(centerI, centerJ), h, w, vec);
    }
    catch (std::exception &e)
    {
        toc.erase(key); // Try and heal the list
        throw std::runtime_error("Can't read" + path + "-" + key + ".data, did u erase it manually ?");
        
    }
    return nullptr;
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
        throw std::runtime_error("Can't open " + path);
        
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
            file = std::ifstream{filename};
            //std::cout << name << '\n';
            toc.insert(p.path().stem().string());
        }
    }
}

void PersistentCachedMap::put(Position *key, Gradient *value)
{
    if ((key == nullptr) || (value == nullptr))
    {
        throw NullPointerException("Putting null value/key inside PersistentCachedMap");       
    }

    if (key->toString().length() > MAX_KEY_LENGTH)
    {
        throw std::invalid_argument("You tried to add a key whose toString method yielded a string over 250 chars");
        
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
        throw NullPointerException("Getting null key inside PersistentCachedMap");
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