#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::string> found;
std::vector<std::string> notFound;

void lookLine(std::string lineA, std::ifstream &File1, std::ifstream &File2)
{
    bool lineFound = false;
    std::string lineB;
    // read File2 until match is found
    while (std::getline(File2, lineB))
    {
        if (lineA == lineB)
        {
            lineFound = true;
            found.push_back(lineA);
            break;
        }
    }
    if (!lineFound)
    {
        notFound.push_back(lineA);
    }
    // clear the state of File2 stream
    File2.clear();
    File2.seekg(0, std::ios::beg);
}

int main()
{
    std::ifstream FileC;
    FileC.open("pendingC.txt");
    std::ifstream FileJ;
    FileJ.open("pendingJ.txt");
    std::string line;

    while (std::getline(FileC, line))
    {
        lookLine(line, FileC, FileJ);
    }
    std::cout << "Not found : \n\n";
    for (auto s : notFound) {
        std::cout << s + "\n";
    }
}
