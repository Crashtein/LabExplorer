/**
* \mainpage
* \par Program LabExplorer v1.3
* \author Paweˆ Kluk
* \date 2017.06.1
* \version 1.3
* \par Kontakt:
* \a kluk.pl@gmail.com
*/

/**
 * \file main.cpp
 * \brief Plik z funkcj¥ main(int argc, char* argv[])
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
