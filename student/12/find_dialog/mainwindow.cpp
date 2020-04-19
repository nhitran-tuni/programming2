#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "checkfile.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sign(false)
{
    ui->setupUi(this);

    connect(ui->matchCheckBox, &QCheckBox::stateChanged, this, &MainWindow::matchbox);
    connect(ui->findPushButton, &QPushButton::clicked, this, &MainWindow::find);
    connect(ui->closePushButton, &QPushButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::matchbox()
{
    sign = ui->matchCheckBox->isChecked();
}

void MainWindow::find()
{
    std::string result = findword(ui->fileLineEdit->text().toStdString(),
                                  ui->keyLineEdit->text().toStdString(),
                                  ui->matchCheckBox->checkState());
    ui->textBrowser->reload();

    if ( result == F_N_FOUND ){
        QString f_n_found(F_N_FOUND.c_str());
        ui->textBrowser->setText(f_n_found);
        return;
    }

    if ( ui->keyLineEdit->text().toStdString() == EMPTY ){
        QString f_found(F_FOUND.c_str());
        ui->textBrowser->setText(f_found);
        return;
    }

    if ( result == W_FOUND ){
        QString w_found(W_FOUND.c_str());
        ui->textBrowser->setText(w_found);
        return;
    }

    QString w_n_found(W_N_FOUND.c_str());
    ui->textBrowser->setText(w_n_found);
    return;
}

void MainWindow::close()
{
    this->close();
}
