#include "mainwindow.h"
#include "ui_mainwindow.h"


//static const QSettings::Format StelIniFormat = QSettings::registerFormat("ini", readStelIniFile, writeStelIniFile);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

