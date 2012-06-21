#include "plplotwidget.h"

PlPlotWidget::PlPlotWidget(QWidget *parent) :
    QWidget(parent)
{
    setAttribute( Qt::WA_DeleteOnClose );

    //QMenu * plotMenu = menuBar()->addMenu( "Plot" );
    //plotMenu->addAction( "Curves", this, SLOT( plotCurves() ) );
    //plotMenu->addAction( "Histogram", this, SLOT( plotHistogram() ) );
    //plotMenu->addAction( "Interactive Selection", this, SLOT( interactive() ) );

    plot = new QtExtWidget( 400, 320, parent );

    // One window = One plot widget = one stream
    plmkstrm( &strm );
    plsdev( "extqt" );

    plsetqtdev( plot );

    plinit();

    resize( 400, 320 );

    pladv( 0 );

    unsigned int col = 255;
    plscolbg(col,col,col);
}

PlPlotWidget::~PlPlotWidget(){
    PLINT cur_strm;
    plgstrm( &cur_strm );
    plsstrm( strm );
    plfreeqtdev(); // also deletes the device ("plot" variable) !
    plsstrm( cur_strm );
}

void PlPlotWidget::plotLinearFit(int size, QVector<double> &xp,QVector<double> &yp,QVector<double> &yp_err, double m, double c){

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

    result_min_x = std::min_element(xp.toStdVector().begin(), xp.toStdVector().end());
    result_max_x = std::max_element(xp.toStdVector().begin(), xp.toStdVector().end());
    result_min_y = std::min_element(yp.toStdVector().begin(), yp.toStdVector().end());
    result_max_y = std::max_element(yp.toStdVector().begin(), yp.toStdVector().end());

    max_x = (*result_max_x)*(1.2);	//sets the axis to be 20% larger than the max value
    max_y = (*result_max_y)*(1.2);

    plcol0( 1 );
    plenv( 0, max_x, 0, max_y, 0, 1 );
    plcol0( 2 );
    pllab( "time (s)", "lambda", "FRAP DATA" );

    plcol0( 3 );
    plwid( 2 );
    plpoin( size, x, y, 20);
    plerry( size, x, y_err_hi,y_err_lo);
    plwid( 1 );

    plcol0( 3 );
    plwid( 2 );
    plline( size, x, y_fit );
    plwid( 1 );

    delete[] x;
    delete[] y;
    delete[] y_fit;
    delete[] y_err_hi;
    delete[] y_err_lo;
}

void PlPlotWidget::plotCurves()
{
    plot->clearWidget();

    PLFLT sine[360];
    PLFLT cosine[360];
    PLFLT indexes[360];
    PLFLT square[360];
    PLFLT cubic[360];

    // 1st plot

    for ( int i = 0; i < 360; ++i )
    {
        sine[i]    = sin( (PLFLT) i / 180. * M_PI );
        cosine[i]  = cos( (PLFLT) i / 180. * M_PI );
        indexes[i] = (PLFLT) i;
    }

    pladv( 0 );
    plvpor( 0.05, 0.95, 0.05, 0.45 );
    plwind( 0., 360., -1.2, 1.2 );

    plcol0( 2 );
    plbox( "bcnst", 0., 0, "bcnst", 0., 0 );

    plcol0( 1 );
    plwid( 2 );
    plline( 360, indexes, sine );

    plcol0( 3 );
    plwid( 1 );
    pllsty( 2 );
    plline( 360, indexes, cosine );
    pllsty( 1 );

    plcol0( 2 );

    plmtex( "t", 1., 0.5, 0.5, "Sines" );

    // 2nd plot

    for ( int i = -180; i < 180; ++i )
    {
        square[i + 180]  = ( ( (PLFLT) i ) / 180. * ( (PLFLT) i ) / 180. );
        cubic[i + 180]   = square[i + 180] * ( (PLFLT) i ) / 180.;
        indexes[i + 180] = ( (PLFLT) i ) / 180.;
    }

    plvpor( 0.05, 0.95, 0.55, 0.95 );
    plwind( -1., 1., -1., 1. );

    plcol0( 2 );
    plbox( "bcnst", 0., 0, "bcnst", 0., 0 );

    plcol0( 1 );
    plwid( 2 );
    plline( 360, indexes, square );

    plcol0( 3 );
    plwid( 1 );
    pllsty( 2 );
    plline( 360, indexes, cubic );
    pllsty( 1 );

    plcol0( 2 );

    plmtex( "t", 1., 0.5, 0.5, "Square & Cubic" );
}
