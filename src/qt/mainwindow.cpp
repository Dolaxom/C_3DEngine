#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

void MainWindow::on_leftb_pressed()
{

}

void MainWindow::on_upb_pressed()
{

}

void MainWindow::on_rightb_pressed()
{

}

void MainWindow::on_downb_pressed()
{

}

void MainWindow::on_autoc_clicked(bool checked)
{

}

void MainWindow::on_autoc_stateChanged(int arg1)
{

}

void MainWindow::on_meshd_activated(int index)
{

}

void MainWindow::on_meshd_currentIndexChanged(int index)
{

}

void MainWindow::on_meshd_currentTextChanged(const QString &arg1)
{

}

