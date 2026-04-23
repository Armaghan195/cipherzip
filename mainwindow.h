#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_compressbtn_clicked();

    void on_quit_clicked();

    void on_encryptbtn_clicked();

    void on_compressbtn_2_clicked();

    void on_decompressbtn_clicked();

    void on_decryptbtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
