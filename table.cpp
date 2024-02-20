#include "table.h"
#include "ui_table.h"

Table::Table(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Table)
{
    ui->setupUi(this);
    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *averageMark = new QMenu("Одинаковые ли? ", menuBar);



    QAction *group_mark = new QAction("Одинаковое ли число отсутсвующих", this);
    averageMark->addAction(group_mark);
    menuBar->addMenu(averageMark);

    QMenu *unsatisfied = new QMenu("Отсутсвующих и присутсвующих", menuBar);

    QAction *find = new QAction("Определить на какой паре было наибольшее число отсутствующих.", this);
    unsatisfied->addAction(find);

    QAction *family_check = new QAction("Вычислить число присутствующих для каждой группы, при условии, что в каждой группе учится 25 человек.", this);
    unsatisfied->addAction(family_check);

    menuBar->addMenu(unsatisfied);

    ui->tableWidget->hide();
    ui->textBrowser->hide();
    ui->lineEdit->setPlaceholderText("Количество пар");
    QIntValidator *validator = new QIntValidator();
    ui->lineEdit->setValidator(validator);

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &Table::table_edit);
    connect(find, &QAction::triggered, this, &Table::find_min_pair);

    connect(group_mark, &QAction::triggered, this, &Table::find_group_average);
    connect(family_check, &QAction::triggered, this, &Table::f_check);
    connect(ui->save, &QPushButton::clicked, this, &Table::save_file);
}

Table::~Table()
{
    delete ui;

}

bool Table::isNumber(const QString& text) {
    bool conversionOk;
    text.toDouble(&conversionOk);
    return conversionOk;
}

void Table::table_edit(){

    ui->tableWidget->show();
    ui->tableWidget->setRowCount(ui->lineEdit->text().toInt()+1);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels((QStringList() << "Номер пары" << "Количество отсутсвующих " ));
}

void Table::find_min_pair() {
    ui->textBrowser->clear();
    ui->textBrowser->show();
    ui->textBrowser->append("максимально отсутсвующих:");

    const int rows = ui->tableWidget->rowCount();
    const int cols = ui->tableWidget->columnCount();

    QTableWidgetItem* max_pair = nullptr;
    QTableWidgetItem* max_s = nullptr;

    for (int row = 0; row < rows; row++) {
        QTableWidgetItem* item = ui->tableWidget->item(row, 1);
        if (item) {
            int current_value = item->text().toInt();
            if (max_s == nullptr || current_value > max_s->text().toInt()) {
                max_s = item;
                max_pair = ui->tableWidget->item(row, 0);
            }
        }
    }

    if (max_pair != nullptr && max_s != nullptr) {
        ui->textBrowser->append("Пара с самым большим числом отсутствующих: " + max_pair->text() + " с максимальным количеством в " + max_s->text());
    } else {
        ui->textBrowser->append("Нет таких");
    }
}



void Table::find_average() {
    for (int row = 0; row < ui->tableWidget->rowCount()-1; ++row) {
        double average = 0;
        int marksCount = 0;
        for (int column = 1; column <= 2; ++column) {
            QTableWidgetItem* item = ui->tableWidget->item(row, column);
            if (item != nullptr && !item->text().isEmpty() && isNumber(item->text())) {
                average += item->text().toDouble();
                marksCount++;
            }
        }
        double averageScore = (marksCount > 0) ? average / marksCount : 0.0;
        QTableWidgetItem* averageItem = new QTableWidgetItem(QString::number(averageScore, 'f', 2));
        ui->tableWidget->setItem(row, 3, averageItem);
    }

}





void Table::find_group_average(){ // все ли одинаковые
    bool flag = true;
    QString result = "да";
     QTableWidgetItem* check_item = ui->tableWidget->item(0, 1);
    for (int row = 1; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem* item = ui->tableWidget->item(row, 1);

        if (item && check_item->text() == item->text()) {
            if(item->text().length() < 8){
                flag = false;
                break;
            }

        }

    }

    if(!flag) {
        result = "да";
    }else{
        result = "нет";
    }



    QMessageBox::information(this, "", "Одинаковое ли число отсутсвующих:: " + result);

}


void Table::on_usl_clicked()
{
    usl.show();
}

void Table::save_file(){
    QString text; // = item->text();

    QString filename = "saved_inf_table.txt";

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            QTableWidgetItem* item = ui->tableWidget->item(row, column);
            if (item != nullptr && !item->text().isEmpty()) {
                text.append(item->text());
                text.append("   ");
            }
        }
        text.append(QString::fromUtf8("\n"));
    }

    QFile file(filename); // Создаем объект файла

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << text;
        file.close();
        qDebug() << "Файл успешно сохранен.";
    } else {
        qDebug() << "Не удалось открыть файл.";
    }


}

bool Table::f_check(){ // сумма учащихся
    ui->textBrowser->clear();
    ui->textBrowser->show();
    ui->textBrowser->append(":");

    const int rows = ui->tableWidget->rowCount();
    const int cols = ui->tableWidget->columnCount();
    int sum = 0;

    QTableWidgetItem* max_pair = nullptr;
    QTableWidgetItem* max_s = nullptr;

    for (int row = 0; row < rows; row++) {

        QTableWidgetItem* item = ui->tableWidget->item(row, 1);
        if (item) {
            sum += 25 - item->text().toInt();
            }
        }
    QString result = QString::number(sum);


    QMessageBox::information(this, "", "Одинаковое ли число отсутсвующих: " + result);

}

