#ifndef PLPLOTWIDGET_H
#define PLPLOTWIDGET_H

#include <QWidget>
#include <QDebug>
#include "qt.h"

#define PLD_qtwidget

class PlPlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlPlotWidget(QWidget *parent = 0);
    ~PlPlotWidget();
    
signals:
    
public slots:
    void plotCurves();
    void plotLinearFit(int size, QVector<double> &xp,QVector<double> &yp,QVector<double> &yp_err, double m, double c);

protected:

    PLINT       strm;
    QtExtWidget * plot;
    
};

#endif // PLPLOTWIDGET_H
