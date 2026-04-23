#ifndef COMPRESSANDDECOMPRESS_H
#define COMPRESSANDDECOMPRESS_H

#include <QWidget>
#include <QTabWidget>
#include "ui_compressanddecompress.h"

namespace Ui {
class CompressAndDecompress;
}

class CompressAndDecompress : public QWidget
{
    Q_OBJECT

public:
    explicit CompressAndDecompress(QWidget *parent = nullptr);
    ~CompressAndDecompress();

    QTabWidget* getTabWidget() const { return ui->tabWidget; }   // Ui::CompressAndDecompress *ui;


private slots:
    void goBackToMainWindow();

    void on_SubmitFilePathfilehandle_2_clicked();

    void on_browsefile_clicked();

    void on_Submitdropboxcompress_10_clicked();

    void on_SubmitFilePathcompress_10_clicked();

    void on_compressButton_clicked();

    void on_cBack_2_clicked();

    void on_DecomBack_2_clicked();

    void on_fetchfilecompress_clicked();

    void on_submitcompress_clicked();

    void on_fetchfiledecompress_clicked();

    void on_submitdecompress_clicked();

    void on_FetchFileDecompress_2_clicked();

    void on_SubmitdropboxdeDEcompress_2_clicked();

    void on_fetchdecompress_clicked();

    void on_cdownload_clicked();

    void on_Submitdropboxcompress_2_clicked();

    void on_ddownload_clicked();


private:
    std::string data;
    Ui::CompressAndDecompress *ui;


};


#endif // COMPRESSANDDECOMPRESS_H
