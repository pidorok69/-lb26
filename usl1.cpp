#include "usl1.h"
#include "ui_usl1.h"

Usl1::Usl1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Usl1)
{
    ui->setupUi(this);
}

Usl1::~Usl1()
{
    delete ui;
}
