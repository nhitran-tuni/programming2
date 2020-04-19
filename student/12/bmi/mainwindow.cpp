#include "mainwindow.hh"
#include "ui_mainwindow.h"

const std::string UNDER = "You are underweight.",
                  OVER = "You are overweight.",
                  NORMAL = "Your weight is normal.";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->countButton, &QPushButton::clicked, this, &MainWindow::count);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::count()
{
//    std::string weight_str_ = ui->weightLineEdit->text().toStdString();
//    std::string height_str_ = ui->heightLineEdit->text().toStdString();

    double w_ = std::stod(ui->weightLineEdit->text().toStdString());
    double h_ = std::stod(ui->heightLineEdit->text().toStdString());

    double bmi_d_ = w_/((h_/100)*(h_/100));
    std::string bmi_str_ = std::to_string(bmi_d_);

    QString bmi_(bmi_str_.c_str());
    ui->resultLabel->setText(bmi_);

    if ( bmi_d_ < 18.5 ){
        QString under_(UNDER.c_str());
        ui->infoTextBrowser->setText(under_);
    }
    if ( bmi_d_ > 25 ){
        QString over_(OVER.c_str());
        ui->infoTextBrowser->setText(over_);
    }
    QString normal_(NORMAL.c_str());
    ui->infoTextBrowser->setText(normal_);

}
