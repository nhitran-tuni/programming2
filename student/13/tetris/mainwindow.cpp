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
//    timer_.setSingleShot(false);
    ui->quitButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);
    ui->resumeButton->setDisabled(true);

    is_running_ = true;

    connect(&timer_, &QTimer::timeout, this, &MainWindow::tetromino_move);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
//    qreal deltaX = static_cast<qreal>(0);
//    qreal deltaY = static_cast<qreal>(0);
    if ( !is_running_ ) return;

    if ( event->key() == Qt::Key_A ){
        if ( check_movable(LEFT) ){
            for ( unsigned int i = all_square.size() - 4;
                  i < all_square.size(); i++ ){
                all_square.at(i).x_ -= 1;
            }
        }
    }

    if ( event->key() == Qt::Key_D ){
        if ( check_movable(RIGHT) ){
            for ( unsigned int i = all_square.size() - 4;
                  i < all_square.size(); i++ ){
                all_square.at(i).x_ += 1;
            }
        }
    }

    if ( event->key() == Qt::Key_S){
        if ( check_movable(DOWN) ){
            for ( unsigned int i = all_square.size() - 4;
                  i < all_square.size(); i++ ){
                all_square.at(i).y_ += 1;
            }
        }
    }

    if ( event->key() == Qt::Key_W ){
        for ( unsigned int j = all_square.size() - 4;
              j < all_square.size(); j++ ){
            int temp_x = all_square.at(j).x_;
            all_square.at(j).x_ = all_square.at(j).y_;
            all_square.at(j).y_ = temp_x;
        }
    }
    draw();
/*
//    for ( unsigned int i = rect_vect.size() - 4; i < rect_vect.size(); i++ ){
//        rect_vect.at(i).rect->moveBy(deltaX,deltaY);
//        rect_vect.at(i).pos_x_ = rect_vect.at(i).rect->x();
//        rect_vect.at(i).pos_y_ = rect_vect.at(i).rect->y();
//    }
    */
}
/*
void MainWindow::start_buttom_press()
{
    timer_.start(1000);
    random_tetromino();

//    QBrush redBrush(Qt::red);
//    QBrush blueBrush(Qt::blue);
//    QBrush greenBrush(Qt::green);
//    QBrush greyBrush(Qt::lightGray);
//    QBrush yellowBrush(Qt::yellow);
//    QBrush cyanBrush(Qt::cyan);
//    QBrush magentaBrush(Qt::darkMagenta);

//    std::map<int, QBrush> palette;
//    palette[HORIZONTAL] = redBrush;
//    palette[RIGHT_CORNER] = blueBrush;
//    palette[LEFT_CORNER] = greenBrush;
//    palette[SQUARE] = greyBrush;
//    palette[STEP_UP_RIGHT] = yellowBrush;
//    palette[PYRAMID] = cyanBrush;
//    palette[STEP_UP_LEFT] = magentaBrush;


    QPen blackPen(Qt::black);
    blackPen.setWidth(1.5);

    for ( auto item : all_square ){
        item.rect = scene_->addRect(item.x_*SQUARE_SIDE, item.y_*SQUARE_SIDE,
                                    SQUARE_SIDE, SQUARE_SIDE,
                                    blackPen, item.color);
    }

    timer_.start(1000);
    random_tetromino();
    draw();
}
*/
void MainWindow::tetromino_move()
{
    /*
//    for ( auto ele_rect : rect_vect ){
//        qreal current_x = ele_rect.rect->x();
//        qreal current_y = ele_rect.rect->y();

//        qreal deltaX, deltaY;

//        deltaY = static_cast<qreal>(SQUARE_SIDE);
//        deltaX = 0;

//        current_y += deltaY;
//        current_x += deltaX;
//        QRectF rect = scene_->sceneRect();
//        if(rect.contains(current_x, current_y)) {
//            ele_rect.rect->moveBy(deltaX, deltaY);
//        } else {
//            timer_.stop();
//        }
//    }
//    while ( check_movable(DOWN) ){
//        qreal deltaY, deltaX;
//        deltaY = static_cast<qreal>(SQUARE_SIDE);
//        deltaX = static_cast<qreal>(0);

//        for ( unsigned int i = rect_vect.size() - 4; i < rect_vect.size(); i++ ){
//            rect_vect.at(i).rect->moveBy(0,deltaY);
//            rect_vect.at(i).pos_x_ = rect_vect.at(i).rect->x();
//            rect_vect.at(i).pos_y_ = rect_vect.at(i).rect->y();
//        }

//        std::vector<Square>::iterator ite;

//        for ( ite = rect_vect.end() - 3; ite != rect_vect.end(); ite++ ){
//            ite->rect->moveBy(deltaX, deltaY);
//        }
//    }
//    timer_.stop();
    */
    if ( check_movable(DOWN) ){
        for ( unsigned int i = all_square.size() - 4;
              i < all_square.size(); i++ ){
            all_square.at(i).y_ += 1;
//            draw();
        }
        draw();
    } else {
        ui->scorelcdNumber->display(score_);
        timer_.stop();
        new_tetromino();
    }
}

void MainWindow::draw()
{
    QPen blackPen(Qt::black);
    blackPen.setWidth(1.5);

    scene_->clear();

    for ( auto item : all_square ){
        item.rect = scene_->addRect(item.x_*SQUARE_SIDE, item.y_*SQUARE_SIDE,
                                    SQUARE_SIDE, SQUARE_SIDE,
                                    blackPen, item.color);
    }
}
/*
//void MainWindow::rotate_current_tet()
//{
//    for ( unsigned int j = all_square.size() - 4; j < all_square.size(); j++ ){
//        int temp_x = all_square.at(j).x_;
//        all_square.at(j).x_ = - all_square.at(j).y_;
//        all_square.at(j).y_ = all_square.at(j).x_;
//    }
//}
*/

void MainWindow::new_tetromino()
{
    if ( !check_movable(DOWN) ){
        timer_.start(1000);
        random_tetromino();
        if ( check_movable(OVERLAP) ){
            draw();
        } else {
            for (int i = 0; i < 4; i++){
                all_square.pop_back();
            }
            score_ -=GAIN_SCORE;
            timer_.stop();
        }
    }
}

bool MainWindow::check_movable(int direct)
{
    /*
//    std::vector<Square>::iterator ite_1, ite_2;

//    for ( ite_1 =  rect_vect.begin(); ite_1 != rect_vect.end() - 3; ite_1++ ){
//        for ( ite_2 = rect_vect.end() - 3; ite_2 != rect_vect.end(); ite_2++ ){
//            if ( direct == LEFT ){
//                if ( ite_2->pos_x_ - SQUARE_SIDE == BORDER_LEFT ){
//                    return false;
//                }
//                if ( ite_2->pos_y_ == ite_1->pos_y_ &&
//                     ite_2->pos_x_ - SQUARE_SIDE == ite_1->pos_x_){
//                    return false;
//                }
//            } else if (direct == RIGHT){
//                if ( ite_2->pos_x_ + SQUARE_SIDE == BORDER_RIGHT ){
//                    return false;
//                }
//                if ( ite_2->pos_y_ == ite_1->pos_y_ &&
//                     ite_2->pos_x_ + SQUARE_SIDE == ite_1->pos_x_){
//                    return false;
//                }
//            } else if (direct == DOWN){
//                if ( ite_2->pos_y_ + SQUARE_SIDE == BORDER_DOWN ){
//                    return false;
//                }
//                if ( ite_2->pos_x_ == ite_1->pos_x_ &&
//                     ite_2->pos_y_ + SQUARE_SIDE == ite_1->pos_y_){
//                    return false;
//                }
//            }
//        }
//    }
    */
    if ( all_square.size() == 4 ){
        for ( unsigned int i = all_square.size() - 4;
              i < all_square.size(); i++ ){
            if ( direct == LEFT ){
                if ( all_square.at(i).x_ <= BORDER_LEFT ){
                    return false;
                }
            } else if (direct == RIGHT){
                if ( all_square.at(i).x_ >= COLUMNS - 1 ){
                    return false;
                }
            } else if (direct == DOWN){
                if ( all_square.at(i).y_ >= ROWS - 1 ){
                    return false;
                }
            }
        }
    }
    for ( unsigned int i = 0; i < all_square.size() - 4; i++ ){
        for ( unsigned int j = all_square.size() - 4;
              j < all_square.size(); j++ ){
            if ( direct == LEFT ){
                if ( all_square.at(j).x_ <= BORDER_LEFT ){
                    return false;
                }
                if ( all_square.at(j).y_ == all_square.at(i).y_ &&
                     all_square.at(j).x_ - 1 == all_square.at(i).x_){
                    return false;
                }
            } else if (direct == RIGHT ){
                if ( all_square.at(j).x_ >= COLUMNS - 1){
                    return false;
                }
                if ( all_square.at(j).y_ == all_square.at(i).y_ &&
                     all_square.at(j).x_ + 1 == all_square.at(i).x_){
                    return false;
                }
            } else if ( direct == DOWN ){
                if ( all_square.at(j).y_ >= ROWS - 1 ){
                    return false;
                }
                if ( all_square.at(j).x_ == all_square.at(i).x_ &&
                     all_square.at(j).y_ + 1 == all_square.at(i).y_){
                    return false;
                }
            } else if ( direct == OVERLAP ){
                if ( all_square.at(j).x_ == all_square.at(i).x_ &&
                     all_square.at(j).y_ == all_square.at(i).y_){
                    return is_running_ = false;
                }
            }
        }
    }
    return true;
}

void MainWindow::random_tetromino()
{
//    random_tet_ = int(distr(randomEng));
    const int in_x = COLUMNS / 2;
    const int in_y = BORDER_UP;

    score_ += GAIN_SCORE;

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QBrush greenBrush(Qt::green);
    QBrush greyBrush(Qt::lightGray);
    QBrush yellowBrush(Qt::yellow);
    QBrush cyanBrush(Qt::cyan);
    QBrush magentaBrush(Qt::darkMagenta);

    switch (int(distr(randomEng))) {
    case HORIZONTAL:
        all_square.push_back( {rect_, in_x - 1, in_y, redBrush} );
        all_square.push_back( {rect_, in_x, in_y, redBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y, redBrush} );
        all_square.push_back( {rect_, in_x + 2, in_y, redBrush} );
        break;
    case LEFT_CORNER:
        all_square.push_back( {rect_, in_x - 1, in_y, blueBrush} );
        all_square.push_back( {rect_, in_x - 1, in_y + 1, blueBrush} );
        all_square.push_back( {rect_, in_x, in_y + 1, blueBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y + 1, blueBrush} );
        break;
    case RIGHT_CORNER:
        all_square.push_back( {rect_, in_x- 1, in_y + 1, greenBrush} );
        all_square.push_back( {rect_, in_x, in_y + 1, greenBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y + 1, greenBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y, greenBrush} );
        break;
    case SQUARE:
        all_square.push_back( {rect_, in_x, in_y, greyBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y, greyBrush} );
        all_square.push_back( {rect_, in_x, in_y + 1, greyBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y + 1, greyBrush} );
        break;
    case STEP_UP_RIGHT:
        all_square.push_back( {rect_, in_x - 1, in_y + 1, yellowBrush} );
        all_square.push_back( {rect_, in_x, in_y + 1, yellowBrush} );
        all_square.push_back( {rect_, in_x, in_y, yellowBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y, yellowBrush} );
        break;
    case PYRAMID:
        all_square.push_back( {rect_, in_x, in_y, cyanBrush} );
        all_square.push_back( {rect_, in_x - 1, in_y + 1, cyanBrush} );
        all_square.push_back( {rect_, in_x, in_y + 1, cyanBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y + 1, cyanBrush} );
        break;
    case STEP_UP_LEFT:
        all_square.push_back( {rect_, in_x - 1, in_y, magentaBrush} );
        all_square.push_back( {rect_, in_x, in_y, magentaBrush} );
        all_square.push_back( {rect_, in_x, in_y + 1, magentaBrush} );
        all_square.push_back( {rect_, in_x + 1, in_y + 1, magentaBrush} );
        break;
    default:
        break;
    }
}

void MainWindow::on_startButton_clicked()
{
    timer_.start(1000);
    random_tetromino();
    draw();
    ui->startButton->setDisabled(true);
    ui->pauseButton->setDisabled(false);
    ui->quitButton->setDisabled(false);
}

void MainWindow::on_quitButton_clicked()
{
    this->close();
}

void MainWindow::on_pauseButton_clicked()
{
    timer_.stop();
    is_running_ = false;
    ui->resumeButton->setDisabled(false);
    ui->pauseButton->setDisabled(true);
}

void MainWindow::on_resumeButton_clicked()
{
    timer_.start(1000);
    is_running_ = true;
    ui->resumeButton->setDisabled(true);
    ui->pauseButton->setDisabled(false);
}
