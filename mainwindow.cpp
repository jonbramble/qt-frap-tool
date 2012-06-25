#include "ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionBackground, SIGNAL(triggered()), this, SLOT(background_file_open()));
    connect(ui->actionClosed_Aperature, SIGNAL(triggered()), this, SLOT(closedapp_file_open()));
    connect(ui->actionImage_Stack, SIGNAL(triggered()), this, SLOT(imagelist_file_open()));
    connect(ui->actionRun_Experiment, SIGNAL(triggered()), this, SLOT(run_experiment()));

    set_background = false;
    set_closed = false;
    set_image_list = false;

    ui->actionClosed_Aperature->setDisabled(true);
    ui->actionImage_Stack->setDisabled(true);
    ui->actionRun_Experiment->setDisabled(true);
    ui->actionShow_Graph->setDisabled(true);

    frapmodel = new FrapModel(0);

    connect(this,SIGNAL(primaset(QString)),frapmodel,SLOT(setPrima(QString)));
    connect(this,SIGNAL(closedset(QString)),frapmodel,SLOT(setClosed(QString)));
    connect(this,SIGNAL(doselection()),frapmodel,SLOT(doSelection()));
    connect(this,SIGNAL(imagelistset(QStringList)),frapmodel,SLOT(setImageList(QStringList)));

    connect(ui->actionShow_Graph, SIGNAL(triggered()),frapmodel, SLOT(prepareLinearFit()));

    //connect(frapmodel,SIGNAL(dataChanged(QModelIndex,QModelIndex)), ui->tableView,SLOT(dataChanged(QModelIndex,QModelIndex)));
    connect(frapmodel,SIGNAL(update_result(QString)), this, SLOT(show_result(QString)));
    connect(frapmodel,SIGNAL(plotLinearFit(int,std::vector<double>&,std::vector<double>&,std::vector<double>&,double,double)), ui->pl_widget, SLOT(plotLinearFit(int,std::vector<double>&,std::vector<double>&,std::vector<double>&,double,double)));

    ui->tabWidget->setCurrentIndex(0);
    starting_dir = "/home/jon/Programming/C/frap-tool-old";
}

MainWindow::~MainWindow()
{
    delete frapmodel;
    delete ui;
}

void MainWindow::show_result(QString diffusion){
    ui->label_result->setText(diffusion);
}

void MainWindow::linear_fit_image_show(){
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::run_experiment()
{
    emit doselection();
    ui->tableView->setModel( frapmodel );
    ui->tableView->show();
}

void MainWindow::background_file_open()
{                                       
    QFileDialog dialog;

    //dialog.setDirectory( starting_dir );
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec()) {
        QStringList filenames = dialog.selectedFiles();
        background_file_name = filenames.at(0);
        set_background = true;
        starting_dir = dialog.directory();
        ui->actionClosed_Aperature->setDisabled(false);
        emit primaset(background_file_name);
    }
    else
    {
        set_background = false;
    }
}

void  MainWindow::closedapp_file_open(){                         
    QFileDialog dialog;

    dialog.setDirectory( starting_dir );
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec()) {
        QStringList filenames = dialog.selectedFiles();
        closedapp_file_name = filenames.at(0);
        set_closed = true;
        ui->actionImage_Stack->setDisabled(false);
        emit closedset(closedapp_file_name);

    }
    else
    {
        set_closed = false;
    }
}

void MainWindow::imagelist_file_open(){
    QFileDialog dialog;

    dialog.setDirectory( starting_dir );
    dialog.setFileMode(QFileDialog::ExistingFiles);
        if (dialog.exec()) {
            image_string_list = dialog.selectedFiles();
            set_image_list = true;
            ui->actionRun_Experiment->setDisabled(false);
            ui->actionShow_Graph->setDisabled(false);
            emit imagelistset(image_string_list);
        }
        else
        {
            set_image_list = false;
        }
}
