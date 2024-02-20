#ifndef MATRIX_H
#define MATRIX_H

#include <QWidget>
#include <QRandomGenerator>
#include <QObject>
#include <QTableWidgetItem>
#include <QMenu>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <filesystem>
#include "usl2.h"

namespace Ui {
class matrix;
}

class matrix : public QWidget
{

    Q_OBJECT

public:
    explicit matrix(QWidget *parent = nullptr);
    ~matrix();

private:
    Ui::matrix *ui;
    Usl2 usl;

private slots:
    void on_random_pressed();
    void matrix_change();
    void findMaxElement();
    void findProductOfOdd();
    void checkRowSumEven();
    bool isNumber(const QString& text);
    void save_file();

    void on_usl_clicked();
};

#endif // MATRIX_H
