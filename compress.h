#ifndef COMPRESS_H
#define COMPRESS_H

#include <string>
#include <QObject>
#include <QPlainTextEdit>


using namespace std;

class Compress : public QObject {
    Q_OBJECT
public:
    static bool compressFile(const string& inputFilePath, const string& outputFilePath);
    static bool decompressFile(const string& inputFilePath, const string& outputFilePath);
    static void fetchAndDecompressFile(const QString &dropboxFilePath, const QString &localFilePath, const QString &accessToken, QPlainTextEdit *outputTextEdit, QObject *parent);
    static void fetchAndCompressFile(const QString &dropboxFilePath, const QString &localFilePath, const QString &accessToken, QPlainTextEdit *outputTextEdit, QObject *parent);

signals:
    void fileDownloaded(const QString& filePath); // Signal for successful download
    void downloadFailed(const QString& error);   // Signal for errors
};

#endif
