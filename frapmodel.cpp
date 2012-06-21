#include "frapmodel.h"

FrapModel::FrapModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    experiment = new FrapTool::Frap();
}

FrapModel::~FrapModel()
{
    delete experiment;
}

void FrapModel::prepareLinearFit(){

     QVector<double> time_s;
     QVector<double> lambda_2;
     QVector<double> lambda_err_2;

     //could use transform?
     for(results_iterator=results.begin();results_iterator<results.end();results_iterator++)
     {
         time_s.push_back( results_iterator->time_s);
         lambda_2.push_back  (results_iterator->lambda_2);
         lambda_err_2.push_back (results_iterator->lambda_err_2);
     }

     double m = (experiment->dif_const())*2;
     double c = 0;

     //size must change if elements are excluded
     emit plotLinearFit(results.size(),time_s,lambda_2,lambda_err_2,m,c);
}

void FrapModel::setPrima(QString prima) {
    experiment->setprima(prima.toStdString());
}

void FrapModel::setClosed(QString closed) {
    experiment->setclosed(closed.toStdString());
}

void FrapModel::doSelection(){
    experiment->doselection();
    /*while(!experiment->selected()){
        wait();
    }*/
    experiment->processdata(); // move somewhere else
    experiment->print_data();

    experiment->get_results(results); // get results from frapmodel

    double dif_const = experiment->dif_const();
    QString result = QString::number(dif_const,'g',3);
    emit update_result(result);

    QModelIndex topLeft= createIndex(0,0);
    QModelIndex bottomRight= createIndex(4,4);
    emit dataChanged(topLeft,bottomRight);
} 

void FrapModel::setImageList(QStringList image_string_list){
    std::vector<std::string> ifiles;
    rows = image_string_list.size();
    ifiles.reserve(image_string_list.size()); // reserve vector space
    std::transform(image_string_list.begin(),image_string_list.end(),std::back_inserter(ifiles),&FrapModel::qStringToSTLString);
    experiment->setimagenames(ifiles);
    results.reserve(image_string_list.size());
}

/*bool FrapModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(row);
    Q_UNUSED(count);
    beginInsertRows(parent,0,0);
    endInsertRows();
    return true;
}*/

 int FrapModel::rowCount(const QModelIndex & /*parent*/) const
 {
    return 5;      // change this
 }

 int FrapModel::columnCount(const QModelIndex & /*parent*/) const
 {
     return 6;
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
                 return QString("Time (s)");
             case 3:
                 return QString("A");
             case 4:
             {
                 QByteArray encodedString = "λ";
                 QString string = codec->toUnicode(encodedString);
                 return string;
             }
             case 5:
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
     int row = index.row();
     int col = index.column();

     if (role == Qt::DisplayRole)
     {
         FrapTool::result result_row;
         result_row = results[row];

         // 0 include tick
         // 1 short Filename

         if(col == 2)
         {
             QString t = QString::number(result_row.time_s,'g',3);
             return t;
         }

         if(col == 3)
         {
             QString A = QString::number(result_row.A,'g',3);
             return A;
         }

         if(col == 4)
         {
             QString l = QString::number(result_row.lambda_2,'g',3);
             return l;
         }

         if(col == 5)
         {
             QString mu = QString::number(result_row.mu,'g',3);
             return mu;
         }

     }

     return QVariant();
 }
