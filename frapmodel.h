#ifndef FRAPMODEL_H
#define FRAPMODEL_H

#include <QDebug>
#include <QAbstractTableModel>
#include <QBrush>
#include <QFontDatabase>
#include <QTextCodec>
#include <QStringList>
#include <fraptool/frap.h>
#include <fraptool/frapimage.h>

class FrapModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FrapModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    //bool insertRows(int row, int count, const QModelIndex &parent);

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    ~FrapModel();
    
signals:
    void update_result(QString diffusion);
    void plotLinearFit(int size, QVector<double> &xp,QVector<double> &yp,QVector<double> &yp_err, double m, double c);
    
public slots:
    void setPrima(QString prima);
    void setClosed(QString closed);
    void doSelection();
    void setImageList(QStringList image_string_list);
    void prepareLinearFit();

private:
    FrapTool::Frap *experiment;
    std::vector<FrapTool::result> results;
    std::vector<FrapTool::result>::iterator results_iterator;

    QVector<double> *time_s;
    QVector<double> *lambda_2;
    QVector<double> *lambda_err_2;

    int rows;
    static std::string qStringToSTLString(const QString& qstring){ return qstring.toStdString(); };

    
};

#endif // FRAPMODEL_H
