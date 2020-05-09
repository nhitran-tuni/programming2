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
    connect(&timer_, &QTimer::timeout, this, &MainWindow::tetrino_move);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::draw_tetrino);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw_tetrino()
{
    timer_.start(1000);
    random_tetrino();

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

    for ( auto item : rect_vect ){
        item.rect = scene_->addRect(item.pos_x_, item.pos_y_,
                                    SQUARE_SIDE, SQUARE_SIDE,
                                    blackPen, item.color);
    }
}

void MainWindow::tetrino_move()
{
//    for ( QGraphicsRectItem* ele_rect : rect_vect ){
//        qreal current_x = rect_vect.front()->x();
//        qreal current_y = rect_vect.front()->y();

//        qreal deltaX, deltaY;

//        deltaY = static_cast<qreal>(SQUARE_SIDE);
//        deltaX = 0;

//        current_y += deltaY;
//        QRectF rect = scene_->sceneRect();
//        if(rect.contains(current_x, current_y)) {
//            ele_rect->moveBy(deltaX, deltaY);
//        } else {
//            timer_.stop();
//        }
//    }
}

void MainWindow::random_tetrino()
{
    random_tet_ = int(distr(randomEng));
    const int in_x = 110;
    const int in_y = 0;

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QBrush greenBrush(Qt::green);
    QBrush greyBrush(Qt::lightGray);
    QBrush yellowBrush(Qt::yellow);
    QBrush cyanBrush(Qt::cyan);
    QBrush magentaBrush(Qt::darkMagenta);

    if ( random_tet_ == HORIZONTAL ){
        rect_vect.push_back( {rect_, in_x - SQUARE_SIDE, in_y, redBrush} );
        rect_vect.push_back( {rect_, in_x, in_y, redBrush} );
        rect_vect.push_back( {rect_, in_x + SQUARE_SIDE, in_y, redBrush} );
        rect_vect.push_back( {rect_, in_x + 2*SQUARE_SIDE, in_y, redBrush} );
    } else if ( random_tet_ == LEFT_CORNER ){
        rect_vect.push_back( {rect_, in_x - SQUARE_SIDE, in_y, blueBrush} );
        rect_vect.push_back( {rect_, in_x - SQUARE_SIDE, in_y + SQUARE_SIDE, blueBrush} );
        rect_vect.push_back( {rect_, in_x, in_y + SQUARE_SIDE, blueBrush} );
        rect_vect.push_back( {rect_, in_x + SQUARE_SIDE, in_y + SQUARE_SIDE, blueBrush} );
    } else if ( random_tet_ == RIGHT_CORNER ){
        rect_vect.push_back( {rect_, in_x- SQUARE_SIDE, in_y + SQUARE_SIDE, greenBrush} );
        rect_vect.push_back( {rect_, in_x, in_y + SQUARE_SIDE, greenBrush} );
        rect_vect.push_back( {rect_, in_x + SQUARE_SIDE, in_y + SQUARE_SIDE, greenBrush} );
        rect_vect.push_back( {rect_, in_x + SQUARE_SIDE, in_y, greenBrush} );
    } else if ( random_tet_ == SQUARE ){
        rect_vect.push_back( {rect_, in_x, in_y, greyBrush} );
        rect_vect.push_back( {rect_, in_x + SQUARE_SIDE, in_y, greyBrush} );
        rect_vect.push_back( {rect_, in_x, in_y + SQUARE_SIDE, greyBrush} );
        rect_vect.push_back( {rect_, in_x + SQUARE_SIDE, in_y + SQUARE_SIDE, greyBrush} );
    } else if ( random_tet_ == STEP_UP_RIGHT ){
        rect_vect.push_back( {rect_, in_x - SQUARE_SIDE, in_y + SQUARE_SIDE, yellowBrush} );
        rect_vect.push_back( {rect_, in_x, in_y + SQUARE_SIDE, yellowBrush} );
        rect_vect.push_back( {rect_, in_x, in_y, yellowBrush} );
        rect_vect.push_back( {rect_, in_x + SQUARE_SIDE, in_y, yellowBrush} );
    } else if ( random_tet_ == PYRAMID ){
        rect_vect.push_back( {rect_, in_x, in_y, cyanBrush} );
        rect_vect.push_back( {rect_, in_x - SQUARE_SIDE, in_y + SQUARE_SIDE, cyanBrush} );
        rect_vect.push_back( {rect_, in_x, in_y + SQUARE_SIDE, cyanBrush} );
        rect_vect.push_back( {rect_, in_x + SQUARE_SIDE, in_y + SQUARE_SIDE, cyanBrush} );
    } else {
        rect_vect.push_back( {rect_, in_x - SQUARE_SIDE, in_y, magentaBrush} );
        rect_vect.push_back( {rect_, in_x, in_y, magentaBrush} );
        rect_vect.push_back( {rect_, in_x, in_y + SQUARE_SIDE, magentaBrush} );
        rect_vect.push_back( {rect_, in_x + SQUARE_SIDE, in_y + SQUARE_SIDE, magentaBrush} );
    }
}

