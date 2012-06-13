#ifndef FRAPMODEL_H
#define FRAPMODEL_H

#include <QAbstractTableModel>
#include <QFontDatabase>
#include <QTextCodec>
#include <QStringList>
#include <fraptool/frap.h>

class FrapModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FrapModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    
signals:
    
public slots:
    void setPrima(QString prima);
    void setClosed(QString closed);
    void doSelection();
    void setImageList(QStringList image_string_list);

private:
    FrapTool::Frap *experiment;

    static std::string qStringToSTLString(const QString& qstring);
    
};

#endif // FRAPMODEL_H
