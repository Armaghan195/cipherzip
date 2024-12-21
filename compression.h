#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <string>
using namespace std;

class Compression {
public:
    static bool compressFile(const string& inputFilePath, const string& outputFilePath);
    static bool decompressFile(const string& inputFilePath, const string& outputFilePath);
};

#endif
