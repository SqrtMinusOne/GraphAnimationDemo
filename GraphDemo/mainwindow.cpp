#include "edge.h"
#include "mainwindow.h"
#include "node.h"
#include "ui_mainwindow.h"
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->widget = new GraphWidget(this);
    ui->mainGraphicsView->setViewport(this->widget);    
    /* Соединение сигналов окна и слотов */
    connect(this->ui->action_clear_animation, SIGNAL(triggered()), this->widget, SLOT(clearAnimations()));
    connect(this->ui->action_start_animation, SIGNAL(triggered()), this->widget, SLOT(startAnimation()));
    connect(this->ui->action_stop_animation, SIGNAL(triggered()), this->widget, SLOT(stopAnimation()));
    connect(this->ui->action_add_animation, SIGNAL(triggered()), this, SLOT(addAnimations()));

    /* Добавление элементов */
    Node* node1 = new Node(this->widget);
    Node *node2 = new Node(this->widget);
    Node* node3 = new Node(this->widget);
    Edge* edge1 = new Edge(node1, node2, this->widget);
    Edge* edge2 = new Edge(node2, node3, this->widget);
    Edge* edge3 = new Edge(node3, node1, this->widget);
    node1->setPos(-100, -0);
    node2->setPos(100, -0);
    node3->setPos(0, -100);
    this->widget->scene()->addItem(node1);
    this->widget->scene()->addItem(node2);
    this->widget->scene()->addItem(node3);
    this->widget->scene()->addItem(edge1);
    this->widget->scene()->addItem(edge2);
    this->widget->scene()->addItem(edge3);
    addAnimations();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    /* Передача управления виджету при нажатии на клавишу */
    this->widget->keyPressEvent(event);
}

void MainWindow::on_action_exit_triggered()
{
    exit(0);
}

void MainWindow::addAnimations()
{
    /* Добавление анимации на каждое ребро */
    foreach (QGraphicsItem *item, this->widget->scene()->items()) {
        if (Edge *edge = qgraphicsitem_cast<Edge*>(item)){
            qint32 color = rand();
            edge->addEllipseAnimation(QColor::fromRgb(color));
        }
    }
}
