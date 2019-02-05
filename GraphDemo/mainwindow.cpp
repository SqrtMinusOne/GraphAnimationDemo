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
    Node* node3 = new Node(this->widget);
    Edge* edge1 = new Edge(node1, node2, this->widget);
    Edge* edge2 = new Edge(node2, node3, this->widget);
    Edge* edge3 = new Edge(node3, node1, this->widget);
    node1->setPos(-100, -0);
    node2->setPos(100, -0);
    node3->setPos(0, -100);
    edge1->addEllipseAnimation(Qt::black);
    edge2->addEllipseAnimation(Qt::red);
    edge3->addEllipseAnimation(Qt::blue);
    this->widget->scene()->addItem(node1);
    this->widget->scene()->addItem(node2);
    this->widget->scene()->addItem(node3);
    this->widget->scene()->addItem(edge1);
    this->widget->scene()->addItem(edge2);
    this->widget->scene()->addItem(edge3);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    this->widget->keyPressEvent(event);
}
