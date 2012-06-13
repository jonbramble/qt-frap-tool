#include "frapmodel.h"

FrapModel::FrapModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    experiment = new FrapTool::Frap();
    rows = 0;
}

FrapModel::~FrapModel()
{
    delete experiment;
}

void FrapModel::setPrima(QString prima) {
    experiment->setprima(prima.toStdString());
}

void FrapModel::setClosed(QString closed) {
    experiment->setclosed(closed.toStdString());
}

void FrapModel::doSelection(){
    experiment->doselection();
   /* while(!experiment->selected()){
        wait();
    }*/

    experiment->processdata(); // move somewhere else
    experiment->print_data();

    double dif_const = experiment->dif_const();
    QString result = QString::number(dif_const,'g',3);
    emit update_result(result);

}

void FrapModel::setImageList(QStringList image_string_list){
    std::vector<std::string> ifiles;
    rows = image_string_list.size();
    ifiles.reserve(image_string_list.size()); // reserve vector space
    std::transform(image_string_list.begin(),image_string_list.end(),std::back_inserter(ifiles),&FrapModel::qStringToSTLString);
    experiment->setimagenames(ifiles);
}

int FrapModel::rowCount(const QModelIndex & /*parent*/) const
 {
    return rows;
 }

 int FrapModel::columnCount(const QModelIndex & /*parent*/) const
 {
     return 5;
 }

 QVariant FrapModel::headerData(int section, Qt::Orientation orientation, int role) const
 {

     if (role == Qt::FontRole)
     {
         QFont boldFont;
         boldFont.setBold(true);
         return boldFont;

     }
     if (role == Qt::DisplayRole)
     {
         QTextCodec *codec = QTextCodec::codecForName("UTF-8");
         if (orientation == Qt::Horizontal) {
             switch (section)
             {
             case 0:
                 return QString("Include");
             case 1:
                 return QString("Filename");
             case 2:
             {
                 QByteArray encodedString = "λ";
                 QString string = codec->toUnicode(encodedString);
                 return string;
             }
             case 3:
             {
                 QByteArray encodedString = "A";
                 QString string = codec->toUnicode(encodedString);
                 return string;
             }

             case 4:
             {
                 QByteArray encodedString = "μ";
                 QString string = codec->toUnicode(encodedString);
                 return string;
             }
             }
         }
     }
     return QVariant();
 }

 QVariant FrapModel::data(const QModelIndex &index, int role) const
 {
     if (role == Qt::DisplayRole)
     {
        return QString("Row%1, Column%2")
                    .arg(index.row() + 1)
                    .arg(index.column() +1);
     }
     return QVariant();
 }
