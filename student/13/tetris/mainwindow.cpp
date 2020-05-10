/*
* Add implements define functions
*
* Program author
* Name: Thuy Phuong Nhi Tran
* Student number: 291937
* UserID: mpthtr
* E-Mail: thuyphuongnhi.tran@tuni.fi
*
* */
#include "mainwindow.hh"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // We need a graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);
    next_scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates, but if you want
    // different placement, you can change their values.
    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Setting random engine ready for the first real call.
    int seed = time(0); // You can change seed value for testing purposes
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng); // Wiping out the first random number (which is almost always 0)
    // After the above settings, you can use randomEng to draw the next falling
    // tetromino by calling: distr(randomEng) in a suitable method.

    // Add more initial settings and connect calls, when needed.

    // The graphicsView displays next random tetromino
    //is placed on window at following coordinates.
    int left_next = 380;
    int top_next = 150;

    // Initialize the GraphicsView displaying next random tetromino
    // the same way as initializing the GraphicsView for playing game.
    ui->nextTetGraphicsView->setGeometry(left_next, top_next,
                                         RIGHT_NEXT + 2, DOWN_NEXT + 2);
    ui->nextTetGraphicsView->setScene(next_scene_);
    next_scene_->setSceneRect(0, 0, RIGHT_NEXT - 1, DOWN_NEXT - 1);

    // Before game start, all press buttons are disable,
    // button buttons to choose game level are exception.
    ui->startButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);
    ui->resumeButton->setDisabled(true);
    ui->restartButton->setDisabled(true);
    ui->resetButton->setDisabled(true);

    ui->gameStatusTextBrowser->setText("-TETRIS GAME-");

    is_running_ = true;

    // The initial score is 0.
    score_ = 0;

    // Timer fires every particular interval
    //depending on the hard level of the game
    timer_.setSingleShot(false);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::tetromino_move);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    // If game is over, the signals from the keyboard are disable.
    if ( !is_running_ ) return;

    switch (event->key()) {
    // Move tetromino to the right by SQUARE_SIDE.
    case Qt::Key_A:
        if ( check_movable(LEFT) ){
            for ( unsigned int i = all_square.size() - 2 * SQUARE_NUM;
                  i < all_square.size() - SQUARE_NUM; i++ ){
                all_square.at(i).x_ -= 1;
            }
        }
        break;
    // Move tetromino to the left by SQUARE_SIDE.
    case Qt::Key_D:
        if ( check_movable(RIGHT) ){
            for ( unsigned int i = all_square.size() - 2 * SQUARE_NUM;
                  i < all_square.size() - SQUARE_NUM; i++ ){
                all_square.at(i).x_ += 1;
            }
        }
        break;
    // Move tetromino to the down by SQUARE_SIDE.
    case Qt::Key_S:
        if ( check_movable(DOWN) ){
            for ( unsigned int i = all_square.size() - 2 * SQUARE_NUM;
                  i < all_square.size() - SQUARE_NUM; i++ ){
                all_square.at(i).y_ += 1;
            }
        }
        break;
    // Rotate the current tetromino clockwise by 90 degree.
    case Qt::Key_W:
        rotate_current_tet();
        break;
    default:
        break;
    }
    update_gameboard();
}

void MainWindow::tetromino_move()
{
    // The current tetromino falls down and stops when it
    // reaches BORDER_DOWN or on the other tetrominos.
    if ( check_movable(DOWN) ){
        for ( unsigned int i = all_square.size() - 2 * SQUARE_NUM;
              i < all_square.size() - SQUARE_NUM; i++ ){
            all_square.at(i).y_ += 1;
        }
        update_gameboard();
    } else {
        timer_.stop();

        // If there is/are full rows, these rows will be deleted.
        delete_full_row();

        // Display the current score
        ui->scorelcdNumber->display(score_);

        // Advance the game if needed
        advance_game();

        // When previous tetromino stops, next tetronimo appears
        // if the game is not over.
        new_tetromino();
    }
}

void MainWindow::update_gameboard()
{
    QPen blackPen(Qt::black);
    blackPen.setWidth(1.5);

    // Update the playing area.
    scene_->clear();
    for ( unsigned int i = 0;
          i < all_square.size() - SQUARE_NUM; i++ ){
        all_square.at(i).rect = scene_->addRect(
                                        all_square.at(i).x_*SQUARE_SIDE,
                                        all_square.at(i).y_*SQUARE_SIDE,
                                        SQUARE_SIDE, SQUARE_SIDE,
                                        blackPen, all_square.at(i).color);
    }

    // Update the area showing the next random tetromino.
    // The position of tetromino is changed to fit the nextTetGraphicsView.
    next_scene_->clear();
    for ( unsigned int i = all_square.size() - SQUARE_NUM;
          i < all_square.size(); i++ ){
        next_scene_->addRect((all_square.at(i).x_ - 4)*SQUARE_SIDE,
                            (all_square.at(i).y_ + 1)*SQUARE_SIDE,
                            SQUARE_SIDE, SQUARE_SIDE,
                            blackPen, all_square.at(i).color);
    }


}

void MainWindow::rotate_current_tet()
{
    // Choosing one square of current tetromino to be pivot.
    int pivotX = all_square.at(all_square.size() - 5).x_;
    int pivotY = all_square.at(all_square.size() - 5).y_;

    // Vector contain the original squares
    // before they change coordinat for rotattion.
    std::vector<Square> current_rotate;

    // If current tetromino is square, nothing happens
    if ( all_square.at(all_square.size() - 5).color ==
         Qt::lightGray ) return;

    // Changing the coordinates of squares of tetronimo needing rotation.
    for ( unsigned int i = all_square.size() - 2 * SQUARE_NUM;
          i < all_square.size() - SQUARE_NUM; i++ ){
        int tempX = all_square.at(i).x_;
        current_rotate.push_back(all_square.at(i));

        all_square.at(i).x_ = (all_square.at(i).y_ - pivotY) + pivotX;
        all_square.at(i).y_ = pivotY - (tempX - pivotX);
    }

    // If the coordiantes of rotated tetronimon overlapping any tetromino
    // the current tetromino change back to original shape.
    if ( !check_movable(LEFT) || !check_movable(RIGHT) ||
           !check_movable(OVERLAP, false) || !check_movable(DOWN) ||
           !check_movable(UP)){
        for ( unsigned int i = all_square.size() - 2 * SQUARE_NUM;
              i < all_square.size() - SQUARE_NUM; i++ ){
            all_square.at(i) = current_rotate.front();
            current_rotate.erase(current_rotate.begin());
        }
    }
}

void MainWindow::new_tetromino()
{

    timer_.start(interval_);

    // Random next tetromino to display in nextTetGraphicsView
    random_tetromino();

    // Check if the game is over or not.
    // If not the next tetromino will fall down automatically.
    // Otherwise, the game is stopped.
    if ( check_movable(OVERLAP, true) && check_movable(UP) ){
        score_ += GAIN_SCORE;
        update_gameboard();
    } else {
        game_over();
    }
}

void MainWindow::delete_full_row()
{
    // Vector contains squares that have same y-coordinate.
    // Number of full row initially equals 0.
    std::vector<int> same_row;
    int full_row = 0;

    // Checking all y-coordinate
    for ( int y = 0; y < ROWS; y++ ){
        for ( unsigned int i = 0; i < all_square.size() - SQUARE_NUM; i++ ){
            if( all_square.at(i).y_ == y ){
                same_row.push_back(i);
            }
        }
        // The number of elements in same_row equals the COLUMNS of
        // game board, that row should be deleted.
        if ( int(same_row.size()) == COLUMNS ){
            while( !(same_row.empty()) ){
                all_square.erase(all_square.begin() + same_row.back());
                same_row.pop_back();
            }
            // Move all squares having y-coordinate down by SQUARE_SIDE.
            if ( int(all_square.size()) > SQUARE_NUM ){
                for( unsigned int i = 0;
                     i < all_square.size() - SQUARE_NUM; i++){
                    if ( all_square.at(i).y_ < y ){
                        all_square.at(i).y_ += 1;
                    }
                }
            }
            // Number of full rows increase by 1
            full_row += 1;
        }
        same_row.clear();
    }
    // Update the game area.
    // There more rows are removed, the more scores gained (by multiplication).
    update_gameboard();
    score_ += full_row*full_row*GAIN_SCORE;
}

void MainWindow::advance_game()
{
    // The speed of falling will increase ( interval_ decreses
    // by ADVANCE) if the score increases by ADVANCE_SCORE.
    if ( interval_ > ADVANCE && score_ % ADVANCE_SCORE == 0 ){
        interval_ -= ADVANCE;
    }
}

void MainWindow::game_over()
{
    score_ -=GAIN_SCORE;
    timer_.stop();

    // Inform the player that the game is over
    ui->gameStatusTextBrowser->setText(" -GAME OVER-");

    // Player can press restartButton to play game again.
    ui->restartButton->setDisabled(false);

    // All other butons are disable when game is over.
    ui->quitButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);
    ui->resetButton->setDisabled(true);
}

bool MainWindow::check_movable(int direct, bool not_rotate)
{
    /* Check that if the current tetromino if movable in
     * direction left, right, down by case LEFT, RIGHT, DOWN
     */
    if ( int(all_square.size()) > 2 * SQUARE_NUM ){
        for ( unsigned int i = 0;
              i < all_square.size() - 2 * SQUARE_NUM; i++ ){
            for ( unsigned int j = all_square.size() - 2 * SQUARE_NUM;
                  j < all_square.size() - SQUARE_NUM; j++ ){
                switch (direct) {
                case LEFT:
                    if ( all_square.at(j).y_ == all_square.at(i).y_ &&
                         all_square.at(j).x_ - 1 == all_square.at(i).x_){
                        return false;
                    }
                    break;
                case RIGHT:
                    if ( all_square.at(j).y_ == all_square.at(i).y_ &&
                         all_square.at(j).x_ + 1 == all_square.at(i).x_){
                        return false;
                    }
                    break;
                case DOWN:
                    if ( all_square.at(j).x_ == all_square.at(i).x_ &&
                         all_square.at(j).y_ + 1 == all_square.at(i).y_){
                        return false;
                    }
                    break;
                // This case UP to check the status of the game.
                case UP:
                    if ( all_square.at(i).y_ <= BORDER_UP ){
                        return is_running_ = false;
                    }
                    break;
                // This case OVERLAP to check
                // bool not_rotate is true when the status of the game
                // otherwise to check if the coordinate of the needed rotation
                // tetromino is overlapped with any other square(s).
                case OVERLAP:
                    if ( all_square.at(j).x_ == all_square.at(i).x_ &&
                         all_square.at(j).y_ == all_square.at(i).y_){
                        if ( not_rotate ) return is_running_ = false;
                        return false;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }

    for ( unsigned int i = all_square.size() - 8;
          i < all_square.size() - 4; i++ ){
        switch (direct) {
        case LEFT:
            if ( all_square.at(i).x_ <= BORDER_LEFT ){
                return false;
            }
            break;
        case RIGHT:
            if ( all_square.at(i).x_ >= COLUMNS - 1 ){
                return false;
            }
            break;
        case DOWN:
            if ( all_square.at(i).y_ >= ROWS - 1 ){
                return false;
            }
            break;
        // This case up is to check if the coordinate of the needed rotation
        // is out of game area.
        case UP:
            if ( all_square.at(i).y_ < BORDER_UP ){
                return false;
            }
            break;
        default:
            break;
        }
    }
    return true;
}

void MainWindow::random_tetromino()
{
    // Initial coordinate of tetromino that lies in the
    // middle of the game area.
    const int in_x = COLUMNS / 2;
    const int in_y = BORDER_UP;

    // Different colors for different tetromino shapes
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QBrush greenBrush(Qt::green);
    QBrush greyBrush(Qt::lightGray);
    QBrush yellowBrush(Qt::yellow);
    QBrush cyanBrush(Qt::cyan);
    QBrush magentaBrush(Qt::darkMagenta);

    // Initialize the initial coordinates and colors
    // for 4 squares combining into different tetromino shapes.
    switch (int(distr(randomEng))) {
    case HORIZONTAL:
        all_square.push_back( {rect_, in_x - 1, in_y, redBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y, redBrush} );
        all_square.push_back( {rect_, in_x + 2, in_y, redBrush} );
        all_square.push_back( {rect_, in_x, in_y, redBrush} );
        break;
    case LEFT_CORNER:
        all_square.push_back( {rect_, in_x - 1, in_y, blueBrush} );
        all_square.push_back( {rect_, in_x - 1, in_y + 1, blueBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y + 1, blueBrush} );
        all_square.push_back( {rect_, in_x, in_y + 1, blueBrush} );
        break;
    case RIGHT_CORNER:
        all_square.push_back( {rect_, in_x- 1, in_y + 1, greenBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y + 1, greenBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y, greenBrush} );
        all_square.push_back( {rect_, in_x, in_y + 1, greenBrush} );
        break;
    case SQUARE:
        all_square.push_back( {rect_, in_x + 1, in_y, greyBrush} );
        all_square.push_back( {rect_, in_x, in_y + 1, greyBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y + 1, greyBrush} );
        all_square.push_back( {rect_, in_x, in_y, greyBrush} );
        break;
    case STEP_UP_RIGHT:
        all_square.push_back( {rect_, in_x - 1, in_y + 1, yellowBrush} );
        all_square.push_back( {rect_, in_x, in_y, yellowBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y, yellowBrush} );
        all_square.push_back( {rect_, in_x, in_y + 1, yellowBrush} );
        break;
    case PYRAMID:
        all_square.push_back( {rect_, in_x, in_y, cyanBrush} );
        all_square.push_back( {rect_, in_x - 1, in_y + 1, cyanBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y + 1, cyanBrush} );
        all_square.push_back( {rect_, in_x, in_y + 1, cyanBrush} );
        break;
    case STEP_UP_LEFT:
        all_square.push_back( {rect_, in_x - 1, in_y, magentaBrush} );
        all_square.push_back( {rect_, in_x, in_y, magentaBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y + 1, magentaBrush} );
        all_square.push_back( {rect_, in_x, in_y + 1, magentaBrush} );
        break;
    default:
        break;
    }
}

void MainWindow::on_startButton_clicked()
{
    timer_.start(interval_);

    // Displays the inital score.
    ui->scorelcdNumber->display(score_);

    score_ += GAIN_SCORE;
    // Random twice  to get the current and the nexr tetromino.
    random_tetromino();
    random_tetromino();
    update_gameboard();

    // StartButton and other (except pause, quit and reset button)
    //is disable when the game starts
    ui->startButton->setDisabled(true);
    ui->pauseButton->setDisabled(false);
    ui->resetButton->setDisabled(false);
    ui->easyRadioButton->setDisabled(true);
    ui->mediumRadioButton->setDisabled(true);
    ui->hardRadioButton->setDisabled(true);
}

void MainWindow::on_quitButton_clicked()
{
    this->close();
}

void MainWindow::on_pauseButton_clicked()
{
    timer_.stop();

    // To make all key press disable
    is_running_ = false;

    // PauseButton cannot be pressed.
    // ResumeButton can be pressed when game is pause.
    ui->resumeButton->setDisabled(false);
    ui->pauseButton->setDisabled(true);
}

void MainWindow::on_resumeButton_clicked()
{
    timer_.start(1000);
    // To make all key press able to press
    is_running_ = true;

    // ResumeButton cannot be pressed.
    // PauseButton can be pressed when game is running.
    ui->resumeButton->setDisabled(true);
    ui->pauseButton->setDisabled(false);
}

void MainWindow::on_resetButton_clicked()
{
    // Clear all the game memory and start game again.
    all_square.clear();
    scene_->clear();
    next_scene_->clear();

    // Score will be to zero and displayed
    score_ = 0;
    ui->scorelcdNumber->display(score_);
    timer_.stop();

    // Buttons to choose the difficulty of game are able to toggle.
    ui->easyRadioButton->setDisabled(false);
    ui->mediumRadioButton->setDisabled(false);
    ui->hardRadioButton->setDisabled(false);

    //Can start game again with previous level
    ui->startButton->setDisabled(false);

    // PauseButton cannot be pressed before chosing game level.
    ui->pauseButton->setDisabled(true);
}

void MainWindow::on_restartButton_clicked()
{
    // To make all key press able to press
    is_running_ = true;
    // Inform player that tthe game has been start.
    ui->gameStatusTextBrowser->setText("-TETRIS GAME-");
    on_resetButton_clicked();
}

void MainWindow::on_easyRadioButton_toggled(bool checked)
{
    ui->easyRadioButton->setChecked(checked);
    interval_ = EASY;
    ui->startButton->setDisabled(false);
}

void MainWindow::on_mediumRadioButton_toggled(bool checked)
{
    ui->mediumRadioButton->setChecked(checked);
    interval_ = MEDIUM;
    ui->startButton->setDisabled(false);
}

void MainWindow::on_hardRadioButton_toggled(bool checked)
{
    ui->hardRadioButton->setChecked(checked);
    interval_ = HARD;
    ui->startButton->setDisabled(false);
}
