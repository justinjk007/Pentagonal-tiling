#include <QApplication>
#include <QString>
#include "Config.h"  // Written by CMake
#include "mainwindow.h"

// This macro disables the extra cmd window popup when in Microsoft windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, char* argv[])
{
    // Emitted types are registered here to make queued connections possible
    qRegisterMetaType<std::vector<Line>>("std::vector<Line>");
    qRegisterMetaType<std::list<Line>>("std::list<Line>");

    QApplication a(argc, argv);
    MainWindow w;
    // Window settings
    w.setWindowTitle("Pentagonal Tiling - Visulization " + QString::number(VER_MAJOR) + "." +QString::number(VER_MINOR));
    w.setWindowIcon(QIcon("favicon.ico"));
    // After all this time
    w.show();
    return a.exec();
    // Always
}
