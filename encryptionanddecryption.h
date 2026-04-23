#ifndef ENCRYPTIONANDDECRYPTION_H
#define ENCRYPTIONANDDECRYPTION_H
#include "ui_encryptionanddecryption.h"
#include <QWidget>
#include <QTabWidget>

namespace Ui {
class EncryptionAndDecryption;
}

class EncryptionAndDecryption : public QWidget
{
    Q_OBJECT

public:
    explicit EncryptionAndDecryption(QWidget *parent = nullptr);
    ~EncryptionAndDecryption();
    QTabWidget* getTabWidget() const { return ui->tabWidget; };


private slots:
    void on_esubmit_clicked();

    void on_eback_clicked();

    void on_dback_clicked();

    void on_dsubmit_clicked();

    void on_decrypt_clicked();

    void on_ddownload_clicked();

    void on_ebrowse_clicked();

    void on_encrypt_clicked();

    void on_edownload_clicked();

    void on_decrypt_2_clicked();

    void on_encrypt_2_clicked();

    void on_ddsubmit_clicked();

    void on_decryptt_clicked();

private:
    Ui::EncryptionAndDecryption *ui;
};

#endif // ENCRYPTIONANDDECRYPTION_H
