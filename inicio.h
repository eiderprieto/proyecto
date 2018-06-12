#ifndef INICIO_H
#define INICIO_H


#include <QPoint>
#include <QMouseEvent>
#include <QWidget>
#include <QKeyEvent>

#include <QMovie>
#include <Qsize>


namespace Ui {
class inicio;
}

class inicio : public QWidget
{
    Q_OBJECT

public:
    explicit inicio(QWidget *parent = 0);
    ~inicio();

private:
    Ui::inicio *ui;
    QPoint mpos;
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void keyPressEvent(QKeyEvent *ev);
};

#endif // INICIO_H
