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
    // To start the game
    void on_startButton_clicked();

    // To quit and close the game window.
    void on_quitButton_clicked();

    // To pause the game until player take any action.
    void on_pauseButton_clicked();

    // To continue play game if game is paused.
    void on_resumeButton_clicked();

    // To reset and play game again from the beginning.
    void on_resetButton_clicked();

    // To play the game again when game is over.
    void on_restartButton_clicked();

    // To choose different level of the game.
    void on_easyRadioButton_toggled(bool checked);
    void on_mediumRadioButton_toggled(bool checked);
    void on_hardRadioButton_toggled(bool checked);

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

    // QGraphicsScence* for displaying the next random tetromino.
    QGraphicsScene* next_scene_;

    // For drawing the squares of tetrominos.
    QGraphicsRectItem* rect_;

    // Constant describing the scene for nex tetromino coordinates.
    const int RIGHT_NEXT = 120;
    const int DOWN_NEXT = 80;

    // Constant for number of square of one tetromino.
    const int SQUARE_NUM = 4;

    // For continuos moving.
    QTimer timer_;

    // Enum value different checking purposes.
    enum Direction {LEFT,
                    RIGHT,
                    UP,
                    DOWN,
                    OVERLAP};

    // Vector that contain all available squares of the game.
    std::vector<Square> all_square;

    // Current score gained.
    int score_;

    // Constant for score gained after a tetrino fall successfully
    // and for one full row removed.
    const int GAIN_SCORE = 10;

    // Bool showing the status of the game.
    bool is_running_;

    // The speed of falling tetromino depending on the chosen level.
    int interval_;
    const int EASY = 1000;
    const int MEDIUM = 600;
    const int HARD = 400;
    // Constant for increase the speed and also limit for the falling speed.
    const int ADVANCE = 50;
    // If score increses by ADVANCE_SCORE, the game advances
    const int ADVANCE_SCORE = 350;

    // When the speed increases, so does level
    int level_;

    /**
     * @brief tetromino_move
     * Move the current tetrominos continuously
     * until it is unable to move down.
     */
    void tetromino_move();

    /**
     * @brief check_movable
     * @param direct - the direction that needed checked
     * @param not_rotate - bool to show if the check is for rotation or not
     * @return true if the tetromino is movable in given direction
     *         otherwise false.
     */
    bool check_movable(int direct, bool not_rotate = true);

    /**
     * @brief random_tetromino
     * Contain initialization of different shapes of tetrominos.
     * Radom next tetromino.
     */
    void random_tetromino();

    /**
     * @brief update_gameboard
     * Display all squares after any movement or taken action.
     */
    void update_gameboard();

    /**
     * @brief rotate_current_tet
     * Rotate the falling tetromino
     * If the new coordinate of any squares in tetromino
     * is not suitable, the tetromino will not be rotated.
     */
    void rotate_current_tet();

    /**
     * @brief new_tetromino
     * If the game is still running, next tetromino displayed automatically.
     */
    void new_tetromino();

    /**
     * @brief delete_full_row
     * If any row is full it will be removed.
     * All needed squares change coordination by decreasing by SQUARE_SIDE.
     */
    void delete_full_row();

    /**
     * @brief advance_game
     * The falling speed increase when the game advances.
     */
    void advance_game();

    /**
     * @brief game_over
     * If game is over the player will be inform.
     * Player can restart the game without open new game.
     */
    void game_over();
};

#endif // MAINWINDOW_HH
