#include "matrix.h"
#include "ui_matrix.h"

matrix::matrix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::matrix)
{
    ui->setupUi(this);
    QMenu *contextMenu = new QMenu(this);
    QAction *action1 = contextMenu->addAction("Найти максимальный элемент");
    QAction *action2 = contextMenu->addAction("Диагональная ли матрица");
    QAction *action3 = contextMenu->addAction("Найти сумму нечетных элементов каждой строки матрицы;.");

    connect(action1, &QAction::triggered, this, &matrix::findMaxElement);
    connect(action2, &QAction::triggered, this, &matrix::findProductOfOdd);
    connect(action3, &QAction::triggered, this, &matrix::checkRowSumEven);

    ui->matrix_table->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->matrix_table, &QWidget::customContextMenuRequested, this, [=](const QPoint &pos) {
        QPoint globalPos = ui->matrix_table->mapToGlobal(pos);
        contextMenu->exec(globalPos);
    });

    connect(ui->random, &QPushButton::clicked, this, &matrix::on_random_pressed);
    connect(ui->rows, &QSpinBox::valueChanged, this, &matrix::matrix_change);
    connect(ui->columns, &QSpinBox::valueChanged, this, &matrix::matrix_change);
    connect(ui->save, &QPushButton::clicked, this, &matrix::save_file);

}

matrix::~matrix()
{
    delete ui;
}

bool matrix::isNumber(const QString& text) {
    bool conversionOk;
    text.toDouble(&conversionOk);
    return conversionOk;
}

void matrix::on_random_pressed(){

    for(int i = 0; i < ui->matrix_table->rowCount(); i++){
        for(int j = 0; j < ui->matrix_table->columnCount(); j++){
            int randomNumber = QRandomGenerator::global()->bounded(0, 99);
            ui->matrix_table->setItem(i, j, new QTableWidgetItem(QString::number(randomNumber)));
        }
    }


}

void matrix::matrix_change(){
    QObject *senderObject = sender();

    if (senderObject == ui->rows)
    { ui->matrix_table->setRowCount(ui->rows->value());

    }

    if (senderObject == ui->columns)
    {
        ui->matrix_table->setColumnCount(ui->columns->value());

    }


}


void matrix::findMaxElement() //max element
{
    int maxItem = INT_MIN;
    for (int row = 0; row < ui->matrix_table->rowCount(); ++row) {

        for (int column = 0; column < ui->matrix_table->rowCount(); ++column) {
            QTableWidgetItem* item = ui->matrix_table->item(row, column);
            if (item != nullptr && !item->text().isEmpty() && isNumber(item->text()) && item->text().toInt() > maxItem) {
                maxItem = item->text().toInt();
            }
        }
    }

    QString result = QString::number(maxItem);
    ui->textBrowser->append(result);

}

void matrix::findProductOfOdd()
{
    bool flag = true;
    if(ui->matrix_table->rowCount()!=ui->matrix_table->columnCount()){
        flag = false;
    }
    for (int row = 0; row < ui->matrix_table->rowCount(); ++row) {
            if(!flag){
                break;
            }
        for (int column = 0; column < ui->matrix_table->columnCount(); ++column) {
            if(row == column){
                continue;
            }

            QTableWidgetItem* item = ui->matrix_table->item(row, column);
            if (item != nullptr && !item->text().isEmpty() && isNumber(item->text()) && item->text().toInt() != 0) {
                flag = false;
                break;
            }
        }


    }
    QString result;

    if(flag){
        result ="Да";
    }
    else{
        result = "Нет";
    }


    ui->textBrowser->append("Матрица диагональная? " + result);


}

void matrix::checkRowSumEven() // сумма нечетных
{
    for (int row = 0; row < ui->matrix_table->rowCount(); ++row) {
        int rowSum = 0;
        for (int column = 0; column < ui->matrix_table->columnCount(); ++column) {
            QTableWidgetItem* item = ui->matrix_table->item(row, column);
            if (item != nullptr && !item->text().isEmpty() && isNumber(item->text()) && item->text().toInt() % 2 != 0) {
                rowSum += item->text().toInt();
            }
        }

        ui->textBrowser->append("В строке " + QString::number(row + 1) + " сумма нечетных элементов: " + QString::number(rowSum));
    }
}

void matrix::save_file(){

    QString filename = "saved_inf.txt";
    QString text = ui->textBrowser->toPlainText();

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

void matrix::on_usl_clicked()
{
    usl.show();
}

