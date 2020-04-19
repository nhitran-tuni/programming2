#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Normally this member should be in private part of the
    // class, but due to the automated tests it must be more
    // accessible.
    QTimer* timer;

private slots:
    // Add your slots here
    void close();
    void reset();
    void start();
    void stop();
    void finish_1000ms();

private:
    Ui::MainWindow *ui;
    // Add other necessary members here
    int second_;
    int minute_;
    int interval_ = 1000;
};

#endif // MAINWINDOW_HH
