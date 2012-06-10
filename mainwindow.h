#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString background_file_name;
    QString closedapp_file_name;

public slots:
    void background_file_open();
    void closedapp_file_open();
    void imagestack_file_open();
    //void
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
