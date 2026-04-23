#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "compressanddecompress.h"
#include "encryptionanddecryption.h"
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("CipherZip");
    setWindowIcon(QIcon(":Downloads/zip-file_4029280.png"));
//    setWindowIcon(QIcon(":Downloads/icons8-file-management-flat-icons/icons8-file-management-100.png"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_compressbtn_clicked()
{
    CompressAndDecompress *compressAndDecompressWindow = new CompressAndDecompress(this);
    compressAndDecompressWindow->show();

    QTabWidget* tabWidget = compressAndDecompressWindow->getTabWidget();

    if (tabWidget)
    {
        tabWidget->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Tab Widget not found!");
    }

}


void MainWindow::on_quit_clicked()
{
    this->close();
}


void MainWindow::on_encryptbtn_clicked()
{
    EncryptionAndDecryption *encryptPanel = new EncryptionAndDecryption(this);
    encryptPanel->show();
    QTabWidget* tabWidget = encryptPanel->getTabWidget();
    if (tabWidget)
    {
        tabWidget->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Tab Widget not found!");
    }

}

void MainWindow::on_decompressbtn_clicked()
{
    CompressAndDecompress *compressAndDecompressWindow = new CompressAndDecompress(this);
    compressAndDecompressWindow->show();

    QTabWidget* tabWidget = compressAndDecompressWindow->getTabWidget();

    if (tabWidget)
    {
        tabWidget->setCurrentIndex(1);
    } else {
        QMessageBox::warning(this, "Error", "Tab Widget not found!");
    }
}


void MainWindow::on_decryptbtn_clicked()
{
    EncryptionAndDecryption *encryptPanel = new EncryptionAndDecryption(this);
    encryptPanel->show();
    QTabWidget* tabWidget = encryptPanel->getTabWidget();
    if (tabWidget)
    {
        tabWidget->setCurrentIndex(1);
    } else {
        QMessageBox::warning(this, "Error", "Tab Widget not found!");
    }
}

