#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer(this);
    ui->setupUi(this);

    second_ = 0;
    minute_ = 0;

    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::reset);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::start);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stop);
    connect(timer, &QTimer::timeout, this, &MainWindow::finish_1000ms);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::close()
{
    this->close();
}

void MainWindow::reset()
{
    timer->stop();
    second_ = 0;
    minute_ = 0;
    ui->lcdNumberSec->display(second_);
    ui->lcdNumberMin->display(minute_);
}

void MainWindow::start()
{
    timer->start(interval_);
}

void MainWindow::stop()
{
    interval_ = timer->remainingTime();
    timer->stop();
}

void MainWindow::finish_1000ms()
{
    timer->start(1000);
    second_ ++;

    if ( second_ == 60 ){
        second_ = 0;
        minute_ ++;
    }

    ui->lcdNumberSec->display(second_);
    ui->lcdNumberMin->display(minute_);
}

