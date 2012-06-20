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
    connect(ui->actionShow_Graph, SIGNAL(triggered()),this,SLOT(linear_fit_image_show()));

    set_background = false;
    set_closed = false;
    set_image_list = false;

    frapmodel = new FrapModel(0);

    //QList<QByteArray> list;
    //list = QImageReader::supportedImageFormats ();
    //qDebug() << list;

    connect(this,SIGNAL(primaset(QString)),frapmodel,SLOT(setPrima(QString)));
    connect(this,SIGNAL(closedset(QString)),frapmodel,SLOT(setClosed(QString)));
    connect(this,SIGNAL(doselection()),frapmodel,SLOT(doSelection()));
    connect(this,SIGNAL(imagelistset(QStringList)),frapmodel,SLOT(setImageList(QStringList)));

    connect(frapmodel,SIGNAL(dataChanged(QModelIndex,QModelIndex)), ui->tableView,SLOT(dataChanged(QModelIndex,QModelIndex)));
    connect(frapmodel,SIGNAL(update_result(QString)), this, SLOT(show_result(QString)));

    ui->tabWidget->setCurrentIndex(0);

    //ui->linearfitimage->

    starting_dir = "/home/jon/Programming/C/frap-tool-old";
}

MainWindow::~MainWindow()
{
    delete scene;
    delete item;
    delete frapmodel;
    delete ui;

}

void MainWindow::show_result(QString diffusion){
    ui->label_result->setText(diffusion);
}

void MainWindow::linear_fit_image_show(){
    QString fileName = QFileDialog::getOpenFileName(this,"Open Image File",QDir::currentPath());
        if(!fileName.isEmpty())
        {
            QImage image(fileName);
            if(image.isNull())
            {
                QMessageBox::information(this,"Image Viewer","Error Displaying image");
                return;
            }

            scene = new QGraphicsScene();
            item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
            scene->addItem(item);
            ui->linearfitimage->setScene(scene);
            ui->linearfitimage->show();
        }
}

void MainWindow::run_experiment()
{

    if(set_background && set_closed && set_image_list)
    {
        emit doselection();
        qDebug() << QString("called table show");
        ui->tableView->setModel( frapmodel );
        ui->tableView->show();
    }
    else {
        QMessageBox::warning(this,
                                 tr("qt-frap-tool"),
                                 tr("Image files not set.") );
    }

    //  experiment = new FrapTool::Frap(background_file_name.toStdString(),closedapp_file_name.toStdString(),false);
    //  experiment->doselection();
    //  experiment->setimagenames(ifiles);
    //  experiment->processdata();
    //  experiment->plplot_chart("prefix");
    //  experiment->print_data();
    //  experiment->save_data_file(prefix);
    //  double dif_const = experiment->dif_const();
    //  QString result = QString::number(dif_const,'g',3);
    //  ui->label_result->setText(result);
    //  delete experiment;
}



void MainWindow::background_file_open()
{                                       
    QFileDialog dialog;

    dialog.setDirectory( starting_dir );
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec()) {
        QStringList filenames = dialog.selectedFiles();
        background_file_name = filenames.at(0);
        set_background = true;
        starting_dir = QDir::currentPath();
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
        starting_dir = QDir::currentPath();
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
            starting_dir = QDir::currentPath();
            emit imagelistset(image_string_list);

        }
        else
        {
            set_image_list = false;
        }
}
