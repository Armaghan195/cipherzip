#include "encryptionanddecryption.h"
#include "ui_encryptionanddecryption.h"
#include "encryption.h"
#include <QFile>
#include <QString>
#include <fstream>
#include <QFileInfo>
#include <zlib.h>
#include "zlib.h"
#include <QtZlib/zlib.h>
#include "mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QTextStream>

EncryptionAndDecryption::EncryptionAndDecryption(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EncryptionAndDecryption)
{
    ui->setupUi(this);
}

EncryptionAndDecryption::~EncryptionAndDecryption()
{
    delete ui;
}


void EncryptionAndDecryption::on_eback_clicked()
{
    this->close();
}


void EncryptionAndDecryption::on_dback_clicked()
{
    this->close();
}


void EncryptionAndDecryption::on_dsubmit_clicked()
{
    //d file path

    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Text File"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (!filePath.isEmpty())
    {
        ui->dfilepath->setText(filePath);
    }
}

void EncryptionAndDecryption::on_ddownload_clicked()
{
    //download decrypted
    QString decryptedText = ui->doutput->toPlainText();

    if (decryptedText.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"), tr("No decrypted content available to download."));
        return;
    }

    QString savePath = QFileDialog::getSaveFileName(this, tr("Save Decrypted File"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (!savePath.isEmpty())
    {
        QFile file(savePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << decryptedText;
            file.close();
            QMessageBox::information(this, tr("Success"), tr("File has been saved successfully!"));
        }
        else
        {
            QMessageBox::warning(this, tr("Error"), tr("Failed to save the file."));
        }
    }
}


void EncryptionAndDecryption::on_ebrowse_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Text File"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (!filePath.isEmpty())
    {
        ui->efilepath->setText(filePath);
    }
}


void EncryptionAndDecryption::on_encrypt_clicked()
{
    QString filePath = ui->efilepath->text();
    QString key = ui->ebox->text();

    if (filePath.isEmpty() || key.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"), tr("Please provide both a file path and a key."));
        return;
    }

    std::ifstream inputFile(filePath.toStdString());
    if (!inputFile.is_open())
    {
        QMessageBox::warning(this, tr("Error"), tr("Unable to open the input file."));
        return;
    }

    // add inputfile
    std::string plaintext((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    listnode* plaintextHead = encryption::createlinkedlist(plaintext);
    //abc becomes A-b c nd null
    listnode* keyHead = encryption::generatekeylist(plaintextHead, key.toStdString());
    //xy becomes x y x
    listnode* ciphertextHead = encryption::encrypttext(plaintextHead, keyHead);
    // a plus x then b plus y and c plus x
    std::string encryptedText = encryption::linkedlisttostring(ciphertextHead);
    // result of ax by cx
    ui->eoutput->setPlainText(QString::fromStdString(encryptedText));

    encryption::deletelinkedlist(plaintextHead);
    encryption::deletelinkedlist(keyHead);
    encryption::deletelinkedlist(ciphertextHead);
}


void EncryptionAndDecryption::on_edownload_clicked()
{
    QString encryptedText = ui->eoutput->toPlainText();

    if (encryptedText.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"), tr("No encrypted content available to download."));
        return;
    }

    QString savePath = QFileDialog::getSaveFileName(this, tr("Save Encrypted File"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (!savePath.isEmpty())
    {
        QFile file(savePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << encryptedText;
            file.close();
            QMessageBox::information(this, tr("Success"), tr("File has been saved successfully!"));
        }
        else
        {
            QMessageBox::warning(this, tr("Error"), tr("Failed to save the file."));
        }
    }
}

void EncryptionAndDecryption::on_encrypt_2_clicked()
{
    QString dropboxFilePath = ui->efilepath_2->text();
    QString localFilePath = "C:/Users/erha/OneDrive/Desktop";
    QString accessToken = "sl.CDlaLZ2Jt6Mn6yQDifLlI80hCBiiq-92FS4kl_SEskmvpnkPKn8P4g35cZnzHRvhzrps_kDZhRavJ7tvEAu0u_Pj64o-kbbp72pBgdJ54LhDYVTXu_bCQ2BBt9ODVqkFJUXa-hy5Iwf-VWh01Y7fmJw";

    QString encryptionKey = ui->ebox_2->text();

    if (dropboxFilePath.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please enter a valid Dropbox file path.");
        return;
    }
    if (encryptionKey.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please enter a valid encryption key.");
        return;
    }

   //if (!ui->eoutput)
    //{
     //  QMessageBox::warning(this, "Error", "Output display widget is not available.");
     //  return;
    //}

    encryption::fetchAndEncryptFile(dropboxFilePath, localFilePath, accessToken, encryptionKey, ui->eoutput, this);

}

void EncryptionAndDecryption::on_ddsubmit_clicked()
{
    QString dropboxFilePath = ui->ddropboxname->text();
    QString localFilePath = "C:/Users/erha/OneDrive/Desktop";
    QString accessToken = "sl.CDlaLZ2Jt6Mn6yQDifLlI80hCBiiq-92FS4kl_SEskmvpnkPKn8P4g35cZnzHRvhzrps_kDZhRavJ7tvEAu0u_Pj64o-kbbp72pBgdJ54LhDYVTXu_bCQ2BBt9ODVqkFJUXa-hy5Iwf-VWh01Y7fmJw";
    QString encryptionKey = ui->ddkey->text();

    if (dropboxFilePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a valid Dropbox file path.");
        return;
    }
    if (encryptionKey.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a valid encryption key.");
        return;
    }

    //    if (!ui->eoutput)
    //    {
  //      QMessageBox::warning(this, "Error", "Output display widget is not available.");
    //    return;
    //}
    encryption::fetchAndDecryptFile(dropboxFilePath, localFilePath, accessToken, encryptionKey, ui->doutput, this);
}

void EncryptionAndDecryption::on_decryptt_clicked()
{
    // Decryption

    QString filePath = ui->dfilepath->text();
    QString key = ui->dkey->text();

    if (filePath.isEmpty() || key.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"), tr("Please provide both a file path and a key."));
        return;
    }

    std::ifstream inputFile(filePath.toStdString());
    if (!inputFile.is_open())
    {
        QMessageBox::warning(this, tr("Error"), tr("Unable to open the input file."));
        return;
    }

    std::string ciphertext((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    listnode* ciphertextHead = encryption::createlinkedlist(ciphertext);
    listnode* keyHead = encryption::generatekeylist(ciphertextHead, key.toStdString());
    listnode* plaintextHead = encryption::decrypttext(ciphertextHead, keyHead);
    std::string decryptedText = encryption::linkedlisttostring(plaintextHead);

    ui->doutput->setPlainText(QString::fromStdString(decryptedText));

    encryption::deletelinkedlist(ciphertextHead);
    encryption::deletelinkedlist(keyHead);
    encryption::deletelinkedlist(plaintextHead);
}
