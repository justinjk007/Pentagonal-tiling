#include <QApplication>
#include <QString>
#include "mainwindow.h"

using namespace std;
using namespace QtCharts;

// This macro disables the extra cmd window popup when in Microsoft windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Window settings
    w.setWindowTitle("Pentagonal Tiling - Visulization");
    w.setWindowIcon(QIcon("favicon.ico"));
    w.setStyleSheet("QMainWindow {background: rgb(147,161,161);}");  // Set background color

    // After all this time
    w.show();
    return a.exec();
}
