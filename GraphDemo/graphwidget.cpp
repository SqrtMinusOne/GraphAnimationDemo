﻿#include "graphwidget.h"
#include "edge.h"
#include <QKeyEvent>
#include <QDebug>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView (parent)
{
    QGraphicsScene* scene = new QGraphicsScene(this); //Создание сцены
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); //Отключить индексирование
    scene->setSceneRect(-200, -200, 400, 400); //Размер сцены (x, y, w, h)
    setScene(scene); //Установка сцены

    /* Оптимизация */
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);

    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);

    /* Настройка таймера */
    animationTimer = new QTimer(this);
    animationTimer->start(10);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(processAnimations()));
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    /* Увеличение / уменьшение сцены */
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    /* Обработка нажатий на кнопку */
    switch (event->key()) {
        case Qt::Key_Plus:
            zoomIn();
            break;
        case Qt::Key_Minus:
            zoomOut();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::startAnimation(){
    /* Запуск таймера */
    if (!this->animationTimer->isActive()){
        this->animationTimer->start(10);
    }
}

void GraphWidget::stopAnimation(){
    /* Остановка таймера */
    if (this->animationTimer->isActive()){
        this->animationTimer->stop();
    }
}

void GraphWidget::clearAnimations(){
    /* Удаление анимаций с ребрер */
    foreach (QGraphicsItem *item, scene()->items()) { //Проход по всем item'ам
        if (Edge *edge = qgraphicsitem_cast<Edge*>(item)) //Если проходит каст item'a к Edge
            edge->clearAnimations();
    }
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    /* Рисование фона */
    QRectF sceneRect = this->sceneRect();
    QBrush brush = QBrush(Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), brush);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
}

void GraphWidget::processAnimations(){
    /* Обработка анимаций.
       QGraphicsItem не унаследован от QObject, а значит, не поддерживает сигналы и слоты.
       Нужно обрабатывать снаружи
    */
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Edge *edge = qgraphicsitem_cast<Edge*>(item))
            edge->processAnimations();
    }
}
