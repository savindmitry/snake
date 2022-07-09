#include "field.h"
#include "mainwindow.h"

#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QThread>
#include <QKeyEvent>
#include <random>

Field::Field(MainWindow* win, QColor col, int diff, QWidget *parent)
    : QWidget{parent}, c(col), d(diff), w(win)
{
    this->setWindowTitle("Змейка");
    setWindowIcon(QIcon("snake-logo"));
    this->setFixedSize(600, 600);
    snake = { {310, 290}, {310, 310} };
    dir = 0;
    score = 0;
    Generate();
    lose = false;
    pressed = false;
}

void Field::ex_code() {
    Move();
    if (lose) {
        delete this;
    }
    QTimer::singleShot(200 / d, this, SLOT(ex_code()));
}

void Field::Move() {
        QPoint next = snake[0];

        if(dir == 0) {
            next.ry() += 580;
        } else if (dir == 1) {
            next.rx() += 620;
        } else if (dir == 2) {
            next.ry() += 620;
        } else {
            next.rx() += 580;
        }
        next.ry() %= 600;
        next.rx() %= 600;

        if (std::count(snake.begin(), snake.end(), next) != 0) {
            w->show();
            w->ChangeScore(score);
            lose = true;
        } else if (next == apple) {
            snake.insert(snake.begin(), next);
            Generate();
            ++score;
        } else {
            snake.pop_back();
            snake.insert(snake.begin(), next);
        }
        pressed = false;
        update();
}

void Field::Generate() {
    std::mt19937 mersenne(std::time(nullptr));

    int a, b;

    do {
        a = 10 + (mersenne() % 30) * 20;
        b = 10 + (mersenne() % 30) * 20;
        apple = { a, b };
    } while (std::find(snake.begin(), snake.end(), apple) != snake.end());
}


void Field::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    QPen pen;
    pen.setColor(c);
    pen.setWidth(20);
    painter.setPen(pen);

    QPen app;
    app.setColor(Qt::red);
    app.setWidth(20);

    QPen grass;
    grass.setColor(QColor(119, 216, 56));
    grass.setWidth(20);

    painter.fillRect(0, 0, 600, 600, QColor(119, 216, 56));

    for (const auto& s : snake) {
        painter.drawPoint(s);
    }

    painter.setPen(app);
    painter.drawPoint(apple);
    painter.setPen(pen);
}

void Field::keyPressEvent(QKeyEvent *event) {
    if (!pressed) {
        int key = event->key();
        if (key == Qt::Key_Up && dir != 2) {
            dir = 0;
        } else if (key == Qt::Key_Right && dir != 3) {
            dir = 1;
        } else if (key == Qt::Key_Down && dir != 0) {
            dir = 2;
        } else if (key == Qt::Key_Left && dir != 1) {
            dir = 3;
        }
        pressed = true;
    }
}

