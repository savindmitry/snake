#include "mainwindow.h"
#include "field.h"

#include <QApplication>
#include <QPainter>
#include <QLabel>
#include <QRandomGenerator>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
