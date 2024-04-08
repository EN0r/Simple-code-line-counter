// lineCounter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

bool find(std::string origin,std::string f)
{
    int it = origin.find(f);
    std::string strBuf;
    for (size_t i = it; i < origin.size(); i++)
    {
        strBuf += origin[i];
    }
    if (strBuf == f)
        return true;
    return false;
}

int main(int argc, char* argv[])// Syntax ./ lineCounter -.h -.c -.cpp
{
    std::fstream fileStream;
    std::string path = "./";
    std::vector<std::string> fileTypes;
    std::vector<std::string> paths;
    std::vector<std::string> validPaths;
    std::string tempBuf; // literally not required
    if(argc < 0)
    {
        for (auto i = 0; i < argc; i++)
        {
            std::string conversion(argv[i]);
            std::string strBuf;
            if (conversion[0] != '-')
                std::cout << "Invalid argument type!" << " Argument: " << i << std::endl;
            for (auto c : conversion)
            {
                if (c == '-')
                    continue;
                strBuf += c;
            }
            fileTypes.push_back(strBuf);
        }
    }
    int linecount = 0;
    for (auto file : std::filesystem::directory_iterator(path))
        paths.push_back(file.path().filename().string());
    for (auto x : paths)
    {
        int i = 0;
        for (auto ch : fileTypes)
        {
            i++;
            if (find(x, ch))
                validPaths.push_back(x);
            else
                continue;
        }
    }
    for (auto file : validPaths)
    {
        fileStream.open((path + file));
        while (std::getline(fileStream, tempBuf))
            linecount++;
        fileStream.close();
    }
    std::cout << "Lines of code: " << linecount << std::endl;
    return 0;
}