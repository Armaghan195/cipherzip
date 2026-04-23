#include "compress.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <zlib.h>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <qfile.h>
#include <QCoreApplication>
#include <qplaintextedit.h>

using namespace std;

bool Compress::compressFile(const string& inputFilePath, const string& outputFilePath) {
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

bool Compress::decompressFile(const string& inputFilePath, const string& outputFilePath) {
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


void Compress::fetchAndDecompressFile(const QString &dropboxFilePath, const QString &localFilePath, const QString &accessToken, QPlainTextEdit *outputTextEdit, QObject *parent)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(parent);
    QUrl url("https://content.dropboxapi.com/2/files/download");
    QNetworkRequest request(url);

    // Set headers
    QString authHeader = "Bearer " + accessToken;
    request.setRawHeader("Authorization", authHeader.toUtf8());

    QString dropboxArgHeader = QString("{\"path\": \"%1\"}").arg(dropboxFilePath);
    request.setRawHeader("Dropbox-API-Arg", dropboxArgHeader.toUtf8());

    QNetworkReply *reply = manager->post(request, QByteArray());

    // Handle the reply once the file is fetched
    connect(reply, &QNetworkReply::finished, [reply, localFilePath, accessToken, outputTextEdit]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Write the received file to a local temporary file
            QByteArray data = reply->readAll();
            ofstream outputFile(localFilePath.toStdString(), ios::binary);
            if (outputFile.is_open()) {
                outputFile.write(data.data(), data.size());
                outputFile.close();

                // Decompress the file
                string decompressedFilePath = "decompressed_output.txt";  // Path for decompressed content
                if (Compress::decompressFile(localFilePath.toStdString(), decompressedFilePath)) {
                    // Read the decompressed file and display its content in the QPlainTextEdit
                    QFile file(QString::fromStdString(decompressedFilePath));
                    if (file.open(QIODevice::ReadOnly)) {
                        QTextStream in(&file);
                        QString decompressedContent = in.readAll();

                        // Set the decompressed content to the provided QPlainTextEdit
                        outputTextEdit->setPlainText(decompressedContent);  // Display decompressed content
                        file.close();
                    } else {
                        QMessageBox::warning(nullptr, "Error", "Failed to open decompressed file.");
                    }
                } else {
                    QMessageBox::warning(nullptr, "Error", "Failed to decompress the file.");
                }
            } else {
                QMessageBox::warning(nullptr, "Error", "Failed to write to local file.");
            }
        } else {
            QMessageBox::warning(nullptr, "Error", "Failed to download the file from Dropbox: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void Compress::fetchAndCompressFile(const QString &dropboxFilePath, const QString &localFilePath, const QString &accessToken, QPlainTextEdit *outputTextEdit, QObject *parent)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(parent);
    QUrl url("https://content.dropboxapi.com/2/files/download");
    QNetworkRequest request(url);

    // Set headers
    QString authHeader = "Bearer " + accessToken;
    request.setRawHeader("Authorization", authHeader.toUtf8());

    QString dropboxArgHeader = QString("{\"path\": \"%1\"}").arg(dropboxFilePath);
    request.setRawHeader("Dropbox-API-Arg", dropboxArgHeader.toUtf8());

    QNetworkReply *reply = manager->post(request, QByteArray());

    // Handle the reply once the file is fetched
    connect(reply, &QNetworkReply::finished, [reply, localFilePath, accessToken, outputTextEdit]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Write the received file to a local temporary file
            QByteArray data = reply->readAll();
            ofstream outputFile(localFilePath.toStdString(), ios::binary);
            if (outputFile.is_open()) {
                outputFile.write(data.data(), data.size());
                outputFile.close();

                // Now use your existing compressFile function to compress the downloaded file
                string compressedFilePath = localFilePath.toStdString() + ".gz";  // Path for the compressed file
                if (Compress::compressFile(localFilePath.toStdString(), compressedFilePath)) {
                    // If compression succeeds, open and read the compressed file
                    QFile file(QString::fromStdString(compressedFilePath));
                    if (file.open(QIODevice::ReadOnly)) {
                        QByteArray compressedData = file.readAll();

                        // Display raw binary data as QByteArray
                        QString rawString = QString::fromUtf8(compressedData);

                        // Ensure the UI updates are done on the main thread
                        QMetaObject::invokeMethod(outputTextEdit, [outputTextEdit, rawString]() {
                            outputTextEdit->setPlainText(rawString);
                        });

                        file.close();
                    } else {
                        QMessageBox::warning(nullptr, "Error", "Failed to open the compressed file.");
                    }
                } else {
                    // If compression fails, show an error message
                    QMessageBox::warning(nullptr, "Error", "Failed to compress the file.");
                }
            } else {
                QMessageBox::warning(nullptr, "Error", "Failed to write to local file.");
            }
        } else {
            QMessageBox::warning(nullptr, "Error", "Failed to download the file from Dropbox: " + reply->errorString());
        }
        reply->deleteLater();
    });
}
