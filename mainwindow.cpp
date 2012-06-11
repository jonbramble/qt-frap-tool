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

    starting_dir = "/home/jon/Programming/C/frap-tool-old";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run_experiment()
{
    if(set_background && set_closed && set_image_list)
    {
        //const char *background_file_name_char = background_file_name.toLocal8Bit().constData();
        //const char *closedapp_file_name_char = closedapp_file_name.toLocal8Bit().constData();

        std::cout << background_file_name.toStdString() << std::endl;
        std::cout << closedapp_file_name.toStdString() << std::endl;

        experiment = new FrapTool::Frap(background_file_name.toStdString(),closedapp_file_name.toStdString(),false);

        experiment->doselection();

        experiment->setimagenames(ifiles);
        experiment->processdata();

        //experiment->plplot_chart("prefix");
        experiment->print_data();
        //experiment->save_data_file(prefix);

        double dif_const = experiment->dif_const();
        QString result = QString::number(dif_const,'g',3);

        ui->label_result->setText(result);

        delete experiment;
    }
    else {
        QMessageBox::warning(this,
                                 tr("qt-frap-tool"),
                                 tr("Image files not set.") );
    }


}

std::string MainWindow::qStringToSTLString(const QString& qstring)
{
   std::string tmpstring = qstring.toStdString();
   return tmpstring;
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

            ifiles.reserve(image_string_list.size()); // reserve vector space
            std::transform(image_string_list.begin(),image_string_list.end(),std::back_inserter(ifiles),&qStringToSTLString);
        }
        else
        {
            set_image_list = false;
        }
}
