#include <QFile>
#include <QString>
#include <QTextStream>
#include <fstream>
#include <QFileInfo>
#include <zlib.h>
#include "zlib.h"
#include <QtZlib/zlib.h>
#include "ui_compressanddecompress.h"
#include "mainwindow.h"
#include "compress.h"
#include "compressanddecompress.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QByteArray>
#include <QTextStream>

//#include "encrypt.h"
//#include "encrypt.cpp"

CompressAndDecompress::CompressAndDecompress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompressAndDecompress)
{
    ui->setupUi(this);


   connect(ui->cBack_2, &QPushButton::clicked, this, &CompressAndDecompress::goBackToMainWindow);
   connect(ui->DecomBack_2, &QPushButton::clicked, this, &CompressAndDecompress::goBackToMainWindow);
}

CompressAndDecompress::~CompressAndDecompress()
{
    delete ui;
}

void CompressAndDecompress::goBackToMainWindow()
{

    this->close();
}

void CompressAndDecompress::on_cBack_2_clicked()
{
    this->close();
}

void CompressAndDecompress::on_DecomBack_2_clicked()
{
    this->close();
}

void CompressAndDecompress::on_fetchfilecompress_clicked()
{
    QString inputFilePath = QFileDialog::getOpenFileName(
        this,
        "Select a file to compress",
        "",
        "Text Files (*.txt)"
        );

    if (inputFilePath.isEmpty())
    {
        return;
    }

    ui->filepathcompress->setText(inputFilePath);
}

void CompressAndDecompress::on_submitcompress_clicked()
{
    QString inputFilePath = ui->filepathcompress->text();
    QString outputFilePath = inputFilePath + ".gz";

    bool success = Compress::compressFile(inputFilePath.toStdString(), outputFilePath.toStdString());

    if (success)
    {
        QFile compressedFile(outputFilePath);
        if (compressedFile.open(QIODevice::ReadOnly))
        {
            QByteArray compressedData = compressedFile.readAll();
            compressedFile.close();
            QString rawCompressedText = QString::fromUtf8(compressedData);
            ui->compressoutput->setPlainText("File compressed successfully. Compressed Data:\n" + rawCompressedText);
        }
        else
        {
            ui->compressoutput->setPlainText("File compressed successfully: " + outputFilePath + "\nFailed to read the compressed file for display.");
        }
    }
    else
    {
        ui->compressoutput->setPlainText("Compression failed.");
    }
}

void CompressAndDecompress::on_SubmitdropboxdeDEcompress_2_clicked()
{
    QString dropboxFilePath = ui->DropboxFileNameDecompress_2->text();
    if (dropboxFilePath.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please enter a valid Dropbox file path.");
        return;
    }

    QString accessToken = "sl.CDlaLZ2Jt6Mn6yQDifLlI80hCBiiq-92FS4kl_SEskmvpnkPKn8P4g35cZnzHRvhzrps_kDZhRavJ7tvEAu0u_Pj64o-kbbp72pBgdJ54LhDYVTXu_bCQ2BBt9ODVqkFJUXa-hy5Iwf-VWh01Y7fmJw";

    QString localFilePath = "C:/Users/erha/OneDrive/Desktop/test.txt";

    Compress::fetchAndDecompressFile(dropboxFilePath, localFilePath, accessToken, ui->decompressoutput, this);
}

void CompressAndDecompress::on_fetchdecompress_clicked()
{
    QString inputFilePath = QFileDialog::getOpenFileName(
        this,
        "Select a file to decompress",
        "",
        "Compressed Files (*.gz *.zip *.txt)"
        );
    if (inputFilePath.isEmpty())
    {
        return;
    }

    ui->filepathDecompress_8->setText(inputFilePath);
}

void CompressAndDecompress::on_submitdecompress_clicked()
{
    QString inputFilePath = ui->filepathDecompress_8->text();

    QString outputFilePath = inputFilePath + "_decompressed.txt";

    bool success = Compress::decompressFile(inputFilePath.toStdString(), outputFilePath.toStdString());

    if (success)
    {
        QFile decompressedFile(outputFilePath);
        if (decompressedFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString decompressedContent = decompressedFile.readAll();
            decompressedFile.close();

            ui->decompressoutput->setPlainText("Decompressed Content:\n" + decompressedContent);
        }
        else
        {
            ui->decompressoutput->setPlainText("File decompressed successfully: " + outputFilePath + "\nFailed to read the decompressed file for display.");
        }
    }
    else
    {
        ui->decompressoutput->setPlainText("Decompression failed.");
    }
}
void CompressAndDecompress::on_cdownload_clicked()
{
    QString content = ui->compressoutput->toPlainText();

    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "C:/Users/erha/Desktop", "Text Files (*.txt)");
    // username
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << content;
            file.close();
            QMessageBox::information(this, "Success", "File saved successfully.");
        } else
        {
            QMessageBox::warning(this, "Error", "Could not save the file.");
        }
    }
}

void CompressAndDecompress::on_Submitdropboxcompress_2_clicked()
{
   QString dropboxFilePath = ui->DropboxFileName_2->text();
    if (dropboxFilePath.isEmpty())
   {
        QMessageBox::warning(this, "Error", "Please enter a valid Dropbox file path.");
        return;
    }

    QString accessToken = "sl.CDlaLZ2Jt6Mn6yQDifLlI80hCBiiq-92FS4kl_SEskmvpnkPKn8P4g35cZnzHRvhzrps_kDZhRavJ7tvEAu0u_Pj64o-kbbp72pBgdJ54LhDYVTXu_bCQ2BBt9ODVqkFJUXa-hy5Iwf-VWh01Y7fmJw";

    QString localFilePath = "C:/Users/erha/OneDrive/Desktop/test_compressed.txt";

    Compress::fetchAndCompressFile(dropboxFilePath, localFilePath, accessToken, ui->compressoutput, this);
}

void CompressAndDecompress::on_ddownload_clicked()
{
    QString content = ui->decompressoutput->toPlainText();

    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "C:/Users/erha/Desktop", "Text Files (*.txt)");

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << content;
            file.close();
            QMessageBox::information(this, "Success", "File saved successfully.");
        }
        else
        {
            QMessageBox::warning(this, "Error", "Could not save the file.");
        }
    }

}

