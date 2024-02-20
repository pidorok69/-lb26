#ifndef USL1_H
#define USL1_H

#include <QWidget>

namespace Ui {
class Usl1;
}

class Usl1 : public QWidget
{
    Q_OBJECT

public:
    explicit Usl1(QWidget *parent = nullptr);
    ~Usl1();

private:
    Ui::Usl1 *ui;
};

#endif // USL1_H
