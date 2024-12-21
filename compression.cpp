#include "compression.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <zlib.h>
using namespace std;

bool Compression::compressFile(const string& inputFilePath, const string& outputFilePath) {
    ifstream inputFile(inputFilePath, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Cannot open input file: " << inputFilePath << endl;
        return false;
    }

    vector<char> inputBuffer((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    uLongf compressedSize = compressBound(inputBuffer.size());
    vector<char> compressedBuffer(compressedSize);

    if (compress((Bytef*)compressedBuffer.data(), &compressedSize, (const Bytef*)inputBuffer.data(), inputBuffer.size()) != Z_OK) {
        cerr << "Compression failed." << endl;
        return false;
    }

    ofstream outputFile(outputFilePath, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Cannot open output file: " << outputFilePath << endl;
        return false;
    }

    outputFile.write(compressedBuffer.data(), compressedSize);
    outputFile.close();

    return true;
}

bool Compression::decompressFile(const string& inputFilePath, const string& outputFilePath) {
    ifstream inputFile(inputFilePath, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Cannot open input file: " << inputFilePath << endl;
        return false;
    }

    vector<char> compressedBuffer((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    uLongf decompressedSize = compressedBuffer.size() * 5; // Assuming max decompression size.
    vector<char> decompressedBuffer(decompressedSize);

    while (uncompress((Bytef*)decompressedBuffer.data(), &decompressedSize, (const Bytef*)compressedBuffer.data(), compressedBuffer.size()) == Z_BUF_ERROR) {
        decompressedSize *= 2;
        decompressedBuffer.resize(decompressedSize);
    }

    ofstream outputFile(outputFilePath, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Cannot open output file: " << outputFilePath << endl;
        return false;
    }

    outputFile.write(decompressedBuffer.data(), decompressedSize);
    outputFile.close();

    return true;
}
