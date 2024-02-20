#include "usl2.h"
#include "ui_usl2.h"

Usl2::Usl2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Usl2)
{
    ui->setupUi(this);
}

Usl2::~Usl2()
{
    delete ui;
}
