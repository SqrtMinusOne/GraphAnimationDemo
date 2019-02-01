#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include "graphwidget.h"
#include "edge.h"

class Node : public QGraphicsItem
{
public:
    Node(GraphWidget* graphWidget);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    int getX() const;
    int getY() const;
    int getW() const;
    int getH() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    GraphWidget* graph;
    QList<Edge *> edgeList;
    QPointF newPos;
    int x;
    int y;
    int w;
    int h;
};

#endif // NODE_H
