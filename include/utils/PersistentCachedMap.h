#ifndef PERSISTENTCACHEDMAP_H
#define PERSISTENTCACHEDMAP_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Gradient;
class Position;

class PersistentCachedMap
{

protected:
    int cacheSize;

    std::string path;

    std::unordered_map<std::string, Gradient *> cache;

    std::vector<std::string> recent;

    std::unordered_set<std::string> toc;

    void persistObject(Position *key, Gradient *value);

    Gradient *recoverObject(std::string key);

private:
    void putInCache(std::string key, Gradient *value);

public:
    static const int MAX_KEY_LENGTH = 250;

    PersistentCachedMap(std::string basePath, std::string name, int cacheSize);

    void put(Position *key, Gradient *value);

    Gradient *get(std::string key);

    bool containsKey(std::string key);
};

#endif
