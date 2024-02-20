#ifndef USL2_H
#define USL2_H

#include <QWidget>

namespace Ui {
class Usl2;
}

class Usl2 : public QWidget
{
    Q_OBJECT

public:
    explicit Usl2(QWidget *parent = nullptr);
    ~Usl2();

private:
    Ui::Usl2 *ui;
};

#endif // USL2_H
