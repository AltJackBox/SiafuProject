#ifndef PERSISTENTCACHEDMAP_H
#define PERSISTENTCACHEDMAP_H

#include <model/Gradient.h>
#include <utils.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class FilenameFilter
{
public:
    FilenameFilter();
    bool accept(const std::string fileName);
};

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

    PersistentCachedMap(std::string basePath, std::string name, int cacheSize, bool fillCache);
    // {
    //     this->cacheSize = cacheSize;
    //     this->recent.reserve(cacheSize);
    //     this->path = basePath + name + "/";

    //     File dir = new File(path);

    //     if (!dir.exists())
    //     {
    //         std::cout << "\nCreating directory for the persisted map in " + path + "\n";

    //         if (!dir.mkdirs())
    //         {
    //             std::cerr << "RuntimeException : Can't create " + path + "\n";
    //         }
    //     }
    //     else if (!dir.isDirectory())
    //     {
    //         std::cerr << "The file " + path + " is in the way, please remove it\n";
    //     }

    //     FilenameFilter *filt = new FilenameFilter();

    //     std::string files[] = dir.list(filter);

    //     if (files != null)
    //     {
    //         for (int i = 0; i < files.length; i++)
    //         {
    //             // file name format is: key.data
    //             int end = files[i].lastIndexOf(".");
    //             toc.add(files[i].substring(0, end));
    //         }
    //     }
    // }

    void put(Position *key, Gradient *value);

    Gradient *get(std::string key);

    bool containsKey(std::string key);
};

#endif
