/* Program author
* Name: Thuy Phuong Nhi Tran
* Student number: 291937
* UserID: mpthtr
* E-Mail: thuyphuongnhi.tran@tuni.fi
*
* */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <vector>
#include <random>
#include <QTimer>
#include <algorithm>
#include <QKeyEvent>

struct Square
{
    QGraphicsRectItem* rect;
    int x_;
    int y_;
    QBrush color;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event) override;

private slots:

    void on_startButton_clicked();

    void on_quitButton_clicked();

    void on_pauseButton_clicked();

    void on_resumeButton_clicked();

    void on_resetButton_clicked();

    void on_restartButton_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene_;

    // Constants describing scene coordinates
    // Copied from moving circle example and modified a bit
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)

    // Size of a tetromino component
    const int SQUARE_SIDE = 20;
    // Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    // Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;

    // Constants for different tetrominos and the number of them
    enum Tetromino_kind {HORIZONTAL,
                         LEFT_CORNER,
                         RIGHT_CORNER,
                         SQUARE,
                         STEP_UP_RIGHT,
                         PYRAMID,
                         STEP_UP_LEFT,
                         NUMBER_OF_TETROMINOS};
    // From the enum values above, only the last one is needed in this template.
    // Recall from enum type that the value of the first enumerated value is 0,
    // the second is 1, and so on.
    // Therefore the value of the last one is 7 at the moment.
    // Remove those tetromino kinds above that you do not implement,
    // whereupon the value of NUMBER_OF_TETROMINOS changes, too.
    // You can also remove all the other values, if you do not need them,
    // but most probably you need a constant value for NUMBER_OF_TETROMINOS.


    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    // More constants, attibutes, and methods
    QGraphicsScene* next_scene_;

    const int RIGHT_NEXT = 120;
    const int DOWN_NEXT = 80;
    const int COLUMN_NEXT = RIGHT_NEXT / SQUARE_SIDE;
    const int ROW_NEXT = DOWN_NEXT / SQUARE_SIDE;

    QTimer timer_;

    QGraphicsRectItem* rect_;

    void tetromino_move();
    bool check_movable(int direct, bool not_rotate = true);
    enum Direction {LEFT,
                    RIGHT,
                    UP,
                    DOWN,
                    OVERLAP};

    std::vector<Square> all_square;
//    std::vector<Square> next_square;
//    int random_tet_;
    void random_tetromino();

    void draw();

    void rotate_current_tet();

    void new_tetromino();

    void delete_full_row();

    void game_over();

    int score_;
    const int GAIN_SCORE = 10;

    bool is_running_;
/*
//    const int type_I[4][4] = {
//                            0,1,0,0,
//                            0,1,0,0,
//                            0,1,0,0,
//                            0,1,0,0

//    };
//    const int type_L1[4][4] = {
//                            1,0,0,0,
//                            1,1,1,0,
//                            0,0,0,0,
//                            0,0,0,0

//    };
//    const int type_L2[4][4] = {
//                            0,0,1,0,
//                            1,1,1,0,
//                            0,0,0,0,
//                            0,0,0,0

//    };
//    const int type_O[4][4] = {
//                            1,1,0,0,
//                            1,1,0,0,
//                            0,0,0,0,
//                            0,0,0,0

//    };
//    const int type_S1[4][4] = {
//                            0,1,1,0,
//                            1,1,0,0,
//                            0,0,0,0,
//                            0,0,0,0

//    };
//    const int type_S2[4][4] = {
//                            1,1,0,0,
//                            0,1,1,0,
//                            0,0,0,0,
//                            0,0,0,0

//    };
//    const int type_T[4][4] = {
//                            1,1,1,0,
//                            0,1,0,0,
//                            0,0,0,0,
//                            0,0,0,0

//    };
*/
};

#endif // MAINWINDOW_HH
