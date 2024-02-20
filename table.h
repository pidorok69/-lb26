#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QMenuBar>
#include <QtWidgets>
#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QIntValidator>
#include <QPalette>
#include <QStringList>
#include <QString>
#include <QTableWidgetItem>
#include <QMessageBox>
#include "usl1.h"
namespace Ui {
class Table;
}

class Table : public QWidget
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = nullptr);
    ~Table();


private:
    Ui::Table *ui;
    Usl1 usl;

public slots:
    void table_edit();
    void find_min_pair();
    void find_average();
    void find_group_average();
    bool isNumber(const QString& text);
    void save_file();
    bool f_check();


private slots:
    void on_usl_clicked();
};

#endif // TABLE_H
