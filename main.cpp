#include "ScaleWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);

    auto ptBeg = b_ptime(boost::gregorian::date(2000, 1, 1));
    auto ptEnd = ptBeg + boost::posix_time::hours(24 * 10);

    TimeRange Range{ptBeg, ptEnd};

    ScaleWidget Widget(Range);
    Widget.show();
    return App.exec();
}
