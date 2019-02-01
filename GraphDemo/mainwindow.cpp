#include "edge.h"
#include "mainwindow.h"
#include "node.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->widget = new GraphWidget(this);
    ui->mainGraphicsView->setViewport(this->widget);
    Node* node1 = new Node(this->widget);
    Node *node2 = new Node(this->widget);
    Edge* edge = new Edge(node1, node2, this->widget);
    node1->setPos(-100, -50);
    node2->setPos(100, -50);
    edge->addEllipseAnimation(Qt::black);
    this->widget->scene()->addItem(node1);
    this->widget->scene()->addItem(node2);
    this->widget->scene()->addItem(edge);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    this->widget->keyPressEvent(event);
}
