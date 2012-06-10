#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frap.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionBackground, SIGNAL(triggered()), this, SLOT(background_file_open()));
    connect(ui->actionClosed_Aperature, SIGNAL(triggered()), this, SLOT(closedapp_file_open()));
    connect(ui->actionImage_Stack, SIGNAL(triggered()), this, SLOT(imagestack_file_open()));

    //FrapTool::Frap *experiment;

    //experiment = new FrapTool::Frap("/home/jon/Programming/frap-tool/prima.tif","/home/jon/Programming/frap-tool/prima.tif",false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::background_file_open()
{
    background_file_name = QFileDialog::getOpenFileName(this, tr("Open Background Image"), "",
                                                    tr("Tiff Files (*.tif)"));

    if (background_file_name != "") {
        QFile file(background_file_name);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        //QTextStream in(&file);
        //textEdit->setText(in.readAll());
        file.close();
        std::cout<< qPrintable(background_file_name) << std::endl;
    }
}

void  MainWindow::closedapp_file_open(){
    closedapp_file_name = QFileDialog::getOpenFileName(this, tr("Open Closed Aperature Image"), "",
                                                    tr("Tiff Files (*.tif)"));

    if (closedapp_file_name != "") {
        QFile file(closedapp_file_name);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        //QTextStream in(&file);
        //textEdit->setText(in.readAll());
        file.close();
        std::cout<< qPrintable(closedapp_file_name) << std::endl;
    }

}

void MainWindow::imagestack_file_open(){

}
