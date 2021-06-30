#include <utils/PersistentCachedMap.h>
#include <model/Gradient.h>
#include <model/Position.h>
#include <exception>
#include <iostream>
#include <algorithm>

bool FilenameFilter::accept(const std::string fileName)
{
    return fileName.find(".data") != std::string::npos;
}

// void PersistentCachedMap::persistObject( Position* key,  Gradient* value)
// {
//     try
//     {
//         FileOutputStream fOut = new FileOutputStream(path + key + ".data");
//         GZIPOutputStream gzFOut = new GZIPOutputStream(fOut);
//         ObjectOutputStream objOut = new ObjectOutputStream(gzFOut);
//         objOut.writeObject(value);

//         gzFOut.finish();
//         gzFOut.close();
//         objOut.close();
//     }
//     catch (std::exception& e)
//     {
//         std::cout << "RuntimeException : Can't write " + path + value + ".data");
//     }
// }

// Object recoverObject(final Object key)
// {
//     try
//     {
//         FileInputStream fIn = new FileInputStream(path + key + ".data");
//         GZIPInputStream gzFIn = new GZIPInputStream(fIn);
//         ObjectInputStream objIn = new ObjectInputStream(gzFIn);
//         Object obj = objIn.readObject();
//         gzFIn.close();
//         objIn.close();
//         return obj;
//     }
//     catch (Exception e)
//     {
//         toc.remove(key.toString()); // Try and heal the list
//         e.printStackTrace();
//         throw new RuntimeException("Can't read" + path + "-" + key + ".data, did u erase it manually?");
//     }
// }

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