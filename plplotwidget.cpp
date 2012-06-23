#include "plplotwidget.h"

PlPlotWidget::PlPlotWidget(QWidget *parent) :
    QWidget(parent)
{
    setAttribute( Qt::WA_DeleteOnClose );

    plot = new QtExtWidget( parent->width(), parent->height(), parent ); //this should fit the widget box

    plmkstrm( &strm );// One window = One plot widget = one stream
    plsdev( "extqt" );
    plsetqtdev( plot );
    plinit();

    plot->setBackgroundColor(255,255,255,1);

    //resize( 400, 320 );
    pladv( 0 );
    //unsigned int col = 255;
    //plscolbg(col,col,col);
}

PlPlotWidget::~PlPlotWidget(){
    qDebug() << "plplot destructor called";
    PLINT cur_strm;
    plgstrm( &cur_strm );
    plsstrm( strm );
    plfreeqtdev(); // also deletes the device ("plot" variable) !
    plsstrm( cur_strm );

}

void PlPlotWidget::plotLinearFit(int size, std::vector<double> &xp,std::vector<double> &yp,std::vector<double> &yp_err, double m, double c){

    plot->clearWidget();

    int   i;
    double max_x, max_y;

    std::vector<double>::iterator result_min_x, result_max_x;
    std::vector<double>::iterator result_min_y, result_max_y;

    PLFLT *x = new PLFLT[size];
    PLFLT *y = new PLFLT[size];
    PLFLT *y_fit = new PLFLT[size];
    PLFLT *y_err_hi = new PLFLT[size];
    PLFLT *y_err_lo = new PLFLT[size];

    for(i=0;i<size;i++){  // is there a better way with first value
        x[i]=xp[i];
        y[i]=yp[i];
        y_fit[i]=m*xp[i]+c;
        y_err_hi[i]=yp[i]+yp_err[i];
        y_err_lo[i]=yp[i]-yp_err[i];
    }

    result_min_x = std::min_element(xp.begin(), xp.end());
    result_max_x = std::max_element(xp.begin(), xp.end());
    result_min_y = std::min_element(yp.begin(), yp.end());
    result_max_y = std::max_element(yp.begin(), yp.end());

    max_x = (*result_max_x)*(1.2);	//sets the axis to be 20% larger than the max value
    max_y = (*result_max_y)*(1.2);

    plcol0( 14 );
    plenv( 0, max_x, 0, max_y, 0, 1 );
    plcol0( 1 );
    pllab( "time (s)", "\gl", "FRAP DATA" );

    plcol0( 14 );
    plwid( 2 );
    plpoin( size, x, y, 20);
    plerry( size, x, y_err_hi,y_err_lo);
    plwid( 1 );

    plcol0( 14 );
    plwid( 2 );
    plline( size, x, y_fit );
    plwid( 1 );

    delete[] x;
    delete[] y;
    delete[] y_fit;
    delete[] y_err_hi;
    delete[] y_err_lo;
}

void PlPlotWidget::plotGaussianFit(int size, std::vector<double> &xp,std::vector<double> &yp,std::vector<double> &yp_fit){

}
