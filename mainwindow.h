#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include <iostream>
#include "frapmodel.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void background_file_open();
    void closedapp_file_open();
    void imagelist_file_open();
    void run_experiment();

signals:
    void primaset(QString prima);
    void closedset(QString closed);
    void doselection();
    void imagelistset(QStringList);
    
private:
    Ui::MainWindow *ui;

    bool set_background, set_closed, set_image_list;

    QString background_file_name;
    QString closedapp_file_name;
    QStringList image_string_list;

    FrapModel *frapmodel;

    QString starting_dir;
};

#endif // MAINWINDOW_H
