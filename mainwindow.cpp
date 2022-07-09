#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "field.h"
#include <QThread>
#include <QTimer>
#include <QString>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(600, 600);
    setWindowTitle("Змейка");
    setWindowIcon(QIcon("snake-logo"));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ChangeScore(int s) {
    ui->label_4->setText(QString::number(std::max(s, (ui->label_4->text()).toInt())));
    ui->label_6->setText(QString::number(s));
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    QColor c;
    if (ui->radioButton_3->isChecked()) {
        c = Qt::black;
    } else if (ui->radioButton_2->isChecked()) {
        c = QColor(148, 63, 227);
    } else {
        c = QColor(235, 211, 8);
    }
    int d;
    if (ui->radioButton_4->isChecked()) {
        d = 3;
    } else if (ui->radioButton_5->isChecked()) {
        d = 2;
    } else {
        d = 1;
    }
    Field* f = new Field(this, c, d);
    f->show();

    QTimer::singleShot(200 / d, f, SLOT(ex_code()));

}

