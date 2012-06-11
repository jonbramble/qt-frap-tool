#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include <iostream>

#include <fraptool/frap.h>

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
    
private:
    Ui::MainWindow *ui;

    bool set_background, set_closed, set_image_list;

    QString background_file_name;
    QString closedapp_file_name;
    QStringList image_string_list;
    std::vector<std::string> ifiles;

    FrapTool::Frap *experiment;

    QString starting_dir;

    static std::string qStringToSTLString(const QString& qstring);
};

#endif // MAINWINDOW_H
