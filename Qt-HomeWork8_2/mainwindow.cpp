#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    sysvw = new SystemViewWidget(this);
}

MainWindow::~MainWindow()
{
    delete sysvw;
}

