#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::table_edit);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::matrix_edit);



}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::table_edit(){
    table_w.show();

}

void MainWindow::matrix_edit(){
    matrix_w.show();
}
