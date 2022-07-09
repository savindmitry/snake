#ifndef FIELD_H
#define FIELD_H

#include "mainwindow.h"
#include <QTimer>
#include <QWidget>
#include <QLineEdit>

class Field : public QWidget
{
    Q_OBJECT
public:
    explicit Field(MainWindow* win, QColor col, int diff, QWidget *parent = nullptr);
    void Move();

    bool lose;
    bool pressed;
protected:
    void paintEvent(QPaintEvent*);

    void keyPressEvent(QKeyEvent *event);

private:
    QColor c; // color
    int d; // difficulty
    QVector<QPoint> snake;
    int dir; // direction
    int score;
    MainWindow* w;
    QPoint apple;

    void Generate();

private slots:
    void ex_code();
};

#endif // FIELD_H
