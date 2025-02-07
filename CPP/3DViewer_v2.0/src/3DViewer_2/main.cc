#include "view/view.h"

#include <QApplication>
#include <QProcess>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLocale::setDefault(
        QLocale::C);  // so on windows and linux will work evenly: 10,1 in russian
                      // reads as 10.1, but in latin 10
    setbuf(stderr, NULL);  // to print error immediately
    setbuf(stdout, NULL);  // same for printf

            // for QSettings class working
    QCoreApplication::setOrganizationName("School21");
    QCoreApplication::setOrganizationDomain("mysoft.com");
    QCoreApplication::setApplicationName("3DViewer_V2");
    s21::View w;
    w.show();
    return a.exec();
}
