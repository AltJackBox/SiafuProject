#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::string> found;
std::vector<std::string> notFound;

// Lines to add to write a file to compare

//C++

// if (pending.size() == 96) {
//     std::ofstream f("pendingC.txt");
//     for (auto pos : pending)
//     {
//         f << pos->toString() + "\n";
//     }
//     f.close();
// }

//JAVA

// PrintWriter writer;
// try
// {
//     writer = new PrintWriter("wallsJ.txt", "UTF-8");
//     writer.print("1 ");
//     writer.close();
// }
// catch (FileNotFoundException e)
// {
//     // TODO Auto-generated catch block
//     e.printStackTrace();
// }
// catch (UnsupportedEncodingException e)
// {
//     // TODO Auto-generated catch block
//     e.printStackTrace();
// }

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

    // Compare the content of 2 files (the lines can be in different order in the 2 files)

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
    for (auto s : notFound)
    {
        std::cout << s + "\n";
    }
}
