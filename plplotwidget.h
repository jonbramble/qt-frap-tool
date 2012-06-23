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
    //void plotCurves();
    void plotLinearFit(int size, std::vector<double> &xp,std::vector<double> &yp,std::vector<double> &yp_err, double m, double c);
    void plotGaussianFit(int size, std::vector<double> &xp,std::vector<double> &yp,std::vector<double> &yp_fit);

protected:

    PLINT       strm;
    QtExtWidget * plot;
    
};

#endif // PLPLOTWIDGET_H
