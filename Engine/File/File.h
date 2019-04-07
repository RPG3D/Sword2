#pragma once

#include <string>
#include <vector>

class File
{
private:
    File();
    virtual ~File();
public:
    static bool fileExist(const std::string& filename);
    static bool readFile(const std::string& fileName, char** s, int* len);
    static void readFile(const std::string& fileName, void* s, int len);
    static void writeFile(const std::string& fileName, void* s, int len);

    template <class T> static void readDataToVector(char* data, int length, std::vector<T>& v)
    {
        readDataToVector(data, length, v, sizeof(T));
    }

    template <class T> static void readDataToVector(char* data, int length, std::vector<T>& v, int length_one)
    {
        int count = length / length_one;
        v.resize(count);
        for (int i = 0; i < count; i++)
        {
            memcpy(&v[i], data + length_one * i, length_one);
        }
    }

    template <class T> static void readFileToVector(std::string filename, std::vector<T>& v)
    {
        char* buffer = nullptr;
        int length;
        if (readFile(filename, &buffer, &length))
        {
            readDataToVector(buffer, length, v);
            delete[] buffer;
        }
    }

    template <class T> static void writeVectorToData(char* data, int length, std::vector<T>& v, int length_one)
    {
        int count = length / length_one;
        v.resize(count);
        for (int i = 0; i < count; i++)
        {
            memcpy(data + length_one * i, &v[i], length_one);
        }
    }

    static char* getIdxContent(std::string filename_idx, std::string filename_grp, std::vector<int>* offset, std::vector<int>* length);
};

